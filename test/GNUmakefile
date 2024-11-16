
TESTS = $(basename $(shell find . -type f -name '*.cpp'))
CXX = g++ -std=gnu++20 -I ../content/ -O2 -Wall -Wextra -Wshadow -Werror

test: $(TESTS:=.ok)

missing:
	@find ../content -name '*.cpp' | sed 's|^../content/||' \
	  | while read -r f ; do [ -e "$$f" ] || echo "$$f" ; done \
	  | sort > missing.tmp
	@sort missing.ignore | comm -23 missing.tmp -
	@rm missing.tmp

clean:
	rm -f $(TESTS:=.test) $(TESTS:=.ok) $(TESTS:=.d)

%.ok: %.test
	timeout --foreground --verbose 60 prlimit -s$$((1<<32)) ./$<
	@touch $@

%.test: %.cpp
	$(CXX) -o $@ $<

%.d: %.cpp
	$(CXX) -M -MT '$*.test $*.d' -MF $@ $<

.PHONY: test clean
.SECONDARY: $(TESTS:=.test)

include $(TESTS:=.d)
