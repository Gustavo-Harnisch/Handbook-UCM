#!/usr/bin/env python3
"""Lista los capítulos Markdown según el orden de navegación de MkDocs."""

from __future__ import annotations

from pathlib import Path
from typing import Any, Iterator

import yaml


ROOT = Path(__file__).resolve().parent.parent


class MkDocsLoader(yaml.SafeLoader):
    """Loader mínimo para las etiquetas admitidas por la configuración."""


def relative_tag(loader: MkDocsLoader, node: yaml.Node) -> str:
    return loader.construct_scalar(node)


MkDocsLoader.add_constructor("!relative", relative_tag)


def markdown_entries(node: Any) -> Iterator[str]:
    if isinstance(node, str):
        if node.endswith(".md"):
            yield node
        return
    if isinstance(node, list):
        for item in node:
            yield from markdown_entries(item)
        return
    if isinstance(node, dict):
        for value in node.values():
            yield from markdown_entries(value)


def main() -> int:
    config_path = ROOT / "mkdocs.yml"
    config = yaml.load(config_path.read_text(encoding="utf-8"), Loader=MkDocsLoader)
    docs_dir = ROOT / config.get("docs_dir", "docs")

    entries = list(markdown_entries(config.get("nav", [])))
    if not entries:
        raise SystemExit("mkdocs.yml no contiene páginas Markdown en nav.")

    for entry in entries:
        source = docs_dir / entry
        if not source.is_file():
            raise SystemExit(f"No existe la página declarada en nav: {entry}")
        print(source.relative_to(ROOT).as_posix())
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
