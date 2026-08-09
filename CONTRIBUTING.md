# Contribuir al Handbook UCM

El handbook separa contenido, código y construcción para mantener una sola fuente de verdad y evitar implementaciones duplicadas.

## Elegir una plantilla

- Usa `templates/concept.md` para fundamentos teóricos, técnicas y referencias.
- Usa `templates/algorithm.md` para algoritmos y estructuras de datos con implementación.

Copia la plantilla a la categoría correspondiente dentro de `content/` y reemplaza todas sus instrucciones.

## Agregar un algoritmo

1. Guarda la implementación en `snippets/<categoria>/<algoritmo>.cpp`.
2. Crea la explicación en `content/<categoria>/<algoritmo>.md`.
3. Incluye el código desde el Markdown:

   ````markdown
   ```cpp
   --8<-- "snippets/<categoria>/<algoritmo>.cpp"
   ```
   ````

4. Agrega la página una sola vez a `nav` en `mkdocs.yml`. Esa posición se utilizará en la web y en el PDF.
5. Ejecuta `make check` y `make pdf`.

Antes de crear una categoría nueva, revisa [STRUCTURE.md](STRUCTURE.md). Las carpetas reservadas contienen `.gitkeep`; reemplázalo o elimínalo cuando se agregue el primer archivo real de esa subsección.

## Responsabilidad de cada directorio

| Directorio | Contiene | No debería contener |
|---|---|---|
| `content/` | Explicaciones, contratos, análisis y enlaces | Copias de implementaciones completas |
| `snippets/` | Código C++ compilable | Explicaciones extensas del capítulo |
| `templates/` | Estructura editorial reutilizable | Contenido publicado |
| `scripts/` | Automatización de construcción y validación | Algoritmos del handbook |
| `dist/` | Resultados generados | Archivos fuente editados manualmente |

## Estándar editorial

Cada capítulo debe permitir que el lector responda rápidamente:

- qué problema resuelve;
- qué condiciones exige;
- cuál es su complejidad temporal y espacial;
- cómo se usa la implementación;
- qué casos límite pueden hacerla fallar.

Define todos los símbolos utilizados en el análisis. Distingue una cota asintótica de una estimación práctica y evita presentar límites de entrada aproximados como garantías.

## Estándar para C++

- Compatibilidad con C++17.
- Una implementación o ejemplo principal por archivo.
- Nombres descriptivos y ausencia de macros personales.
- Tipos numéricos adecuados para los límites documentados.
- Indexación, precondiciones y resultado explicados en el capítulo.
- Sin una segunda copia del código dentro de `content/`.

`make code-check` compila sintácticamente todos los archivos `.cpp` de `snippets/` con advertencias habilitadas.

## Migrar código desde UTFSM

Al trasladar una implementación desde el handbook de la UTFSM:

1. conserva el aviso de licencia y el reconocimiento del proyecto;
2. registra en `snippets/ATTRIBUTION.md` el archivo de origen y la persona acreditada por UTFSM; si el archivo no indica autor, usa el historial del repositorio y aclara que es la persona que lo incorporó;
3. muestra ese crédito junto al snippet en su página Markdown;
4. revisa el código en vez de copiarlo de forma mecánica;
5. elimina dependencias implícitas, macros personales y alias no definidos;
6. documenta su contrato y complejidad;
7. valida que compile como snippet independiente;
8. registra cambios funcionales relevantes en la explicación.
