# Complejidad algorítmica y notación Big O

La complejidad algorítmica describe cómo cambia el costo de una solución cuando crece su entrada. Permite comparar algoritmos sin depender de un computador, una marca de procesador o una ejecución particular.

## Objetivo

Al terminar este capítulo deberías poder:

- identificar las variables que determinan el tamaño de una entrada;
- estimar la complejidad temporal y espacial de un algoritmo;
- reconocer los órdenes de crecimiento más comunes;
- relacionar las restricciones de un problema con una solución razonable.

## Tiempo y espacio

La **complejidad temporal** aproxima la cantidad de operaciones ejecutadas. La **complejidad espacial** aproxima la memoria adicional que utiliza el algoritmo.

Ambas se expresan en función del tamaño de la entrada. Por ejemplo, recorrer un arreglo de `n` elementos toma tiempo `Θ(n)`. Guardar una copia completa del mismo arreglo requiere espacio adicional `Θ(n)`.

No siempre existe una sola variable. En un grafo suelen utilizarse `V` para los vértices y `E` para las aristas; recorrer una lista de adyacencia completa cuesta `Θ(V + E)`.

## Notaciones asintóticas

Las notaciones asintóticas describen el crecimiento para entradas suficientemente grandes.

| Notación | Qué expresa | Lectura práctica |
|---|---|---|
| `O(f(n))` | Cota superior | El costo no crece más rápido que `f(n)`, salvo por una constante |
| `Ω(f(n))` | Cota inferior | El costo crece al menos tan rápido como `f(n)` |
| `Θ(f(n))` | Cota ajustada | El costo crece al mismo orden que `f(n)` |

Si el número de operaciones es `3n^2 + 5n + 20`, el término dominante es `n^2`, por lo que su complejidad ajustada es `Θ(n^2)`. Las constantes y los términos de menor orden dejan de dominar a medida que `n` crece.

En programación competitiva se usa con frecuencia “Big O” para comunicar el orden de crecimiento esperado. Conviene elegir la cota más informativa: aunque un algoritmo `Θ(n^2)` también pertenece a `O(n^3)`, decir `O(n^2)` permite compararlo mejor.

> **Importante:** Big O no significa automáticamente “peor caso”. El peor, mejor y caso promedio describen qué entrada se analiza; `O`, `Ω` y `Θ` indican el tipo de cota aplicada a ese análisis.

## Cómo analizar un algoritmo

### Operaciones consecutivas

Los costos se suman y domina el término de mayor crecimiento:

```text
O(n) + O(n^2) = O(n^2)
```

### Ciclos anidados

Si un ciclo de `n` iteraciones contiene otro de `m`, el trabajo total suele ser `O(nm)`. Si ambos recorren `n` elementos, suele ser `O(n^2)`.

### Reducción del problema

Cuando el tamaño restante se divide por una constante en cada iteración, aparece un logaritmo. La búsqueda binaria pasa de `n` elementos a `n/2`, luego a `n/4` y así sucesivamente, por lo que realiza `O(log n)` iteraciones.

### Condiciones y casos

Para analizar el peor caso de una bifurcación se toma la rama más costosa. Si la elección depende de los datos, también puede ser útil indicar el mejor caso o el costo esperado.

### Recursión

No basta con contar la profundidad. También importa cuántas llamadas se generan en cada nivel. Una recursión que crea dos llamadas sobre `n - 1` puede ser exponencial; una que crea dos llamadas sobre mitades disjuntas puede ser `O(n log n)`.

## Ejemplos de crecimiento

Los ejemplos están almacenados como archivos C++ independientes. La web y el PDF insertan exactamente el mismo código, de modo que no existan versiones diferentes del algoritmo.

### Tiempo constante — `O(1)`

Acceder a una posición conocida de un `vector` no depende de la cantidad total de elementos.

```cpp
--8<-- "snippets/fundamentals/complexity/constant-access.cpp"
```

### Tiempo lineal — `O(n)`

Para encontrar el máximo sin información adicional es necesario inspeccionar todos los elementos.

```cpp
--8<-- "snippets/fundamentals/complexity/linear-maximum.cpp"
```

### Tiempo logarítmico — `O(log n)`

La búsqueda binaria descarta la mitad del intervalo en cada paso. Requiere que el arreglo esté ordenado.

