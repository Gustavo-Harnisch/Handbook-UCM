# Complemento UTFSM: geometría computacional avanzada

## Convex hull

Construye el casco convexo de puntos enteros en sentido antihorario mediante monotonic chain. Tarda `O(N log N)`, no repite el primer punto al final y elimina puntos colineales interiores.

> **Crédito UTFSM:** Sebastián Torrealba contribuyó la implementación de referencia en el Handbook UTFSM.

```cpp
--8<-- "snippets/geometry/convex-hull.cpp"
```

## Punto en polígono

Clasifica un punto como interior, borde o exterior con ray casting. Funciona para polígonos simples y usa `long double`; la respuesta de borde depende del epsilon documentado.

> **Crédito UTFSM:** Sebastián Torrealba contribuyó la implementación de referencia en el Handbook UTFSM.

```cpp
--8<-- "snippets/geometry/point-in-polygon.cpp"
```

## Intersección de semiplanos

Interseca semiplanos orientados: el interior de cada uno debe quedar a la izquierda de su dirección. Corre en `O(N log N)` y devuelve el polígono convexo de intersección, o un vector vacío si la intersección es vacía o no queda acotada.

> **Crédito UTFSM:** Sebastián Torrealba contribuyó la implementación de referencia en el Handbook UTFSM.

```cpp
--8<-- "snippets/geometry/half-plane-intersection.cpp"
```

## Checklist numérico

- Mantén una convención única de orientación en todas las primitivas.
- Evita mezclar `double` y enteros cuando el problema requiera exactitud.
- Prueba casos degenerados: puntos colineales, aristas horizontales y semiplanos paralelos.
