# Ejecutar el proyecto localmente

Esta guía muestra cómo abrir el handbook con MkDocs y cómo generar su PDF con Pandoc.

## Preparación inicial

### 1. Instalar las herramientas

En Ubuntu o Debian, ejecuta:

```bash
sudo apt update
sudo apt install python3 python3-venv python3-pip pandoc texlive-xetex texlive-fonts-recommended make
```

### 2. Preparar Python

Desde la carpeta principal del proyecto:

```bash
python3 -m venv .venv
source .venv/bin/activate
python -m pip install -r requirements.txt
```

Esta preparación se realiza una sola vez.

## Abrir MkDocs en el navegador

Cada vez que quieras trabajar en la documentación, ejecuta:

```bash
source .venv/bin/activate
mkdocs serve
```

Después, abre esta dirección:

<http://127.0.0.1:8000/>

Los cambios se mostrarán automáticamente al guardar un archivo. Para cerrar el servidor, presiona `Ctrl+C`.

## Generar el PDF con Pandoc

Ejecuta desde la carpeta principal del proyecto:

```bash
make pdf
```

El PDF se guardará en:

```text
dist/UCM-Competitive-Programming-Handbook.pdf
```

El orden de los capítulos se obtiene automáticamente desde `nav` en `mkdocs.yml`. La presentación del documento se configura en `pandoc/metadata.yaml`.

## Agregar una página nueva

Cuando agregues un archivo Markdown nuevo:

1. Guárdalo dentro de `content/`.
2. Si contiene código, guarda la implementación en la ruta equivalente dentro de `snippets/`.
3. Agrégalo a `nav` en `mkdocs.yml` para que aparezca, en el mismo orden, en la web y en el PDF.

Revisa `STRUCTURE.md` para elegir la categoría y subcategoría correspondientes.

## Comandos principales

| Comando | Acción |
| --- | --- |
| `mkdocs serve` | Abre la web local para trabajar. |
| `make web` | Genera la web en `dist/site/`. |
| `make pdf` | Genera el PDF en `dist/`. |
| `make all` | Genera la web y el PDF. |
| `make clean` | Elimina los archivos generados. |

> **Importante:** edita los archivos de `content/`, no los archivos generados dentro de `dist/`.
