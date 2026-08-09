#!/usr/bin/env bash
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$ROOT"

export NO_MKDOCS_2_WARNING=1

strict=""
if [[ "${1:-}" == "--strict" ]]; then
    strict="--strict"
fi

python3 -m mkdocs build --clean ${strict}

echo "Web generada: dist/site/index.html"
