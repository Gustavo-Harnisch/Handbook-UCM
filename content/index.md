# UCM Competitive Programming Handbook

Esta es una **beta mínima** para comprobar que un mismo conjunto de archivos Markdown puede alimentar dos salidas:

1. una web navegable con MkDocs;
2. un handbook PDF offline con Pandoc.

## Contenido de esta beta

| Área | Tema | Complejidad principal | Uso típico |
|---|---|---:|---|
| Fundamentos | Notación Big-O | - | Estimar si una solución entra en tiempo |
| Estructuras | Fenwick Tree | `O(log n)` | Sumas prefijas con actualizaciones |
| Grafos | Dijkstra | `O((V+E) log V)` | Caminos mínimos con pesos no negativos |

## Filosofía

El directorio `content/` es la **fuente única de verdad**. Si corriges una explicación o un código aquí, el cambio aparecerá tanto en la web como en el siguiente PDF generado.

## Plantilla C++ mínima

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    return 0;
}
```
