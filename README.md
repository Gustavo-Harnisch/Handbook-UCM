# 📚 UCM Competitive Programming Handbook

![Banner del UCM Competitive Programming Handbook](content/assets/banner.png)

Handbook de programación competitiva desarrollado por estudiantes de la Universidad Católica del Maule (UCM).

## Formatos

- **Web:** <https://gustavo-harnisch.github.io/Handbook-UCM/>
- **PDF:** se publica junto con el sitio y también puede generarse localmente.

El contenido de ambos formatos proviene de los mismos archivos Markdown. Los códigos viven una sola vez en `snippets/` y se insertan tanto en MkDocs como en Pandoc.

El reconocimiento de ese material está en `snippets/ATTRIBUTION.md`.

## Estructura

```text
content/             Partes y capítulos publicados del handbook
content/assets/      Recursos compartidos de la web y la documentación (banner, estilos, etc.)
snippets/            Implementaciones y ejemplos C++ futuros
_drafts/             Material conservado fuera de la publicación
templates/           Plantillas para conceptos y algoritmos
pandoc/              Presentación y metadatos del PDF
scripts/             Construcción y validaciones
mkdocs.yml           Índice maestro y configuración web
```

El orden declarado en `mkdocs.yml` también determina el orden de los capítulos del PDF. De este modo, no hay que mantener dos índices manuales.

Los recursos visuales y de estilo se mantienen únicamente en `content/assets/`. El sitio MkDocs los usa con rutas relativas a `content/` y este README los referencia como `content/assets/...`; al actualizar un recurso, ambos consumen el mismo archivo.

La estructura completa está documentada en [STRUCTURE.md](STRUCTURE.md).

## Desarrollo local

Requisitos principales: Python 3, Pandoc, XeLaTeX, GNU Make y un compilador compatible con C++17.

```bash
python3 -m venv .venv
source .venv/bin/activate
python -m pip install -r requirements.txt
make check
make pdf
```

Comandos disponibles:

| Comando | Acción |
| --- | --- |
| `make web` | Genera la web en `dist/site/` |
| `make pdf` | Genera el PDF en `dist/` |
| `make code-check` | Valida todos los snippets C++ |
| `make check` | Valida el código y construye la web en modo estricto |
| `make all` | Construye la web y el PDF |

Consulta [CONTRIBUTING.md](CONTRIBUTING.md) antes de agregar o migrar contenido.

## Reconocimientos

Este proyecto utiliza como base y referencia el **USM Competitive Programming Handbook**, desarrollado por la comunidad de Programación Competitiva de la Universidad Técnica Federico Santa María (UTFSM).

[Repositorio original](https://github.com/ProgramacionCompetitivaUTFSM/Handbook-USM)

Agradecemos a sus autores y colaboradores por compartir su trabajo con la comunidad. El proyecto original está distribuido bajo licencia MIT.

## Licencia

Este proyecto está distribuido bajo la licencia MIT. Consulta [LICENCE](LICENCE) para más información.
