.PHONY: web pdf code-check check all clean

web:
	./scripts/build-web.sh

pdf:
	./scripts/build-pdf.sh

code-check:
	./scripts/check-code.sh

check: code-check
	./scripts/build-web.sh --strict

all: web pdf

clean:
	rm -rf dist/site dist/.build dist/UCM-Competitive-Programming-Handbook.pdf
