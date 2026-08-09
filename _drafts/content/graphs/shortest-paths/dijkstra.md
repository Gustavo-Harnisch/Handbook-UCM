# Dijkstra

El algoritmo de **Dijkstra** calcula las distancias mínimas desde un nodo origen cuando las aristas tienen pesos **no negativos**.

## Cuándo utilizarlo

Úsalo para caminos mínimos desde una fuente en grafos dirigidos o no dirigidos, siempre que todas las aristas tengan peso mayor o igual que cero. Si existen pesos negativos, se necesita otro algoritmo, como Bellman–Ford.

## Propiedades

| Elemento | Valor |
|---|---|
| Tipo de grafo | Dirigido o no dirigido |
| Pesos negativos | No permitidos |
| Estructura habitual | `priority_queue` |
| Complejidad | `O((V + E) log V)` |

La lista de adyacencia ocupa `O(V + E)` y los arreglos auxiliares, junto con la cola de prioridad, requieren hasta `O(V + E)` memoria en esta implementación.

## Idea principal

La cola de prioridad mantiene el vértice pendiente con menor distancia conocida. Cuando se extrae una entrada vigente, se intentan mejorar las distancias de sus vecinos mediante relajación.

Una distancia puede insertarse varias veces porque `priority_queue` no disminuye claves existentes. La condición `current_distance != distance[u]` descarta las entradas antiguas.

## Implementación

```cpp
--8<-- "snippets/graphs/shortest-paths/dijkstra.cpp"
```

## Contrato de la implementación

- Los vértices están numerados desde `0`.
- Cada arista se representa como `{destino, peso}`.
- Todos los pesos deben ser no negativos.
- Un vértice inalcanzable conserva el valor `INF` definido en la función.

## Errores frecuentes

- Usar Dijkstra cuando existen pesos negativos.
- Usar `int` si la suma de pesos puede superar `2^31 - 1`.
- Olvidar descartar entradas antiguas de la cola de prioridad.
- Elegir un valor infinito demasiado pequeño.
- Sumar un peso a una distancia infinita sin controlar un posible desbordamiento.

## Checklist de competencia

1. ¿Todos los pesos son no negativos?
2. ¿Las distancias necesitan `long long`?
3. ¿El grafo es dirigido o no dirigido?
4. ¿Solo necesitas una fuente o varias?
5. ¿La lista de adyacencia agrega cada arista en la dirección correcta?
