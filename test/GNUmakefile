
TESTS = $(basename $(shell find . -path ./awk -prune -o -type f -name '*.cpp' -print))
AWK = $(basename $(shell find . -type f -name '*.awk'))
CXX = g++ -std=gnu++20 -I awk/ -I ../content/ -O2 -Wall -Wextra -Wshadow -Werror
SAN = -fsanitize=address,undefined -DSANITIZE
TIMEOUT = 5m

test: $(TESTS:=.ok) $(TESTS:=.san.ok)

missing:
	@find ../content -name '*.cpp' | sed 's|^../content/||' \
	  | while read -r f ; do [ -e "$$f" ] || echo "$$f" ; done \
	  | sort > missing.tmp
	@sort missing.ignore | comm -3 missing.tmp -
	@rm missing.tmp

clean:
	rm -f $(TESTS:=.test) $(TESTS:=.ok) $(TESTS:=.san.ok) $(TESTS:=.d)
	rm -rf awk/

%.ok: %.test
	timeout --foreground --verbose $(TIMEOUT) prlimit -s$$((1<<32)) ./$<
	@touch $@

%.test: %.cpp
	$(CXX) -o $@ $<

%.san.test: %.cpp
	$(CXX) $(SAN) -o $@ $<

awk/%: %.awk ../content/%
	@mkdir -p $(dir $@)
	awk -f $*.awk < ../content/$* > $@

%.d: %.cpp $(addprefix awk/,$(AWK))
	$(CXX) -M -MP -MT '$*.test $*.san.test $*.d' -MF $@ $<

.PHONY: test clean
.SECONDARY: $(TESTS:=.test) $(addprefix awk/,$(AWK))

include $(TESTS:=.d)
