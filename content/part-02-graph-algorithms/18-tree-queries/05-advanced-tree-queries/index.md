# Complemento UTFSM: consultas avanzadas en árboles

## Heavy-Light Decomposition

Descompone un árbol en segmentos contiguos para delegar consultas de camino a una estructura de rangos. La construcción toma `O(V)` y un camino se expresa en `O(log V)` segmentos. `path_segments(u, v)` devuelve intervalos inclusivos; para valores en aristas usa `edge_values = true`. El orden de los segmentos no sirve directamente para operaciones no conmutativas.

> **Crédito UTFSM:** Javier Oliva figura como autor de la implementación de referencia en el Handbook UTFSM.

```cpp
--8<-- "snippets/graphs/flow-and-trees/heavy-light-decomposition.cpp"
```

## Uso seguro

- El grafo debe ser un árbol conexo y sus vértices deben estar en `[0, V)`.
- Construye luego un segment tree o Fenwick sobre `position(v)`.
- Usa `subtree_segment(v)` para consultas sobre el subárbol de `v`.
