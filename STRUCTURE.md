# Estructura del Handbook UCM

La estructura inicial replica las 3 partes, los 30 capítulos y las 118 subsecciones de `book.pdf`. Cada carpeta contiene únicamente un `index.md` con el nombre de la sección.

```text
content/
├── index.md
├── assets/                         Recursos compartidos de web y documentación
│   ├── banner.png
│   └── stylesheets/
│       └── extra.css
├── 00-preface/
│   └── index.md
├── part-01-basic-techniques/
│   ├── index.md
│   ├── 01-introduction/
│   │   ├── index.md
│   │   ├── 01-programming-languages/index.md
│   │   ├── 02-input-and-output/index.md
│   │   └── ...
│   ├── 02-time-complexity/index.md
│   ├── 03-sorting/index.md
│   ├── 04-data-structures/index.md
│   ├── 05-complete-search/index.md
│   ├── 06-greedy-algorithms/index.md
│   ├── 07-dynamic-programming/index.md
│   ├── 08-amortized-analysis/index.md
│   ├── 09-range-queries/index.md
│   └── 10-bit-manipulation/index.md
├── part-02-graph-algorithms/
│   ├── index.md
│   ├── 11-basics-of-graphs/index.md
│   ├── 12-graph-traversal/index.md
│   ├── 13-shortest-paths/index.md
│   ├── 14-tree-algorithms/index.md
│   ├── 15-spanning-trees/index.md
│   ├── 16-directed-graphs/index.md
│   ├── 17-strong-connectivity/index.md
│   ├── 18-tree-queries/index.md
│   ├── 19-paths-and-circuits/index.md
│   └── 20-flows-and-cuts/index.md
├── part-03-advanced-topics/
│   ├── index.md
│   ├── 21-number-theory/index.md
│   ├── 22-combinatorics/index.md
│   ├── 23-matrices/index.md
│   ├── 24-probability/index.md
│   ├── 25-game-theory/index.md
│   ├── 26-string-algorithms/index.md
│   ├── 27-square-root-algorithms/index.md
│   ├── 28-segment-trees-revisited/index.md
│   ├── 29-geometry/index.md
│   └── 30-sweep-line-algorithms/index.md
└── 99-bibliography/
    └── index.md
```

El patrón mostrado para `01-introduction/` se repite en los treinta capítulos. La lista completa de subsecciones y su orden está declarada en `mkdocs.yml`.

Los complementos prácticos derivados del material UTFSM se agregan como subsecciones explícitas dentro del capítulo relacionado. Sus implementaciones se agrupan por dominio en `snippets/` y cada página incluye el contrato de uso, complejidad y restricciones relevantes.

`mkdocs.yml` es el índice maestro. MkDocs usa esta navegación para la web y el generador de Pandoc lee el mismo orden para construir el PDF.

Los recursos comunes viven solamente en `content/assets/`. Las páginas de MkDocs los usan con rutas relativas a `content/`; los documentos de la raíz, como `README.md`, los referencian mediante `content/assets/...`. No se deben duplicar recursos en una carpeta `assets/` de la raíz.

El contenido desarrollado previamente se conserva fuera de la publicación en `_drafts/`.
