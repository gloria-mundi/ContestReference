
LATEXMK = latexmk -interaction=nonstopmode

tcr.pdf: FORCE
	$(LATEXMK) -pdf tcr

pdf: tcr.pdf tcr-opt.pdf

tcr-opt.pdf: FORCE
	$(LATEXMK) -pdf -jobname=tcr-opt -usepretex="\def\OPTIONAL{}" tcr

all: pdf test

test:
	+gmake -f TestMakefile

clean: cleanpdf cleantest

cleanpdf:
	$(LATEXMK) -C tcr
	$(LATEXMK) -C -jobname=tcr-opt tcr
	rm -f *.thm

cleantest:
	+-gmake -f TestMakefile cleantest

FORCE:
.PHONY: all pdf test clean cleanpdf cleantest FORCE
