#!/usr/bin/env python3
"""Expande inclusiones de PyMdown Snippets para la compilación con Pandoc."""

from __future__ import annotations

import argparse
import re
from pathlib import Path


ROOT = Path(__file__).resolve().parent.parent
INCLUDE = re.compile(
    r'^(?P<indent>[ \t]*)--8<--\s+"(?P<path>[^"]+)"[ \t]*$',
    re.MULTILINE,
)
FIRST_HEADING = re.compile(r"^#{1,6}(?P<space>[ \t]+)", re.MULTILINE)


class SnippetError(RuntimeError):
    """Indica que una inclusión no es válida o no puede resolverse."""


def project_file(relative_path: str) -> Path:
    """Resuelve una ruta y garantiza que permanezca dentro del repositorio."""
    candidate = (ROOT / relative_path).resolve()
    try:
        candidate.relative_to(ROOT)
    except ValueError as error:
        raise SnippetError(
            f"La inclusión sale del repositorio: {relative_path}"
        ) from error

    if not candidate.is_file():
        raise SnippetError(f"No existe el archivo incluido: {relative_path}")
    return candidate


def expand_text(text: str, stack: tuple[Path, ...] = ()) -> str:
    """Sustituye cada directiva --8<-- por el contenido de su archivo."""

    def replace(match: re.Match[str]) -> str:
        relative_path = match.group("path")
        snippet = project_file(relative_path)
        if snippet in stack:
            chain = " -> ".join(path.relative_to(ROOT).as_posix() for path in (*stack, snippet))
            raise SnippetError(f"Inclusión circular detectada: {chain}")

        included = snippet.read_text(encoding="utf-8").rstrip("\n")
        if snippet.suffix.lower() in {".md", ".markdown"}:
            included = expand_text(included, (*stack, snippet))

        indent = match.group("indent")
        if not indent:
            return included
        return "\n".join(
            f"{indent}{line}" if line else "" for line in included.splitlines()
        )

    return INCLUDE.sub(replace, text)


def build_document(sources: list[str]) -> str:
    """Une los capítulos en el orden recibido y expande sus snippets."""
    document = ""
    for source_name in sources:
        source = project_file(source_name)
        text = source.read_text(encoding="utf-8")
        expanded = expand_text(text, (source,)).strip()

        relative = source.relative_to(ROOT / "content")
        parts = relative.parts
        if parts[0].startswith("part-"):
            level = min(3, len(parts) - 1)
            expanded = FIRST_HEADING.sub(
                f"{'#' * level}\\g<space>", expanded, count=1
            )

        starts_new_page = (
            not document
            or not parts[0].startswith("part-")
            or len(parts) <= 3
        )
        separator = "\n\n\\newpage\n\n" if starts_new_page and document else "\n\n"
        document += separator + expanded
    return document + "\n"


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Prepara el Markdown del handbook para Pandoc."
    )
    parser.add_argument("sources", nargs="+", help="Capítulos Markdown en orden")
    parser.add_argument("--output", required=True, help="Archivo Markdown generado")
    return parser.parse_args()


def main() -> int:
    args = parse_args()
    output = (ROOT / args.output).resolve()
    try:
        output.relative_to(ROOT)
    except ValueError as error:
        raise SnippetError(f"La salida debe quedar dentro del repositorio: {args.output}") from error

    output.parent.mkdir(parents=True, exist_ok=True)
    output.write_text(build_document(args.sources), encoding="utf-8")
    return 0


if __name__ == "__main__":
    try:
        raise SystemExit(main())
    except SnippetError as error:
        raise SystemExit(f"Error de snippets: {error}") from error
