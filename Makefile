TESTS = \
	datastructures/test/fenwickTree.test \
	datastructures/test/fenwickTree2.test \
	datastructures/test/monotonicConvexHull.test \
	datastructures/test/persistent.test \
	graph/test/binary_lifting.test \
	graph/test/LCA_sparse.test

LATEXMK = latexmk -interaction=nonstopmode

tcr.pdf: FORCE
	$(LATEXMK) -pdf tcr

pdf: tcr.pdf tcr-opt.pdf

tcr-opt.pdf: FORCE
	$(LATEXMK) -pdf -jobname=tcr-opt -usepretex="\def\OPTIONAL{}" tcr

all: pdf test

test: $(TESTS:.test=.ok)

clean: cleanpdf cleantest

cleanpdf:
	$(LATEXMK) -C tcr
	$(LATEXMK) -C -jobname=tcr-opt tcr
	rm -f *.thm

cleantest:
	rm -f $(TESTS) $(TESTS:.test=.ok)

%.ok: %.test
	timeout -v 1 ./$<
	@touch $@
%.test: %.cpp test.h
	g++ -include test.h -std=gnu++20 -Wall -Wextra -Wpedantic -Werror \
		-fsanitize=address,undefined -g -o $@ $<

datastructures/test/fenwickTree.test: datastructures/test/fenwickTree.cpp \
	datastructures/fenwickTree.cpp
datastructures/test/fenwickTree2.test: datastructures/test/fenwickTree2.cpp \
	datastructures/fenwickTree2.cpp
datastructures/test/monotonicConvexHull.test: \
	datastructures/test/monotonicConvexHull.cpp \
	datastructures/monotonicConvexHull.cpp
datastructures/test/persistent.test: datastructures/test/persistent.cpp \
	datastructures/persistent.cpp
graph/test/binary_lifting.test: graph/test/binary_lifting.cpp \
	graph/binary_lifting.cpp graph/test/util.cpp
graph/test/LCA_sparse.test: graph/test/LCA_sparse.cpp \
	graph/LCA_sparse.cpp datastructures/sparseTable.cpp graph/test/util.cpp

FORCE:
.PHONY: all pdf test clean cleanpdf cleantest FORCE
