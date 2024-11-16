LATEXMK = latexmk -interaction=nonstopmode

tcr.pdf: FORCE
	cd content && $(LATEXMK)

tcr-opt.pdf: FORCE
	cd content && $(LATEXMK) -r latexmk.opt

pdf: tcr.pdf tcr-opt.pdf

all: pdf test

test:
	+gmake -C test

clean: cleanpdf cleantest

cleanpdf:
	cd content && $(LATEXMK) -C
	cd content && $(LATEXMK) -r latexmk.opt -C

cleantest:
	+-gmake -C clean

FORCE:
.PHONY: all pdf test clean cleanpdf cleantest FORCE
