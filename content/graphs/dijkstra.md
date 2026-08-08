# Dijkstra

El algoritmo de **Dijkstra** calcula las distancias mínimas desde un nodo origen cuando las aristas tienen pesos **no negativos**.

## Propiedades

| Elemento | Valor |
|---|---|
| Tipo de grafo | Dirigido o no dirigido |
| Pesos negativos | No permitidos |
| Estructura habitual | `priority_queue` |
| Complejidad | `O((V + E) log V)` |

## Implementación

```cpp
using ll = long long;
using Edge = pair<int, int>; // {to, weight}

vector<ll> dijkstra(int source, const vector<vector<Edge>>& g) {
    const ll INF = (1LL << 62);
    int n = (int)g.size();

    vector<ll> dist(n, INF);
    priority_queue<pair<ll, int>,
                   vector<pair<ll, int>>,
                   greater<pair<ll, int>>> pq;

    dist[source] = 0;
    pq.push({0, source});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        if (d != dist[u])
            continue;

        for (auto [v, w] : g[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }

    return dist;
}
```

## Errores frecuentes

- usar Dijkstra cuando existen pesos negativos;
- usar `int` si la suma de pesos puede superar `2^31 - 1`;
- olvidar descartar entradas viejas de la cola de prioridad;
- elegir un `INF` demasiado pequeño.

## Checklist de competencia

1. ¿Todos los pesos son no negativos?
2. ¿Las distancias necesitan `long long`?
3. ¿El grafo es dirigido o no dirigido?
4. ¿Solo necesitas una fuente o varias?
