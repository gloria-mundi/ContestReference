TESTS = graph/test/binary_lifting.test

pdf:
	latexmk -pdf tcr

all: pdf test

test: $(TESTS:.test=.ok)

clean:
	latexmk -c tcr
	rm -f *.thm
	rm -f $(TESTS) $(TESTS:.test=.ok)

%.ok: %.test
	timeout -v 1 ./$<
	@touch $@
%.test: %.cpp
	g++ -std=gnu++20 -Wall -Wextra -Wpedantic -Werror \
		-fsanitize=address,undefined -g -o $@ $<

graph/test/binary_lifting.test: graph/test/binary_lifting.cpp \
	graph/binary_lifting.cpp

.PHONY: all pdf test clean
