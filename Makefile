DAYS := $(shell seq 1 23)
PROBLEMS := $(foreach day,$(DAYS),$(day)a $(day)b)
EXAMPLES := $(foreach day,$(DAYS),$(day)a_example $(day)b_example)

%/a.c :
	@mkdir $* 2> /dev/null || true
	@cp template.c $@

%/b.c :
	@mkdir $* 2> /dev/null || true
	@cp template.c $@

build/%a : %/a.c aoc.c
	@mkdir build/ 2> /dev/null || true
	@gcc -Wall -Werror aoc.c $< -o $@

build/%b : %/b.c aoc.c
	@mkdir build/ 2> /dev/null || true
	@gcc -Wall -Werror aoc.c $< -o $@

%a : build/%a %/input
	@echo -n "$@: "
	@$< $*/input

%b : build/%b %/input
	@echo -n "$@: "
	@$< $*/input

%a_example : build/%a %/example
	@echo -n "$@: "
	@$< $*/example

%b_example : build/%b %/example
	@echo -n "$@: "
	@$< $*/example

%/input :
	@echo "Enter input for day $*:"
	@cat > $@

%/example :
	@echo "Enter example for day $*:"
	@cat > $@

.PRECIOUS: %/a.c %/b.c %/input %/example build/%a build/%b

.PHONY: examples all clean

all: $(PROBLEMS)

examples: $(EXAMPLES)

clean:
	@rm -r build