```cpp
--8<-- "snippets/fundamentals/complexity/binary-search.cpp"
```

### Tiempo lineal-logarítmico — `O(n log n)`

Ordenar `n` elementos mediante `std::sort` requiere `O(n log n)` comparaciones.

```cpp
--8<-- "snippets/fundamentals/complexity/sort-values.cpp"
```

### Tiempo cuadrático — `O(n^2)`

Comparar cada elemento con todos los elementos posteriores examina aproximadamente `n(n - 1) / 2` pares.

```cpp
--8<-- "snippets/fundamentals/complexity/equal-pairs.cpp"
```

## Órdenes de crecimiento comunes

| Complejidad | Nombre habitual | Ejemplo |
|---:|---|---|
| `O(1)` | Constante | Acceso por índice |
| `O(log n)` | Logarítmica | Búsqueda binaria |
| `O(n)` | Lineal | Recorrer un arreglo |
| `O(n log n)` | Lineal-logarítmica | Ordenamiento eficiente |
| `O(n^2)` | Cuadrática | Comparar todos los pares |
| `O(n^3)` | Cúbica | Floyd–Warshall |
| `O(2^n)` | Exponencial | Enumerar subconjuntos |
| `O(n!)` | Factorial | Enumerar permutaciones |

El orden de menor a mayor crecimiento es:

```text
O(1) < O(log n) < O(n) < O(n log n) < O(n^2) < O(n^3) < O(2^n) < O(n!)
```

## Relación con las restricciones

La siguiente tabla es una orientación para C++ en problemas con límites de tiempo habituales. No reemplaza el análisis de las constantes, la memoria, el lenguaje ni la máquina utilizada por el juez.

| Tamaño máximo aproximado | Complejidades que suelen considerarse |
|---:|---|
| `n <= 10` | `O(n!)`, dependiendo de la poda |
| `n <= 20` | `O(2^n)` |
| `n <= 500` | `O(n^3)` |
| `n <= 5 000` | `O(n^2)` |
| `n <= 200 000` | `O(n log n)` |
| `n <= 1 000 000` | `O(n)` o `O(n log n)` con constantes pequeñas |

Estas referencias suponen que `n` es la dimensión relevante. Una tabla `O(nm)` debe analizar los máximos de `n` y `m` juntos.

## Complejidad espacial

El análisis de memoria incluye las estructuras auxiliares y la pila de recursión:

- unas pocas variables escalares requieren `O(1)` espacio adicional;
- un arreglo auxiliar de `n` posiciones requiere `O(n)`;
- una matriz de `n * m` requiere `O(nm)`;
- una recursión de profundidad `n` puede consumir `O(n)` en la pila, aunque no cree un arreglo explícito.

También importa el tamaño real de cada elemento. Un vector de un millón de valores `long long` ocupa aproximadamente 8 MB solo para sus datos, mientras que una matriz cuadrada de esa dimensión es inviable.

## Factores que Big O no muestra

Dos soluciones con la misma complejidad pueden tener rendimientos diferentes debido a:

- constantes ocultas;
- acceso a memoria y uso de caché;
- estructuras de datos elegidas;
- costo de entrada y salida;
- recursión, asignaciones dinámicas o funciones de hash;
- optimizaciones del compilador y características del juez.

Primero se elige un orden de crecimiento compatible con las restricciones. Después se optimizan las constantes cuando sea necesario.

## Errores frecuentes

- Analizar solo un ciclo y olvidar trabajo realizado dentro de él.
- Multiplicar ciclos consecutivos en vez de sumar sus costos.
- Suponer que todo ciclo anidado es `O(n^2)` aunque sus límites sean distintos.
- Ignorar el costo de copiar contenedores al pasarlos por valor.
- Confundir `O(log n)` con `O(n)` en un ciclo que divide la variable de control.
- Omitir la memoria usada por la pila recursiva.
- Elegir una complejidad por el nombre del algoritmo sin revisar su implementación concreta.

## Checklist para competencia

1. Identifica todas las variables de entrada y sus valores máximos.
2. Cuenta cuántas veces se ejecuta la operación dominante.
3. Conserva el término que más crece y expresa la complejidad.
4. Analiza por separado el tiempo y la memoria adicional.
5. Comprueba que el peor caso cabe razonablemente en los límites.
6. Revisa constantes importantes, copias y costo de entrada/salida.
