# Complemento UTFSM: flujos y matching

Estas implementaciones complementan el capítulo con soluciones listas para integrar en C++17. Se revisaron a partir de material del Handbook UTFSM; la procedencia detallada y la licencia se indican en la sección de créditos.

## Dinic

Calcula flujo máximo en una red dirigida con capacidades enteras no negativas. Su complejidad es `O(V^2 E)` en el peor caso y usa `O(V + E)` memoria. Crea el grafo con vértices en `[0, V)` y llama a `max_flow(source, sink)`; no reutilices la misma instancia si necesitas conservar las capacidades originales.

> **Crédito UTFSM:** Pablo Messina figura como autor de la implementación de referencia en el Handbook UTFSM.

```cpp
--8<-- "snippets/graphs/flow-and-trees/dinic.cpp"
```

## Hopcroft-Karp

Encuentra un matching máximo bipartito en `O(E sqrt(V))`. Los vértices de ambos lados se indexan desde cero y `left_matching()[u]` devuelve el vértice derecho emparejado con `u`, o `-1`.

> **Crédito UTFSM:** Abner Vidal contribuyó la implementación de referencia en el Handbook UTFSM.

```cpp
--8<-- "snippets/graphs/flow-and-trees/hopcroft-karp.cpp"
```

## Checklist

- Modela aristas dirigidas en Dinic; para una arista no dirigida agrega ambas direcciones según la capacidad requerida.
- En Hopcroft-Karp, separa claramente los dos conjuntos de vértices antes de insertar aristas.
- Usa `long long` si el flujo total puede superar `int`.
