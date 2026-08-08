# Fenwick Tree

Un **Fenwick Tree** o **Binary Indexed Tree (BIT)** mantiene información acumulada y permite actualizaciones puntuales y consultas de prefijo en `O(log n)`.

## Operaciones

| Operación | Complejidad |
|---|---:|
| Actualizar una posición | `O(log n)` |
| Suma de prefijo `[1, i]` | `O(log n)` |
| Suma de rango `[l, r]` | `O(log n)` |
| Memoria | `O(n)` |

## Idea clave

La expresión:

```cpp
i & -i
```

obtiene el bit menos significativo encendido. Ese valor determina el salto entre nodos internos del árbol.

## Implementación

```cpp
struct Fenwick {
    int n;
    vector<long long> bit;

    Fenwick(int n) : n(n), bit(n + 1, 0) {}

    void add(int i, long long delta) {
        for (; i <= n; i += i & -i)
            bit[i] += delta;
    }

    long long sumPrefix(int i) const {
        long long ans = 0;
        for (; i > 0; i -= i & -i)
            ans += bit[i];
        return ans;
    }

    long long sumRange(int l, int r) const {
        return sumPrefix(r) - sumPrefix(l - 1);
    }
};
```

## Cuándo usarlo

Es una buena opción cuando necesitas muchas operaciones mezcladas de:

- actualizar `a[i]`;
- consultar sumas prefijas;
- consultar sumas de intervalos.

Para operaciones más generales sobre rangos, un Segment Tree puede ser más flexible.
