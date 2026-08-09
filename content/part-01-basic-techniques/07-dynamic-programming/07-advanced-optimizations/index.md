# Complemento UTFSM: optimización de programación dinámica

## Li Chao Tree

Mantiene el mínimo de rectas `m*x + b` sobre un dominio entero fijo y cerrado. Insertar una recta y consultar un punto cuestan `O(log C)`, donde `C` es el tamaño del intervalo de coordenadas. Declara el dominio al construirlo y verifica que no haya overflow en `m*x + b`.

> **Crédito UTFSM:** Carlos Lagos contribuyó la implementación de referencia en el Handbook UTFSM.

```cpp
--8<-- "snippets/dynamic-programming/li-chao-tree.cpp"
```

Es apropiado para transiciones DP que minimizan expresiones lineales; para máximos, niega pendientes e interceptos, y vuelve a negar la respuesta.
