# Complejidad algorítmica

Antes de implementar una solución conviene comparar el tamaño máximo de entrada con la complejidad esperada.

## Referencia rápida

| `n` aproximado | Complejidad que suele ser razonable |
|---:|---|
| `n <= 20` | `O(2^n)` o backtracking |
| `n <= 500` | `O(n^3)` en algunos problemas |
| `n <= 5,000` | `O(n^2)` |
| `n <= 200,000` | `O(n log n)` |
| `n <= 1,000,000` | `O(n)` o cercano |

Estas cifras son orientativas: el límite real depende del lenguaje, las constantes y el tiempo disponible.

## Orden de crecimiento

De menor a mayor costo típico:

```text
O(1)
O(log n)
O(n)
O(n log n)
O(n^2)
O(n^3)
O(2^n)
O(n!)
```

## Regla para competencia

Si el problema permite `n = 2 * 10^5`, una solución `O(n^2)` casi siempre es una señal de que falta una optimización o una idea distinta.
