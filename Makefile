PYTHON ?= python

.PHONY: all verify setup info progress test clean

all verify:
	$(PYTHON) tools/build.py

setup:
	$(PYTHON) tools/bootstrap.py --analysis
	$(PYTHON) tools/compiler_agbcc.py bootstrap
	$(PYTHON) tools/compiler_libgcc.py bootstrap

info:
	$(PYTHON) tools/analyze.py info

progress:
	$(PYTHON) tools/analyze.py progress

test:
	$(PYTHON) -m unittest discover -s tests -v

clean:
	$(PYTHON) tools/clean.py
