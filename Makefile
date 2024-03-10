TESTS = \
	datastructures/test/fenwickTree.test \
	datastructures/test/fenwickTree2.test \
	graph/test/binary_lifting.test \
	graph/test/LCA_sparse.test

pdf:
	latexmk -pdf tcr

all: pdf test

test: $(TESTS:.test=.ok)

clean: cleanpdf cleantest

cleanpdf:
	latexmk -c tcr
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
graph/test/binary_lifting.test: graph/test/binary_lifting.cpp \
	graph/binary_lifting.cpp graph/test/util.cpp
graph/test/LCA_sparse.test: graph/test/LCA_sparse.cpp \
	graph/LCA_sparse.cpp datastructures/sparseTable.cpp graph/test/util.cpp

.PHONY: all pdf test clean cleanpdf cleantest
