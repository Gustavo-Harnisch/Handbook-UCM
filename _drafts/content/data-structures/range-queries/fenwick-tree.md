# Fenwick Tree

Un **Fenwick Tree** o **Binary Indexed Tree (BIT)** mantiene información acumulada y permite actualizaciones puntuales y consultas de prefijo en `O(log n)`.

## Cuándo utilizarlo

Es apropiado cuando se mezclan muchas operaciones de estos tipos:

- sumar un valor a una posición;
- consultar una suma prefija;
- consultar la suma de un intervalo.

Esta implementación utiliza índices desde `1` hasta `n`. Para operaciones de rango más generales, un Segment Tree suele ser más flexible.

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

Al actualizar la posición `i`, la estructura avanza hacia los nodos que contienen su aporte. Al consultar un prefijo, retrocede acumulando bloques disjuntos hasta llegar a cero.

## Implementación

```cpp
--8<-- "snippets/data-structures/range-queries/fenwick-tree.cpp"
```

## Contrato de la implementación

- `add(i, delta)` requiere `1 <= i <= n`;
- `sum_prefix(i)` devuelve la suma del intervalo `[1, i]`;
- `sum_range(left, right)` devuelve la suma inclusiva `[left, right]`;
- los valores acumulados utilizan `long long`.

## Errores frecuentes

- Usar el índice `0` en una actualización: `i & -i` también será cero y el ciclo no avanzará.
- Confundir la indexación del arreglo original con la indexación interna desde uno.
- Utilizar `int` cuando las sumas pueden superar su rango.
- Intentar usar esta versión para operaciones que no admiten la resta de dos prefijos.
