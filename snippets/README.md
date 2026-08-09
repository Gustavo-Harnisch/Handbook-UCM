# Snippets de código

Este directorio contiene las implementaciones que aparecen en el handbook. Cada algoritmo vive en un único archivo y se incluye desde Markdown con PyMdown Snippets:

````markdown
```cpp
--8<-- "snippets/categoria/subcategoria/algoritmo.cpp"
```
````

MkDocs resuelve la inclusión para la web. `scripts/expand-snippets.py` realiza la misma operación antes de invocar Pandoc para que el PDF use exactamente el mismo código.

## Reglas

- Un archivo contiene un solo algoritmo, estructura o ejemplo bien delimitado.
- El código debe compilar con C++17 y no depender de macros personales.
- Los nombres deben describir el contenido y usar minúsculas con guiones.
- Los contratos e ideas se explican en `content/`; los archivos C++ conservan solo comentarios útiles para la implementación.
- Una corrección se realiza en el snippet, nunca en una copia pegada dentro del Markdown.

Las rutas de `snippets/` deben reflejar las rutas de `content/`. Por ejemplo:

```text
content/graphs/shortest-paths/dijkstra.md
snippets/graphs/shortest-paths/dijkstra.cpp
```
