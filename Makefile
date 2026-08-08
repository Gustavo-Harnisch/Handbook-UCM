.PHONY: web pdf all clean

web:
	./scripts/build-web.sh

pdf:
	./scripts/build-pdf.sh

all: web pdf

clean:
	rm -rf dist/site dist/UCM-Competitive-Programming-Handbook.pdf
