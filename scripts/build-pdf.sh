#!/usr/bin/env bash
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$ROOT"

mkdir -p dist

files=()
while IFS= read -r line || [[ -n "$line" ]]; do
    [[ -z "$line" ]] && continue
    [[ "$line" =~ ^[[:space:]]*# ]] && continue
    files+=("$line")
done < pandoc/order.txt

pandoc \
    --metadata-file=pandoc/metadata.yaml \
    --from=gfm \
    --pdf-engine=xelatex \
    --highlight-style=tango \
    "${files[@]}" \
    -o dist/UCM-Competitive-Programming-Handbook.pdf

echo "PDF generado: dist/UCM-Competitive-Programming-Handbook.pdf"
