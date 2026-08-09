# Complemento UTFSM: estructuras avanzadas de rango

## Union-find con rollback

Mantiene componentes conexas reversibles, útil para conectividad offline con árbol de segmentos sobre el tiempo. `unite` cuesta `O(log V)` y `rollback(snapshot)` revierte las operaciones posteriores. No usa compresión de caminos para conservar el rollback.

> **Crédito UTFSM:** Sebastián Torrealba contribuyó la implementación de referencia en el Handbook UTFSM.

```cpp
--8<-- "snippets/data-structures/range-queries/rollback-disjoint-set.cpp"
```

## Segment tree lazy

Esta versión implementa suma de rango y suma de valores sobre un intervalo cerrado `[left, right]`. Tanto `add` como `sum` cuestan `O(log N)` y el árbol usa `O(N)` memoria. El vector inicial debe ser no vacío.

> **Crédito UTFSM:** Gabriel Carmona contribuyó la implementación de referencia en el Handbook UTFSM.

```cpp
--8<-- "snippets/data-structures/range-queries/lazy-segment-tree.cpp"
```

## Segment tree persistente

Cada actualización puntual genera una versión nueva. `update` devuelve su identificador y `sum(version, left, right)` consulta cualquier versión en `O(log N)`; la memoria total es `O(N + Q log N)`.

> **Crédito UTFSM:** Sebastián Torrealba contribuyó la implementación de referencia en el Handbook UTFSM.

```cpp
--8<-- "snippets/data-structures/range-queries/persistent-segment-tree.cpp"
```

## Errores frecuentes

- No mezcles rangos abiertos con estos intervalos cerrados.
- Conserva el número de versión retornado por `update`.
- Toma un `snapshot` antes del bloque temporal que deseas deshacer.
