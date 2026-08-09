# Complemento UTFSM: teoría de números avanzada

## Teorema chino del resto

Combina dos congruencias, incluso si los módulos no son coprimos. Devuelve `(residuo, modulo)` normalizado, o `std::nullopt` si no hay solución o el mínimo común múltiplo no cabe en `long long`. La complejidad es `O(log min(m, n))`.

> **Crédito UTFSM:** Sebastián Torrealba contribuyó la implementación de referencia en el Handbook UTFSM.

```cpp
--8<-- "snippets/mathematics/chinese-remainder-theorem.cpp"
```

## Miller-Rabin determinista para 64 bits

`is_prime(number)` prueba primalidad exacta para todo `uint64_t` mediante una base de testigos válida en ese dominio. Usa multiplicación de 128 bits y tarda `O(log number)` por testigo.

> **Crédito UTFSM:** Sebastián Torrealba contribuyó la implementación de referencia en el Handbook UTFSM.

```cpp
--8<-- "snippets/mathematics/miller-rabin.cpp"
```

## Precauciones

- No conviertas números negativos a `uint64_t` antes de llamar a `is_prime`.
- El CRT admite módulos positivos solamente.
- Si necesitas combinar más de dos congruencias, combina el resultado con la siguiente de forma iterativa.
