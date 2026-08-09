# Complemento UTFSM: multiplicación rápida de polinomios

## Number Theoretic Transform

Multiplica polinomios módulo `998244353` mediante NTT. `convolve(a, b)` funciona en `O(N log N)`, donde `N` es la siguiente potencia de dos que cubre el grado del resultado. Sus coeficientes de entrada deben estar normalizados en `[0, 998244353)`.

> **Crédito UTFSM:** Sebastián Torrealba contribuyó la implementación de referencia en el Handbook UTFSM.

```cpp
--8<-- "snippets/mathematics/number-theoretic-transform.cpp"
```

La raíz primitiva y el módulo están fijados porque el módulo permite longitudes potencia de dos hasta `2^23`. Para otro módulo, usa CRT entre NTT compatibles o una FFT con control de redondeo.
