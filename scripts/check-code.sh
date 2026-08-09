#!/usr/bin/env bash
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$ROOT"

mapfile -d '' files < <(find snippets -type f -name '*.cpp' -print0 | sort -z)

if [[ ${#files[@]} -eq 0 ]]; then
    echo "No hay snippets C++ para validar."
    exit 0
fi

for file in "${files[@]}"; do
    g++ -std=c++17 -Wall -Wextra -Wpedantic -fsyntax-only "$file"
    echo "C++ válido: $file"
done
