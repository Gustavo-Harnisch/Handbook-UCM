# Complemento UTFSM: algoritmos avanzados de strings

## KMP

`kmp_search(text, pattern)` devuelve todos los índices de inicio de coincidencias, incluso solapadas, en `O(|text| + |pattern|)`. El patrón vacío devuelve una lista vacía por decisión explícita de la interfaz.

> **Crédito UTFSM:** Gabriel Carmona contribuyó la implementación de referencia en el Handbook UTFSM.

```cpp
--8<-- "snippets/strings/kmp.cpp"
```

## Aho-Corasick

Busca múltiples patrones simultáneamente en tiempo lineal respecto al texto más las coincidencias. Esta implementación acepta solamente letras minúsculas `a`–`z`; agrega patrones, llama una vez a `build` y luego a `search`. Cada resultado contiene `(índice final, id_del_patron)`.

> **Crédito UTFSM:** Sebastián Torrealba contribuyó la implementación de referencia en el Handbook UTFSM.

```cpp
--8<-- "snippets/strings/aho-corasick.cpp"
```

## Suffix array y LCP

`suffix_array` ordena los sufijos en `O(N log^2 N)` y `lcp_array` calcula los LCP adyacentes en `O(N)`. Ambos aceptan cualquier byte de `std::string`; para texto vacío devuelven vectores vacíos.

> **Crédito UTFSM:** Sebastián Torrealba contribuyó la implementación de referencia en el Handbook UTFSM.

```cpp
--8<-- "snippets/strings/suffix-array.cpp"
```

## Manacher

Calcula radios de palíndromos pares e impares en `O(N)`. En `odd_palindrome_radii`, el radio incluye el centro; en `even_palindrome_radii`, indica cuántos caracteres se extienden a cada lado del corte.

> **Crédito UTFSM:** Sebastián Torrealba contribuyó la implementación de referencia en el Handbook UTFSM.

```cpp
--8<-- "snippets/strings/manacher.cpp"
```
