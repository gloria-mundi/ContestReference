TESTS = \
	datastructures/test/segmentTree.test \
	datastructures/test/segmentTree2.test \
	datastructures/test/fenwickTree.test \
	datastructures/test/fenwickTree2.test \
	datastructures/test/monotonicConvexHull.test \
	datastructures/test/persistent.test \
	datastructures/test/sparseTable.test \
	datastructures/test/sparseTableDisjoint.test \
	graph/test/binary_lifting.test \
	graph/test/LCA_sparse.test \
	math/test/binomial0.test

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
	rm -f $(TESTS) $(TESTS:.test=.ok) \
		datastructures/test/segmentTree.tmp.cpp \
		datastructures/test/segmentTree2.tmp.cpp

%.ok: %.test
	timeout -v 1 ./$<
	@touch $@
%.test: %.cpp test.h
	g++ -include test.h -std=gnu++20 -Wall -Wextra -Wpedantic -Werror \
		-fsanitize=address,undefined -g -o $@ $<

datastructures/test/segmentTree.test: datastructures/test/segmentTree.cpp \
	datastructures/test/segmentTree.tmp.cpp
datastructures/test/segmentTree.tmp.cpp: datastructures/segmentTree.cpp
	{ sed -e '/OR/,$$d' $< ; echo '};' ; } > $@
datastructures/test/segmentTree2.test: datastructures/test/segmentTree2.cpp \
	datastructures/test/segmentTree2.tmp.cpp
datastructures/test/segmentTree2.tmp.cpp: datastructures/segmentTree.cpp
	sed -e '/void update/,/OR/d' \
	    -e '/remove for range/,/}}/{/}}/!d;s/}}/}/}' $< > $@
datastructures/test/fenwickTree.test: datastructures/test/fenwickTree.cpp \
	datastructures/fenwickTree.cpp
datastructures/test/fenwickTree2.test: datastructures/test/fenwickTree2.cpp \
	datastructures/fenwickTree2.cpp
datastructures/test/monotonicConvexHull.test: \
	datastructures/test/monotonicConvexHull.cpp \
	datastructures/monotonicConvexHull.cpp
datastructures/test/persistent.test: datastructures/test/persistent.cpp \
	datastructures/persistent.cpp
datastructures/test/sparseTable.test: datastructures/test/sparseTable.cpp \
	datastructures/sparseTable.cpp
datastructures/test/sparseTableDisjoint.test: \
	datastructures/test/sparseTableDisjoint.cpp \
	datastructures/sparseTableDisjoint.cpp
graph/test/binary_lifting.test: graph/test/binary_lifting.cpp \
	graph/binary_lifting.cpp graph/test/util.cpp
graph/test/LCA_sparse.test: graph/test/LCA_sparse.cpp \
	graph/LCA_sparse.cpp datastructures/sparseTable.cpp graph/test/util.cpp
math/test/binomial0.test: math/test/binomial0.cpp math/binomial0.cpp \
	math/shortModInv.cpp

FORCE:
.PHONY: all pdf test clean cleanpdf cleantest FORCE
