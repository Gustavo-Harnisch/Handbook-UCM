#!/usr/bin/env bash
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$ROOT"

mkdir -p dist
mkdir -p dist/.build

mapfile -t files < <(python3 scripts/list-nav-files.py)

if [[ ${#files[@]} -eq 0 ]]; then
    echo "No se encontraron capítulos en la navegación de mkdocs.yml." >&2
    exit 1
fi

python3 scripts/expand-snippets.py \
    --output dist/.build/handbook.md \
    "${files[@]}"

pandoc \
    --metadata-file=pandoc/metadata.yaml \
    --from=markdown \
    --pdf-engine=xelatex \
    --highlight-style=tango \
    --resource-path=.:content \
    dist/.build/handbook.md \
    -o dist/UCM-Competitive-Programming-Handbook.pdf

echo "PDF generado: dist/UCM-Competitive-Programming-Handbook.pdf"
