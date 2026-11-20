BASICGOL_DIR ?= .deps/BASICGOL
examples := $(sort $(patsubst %/,%,$(dir $(wildcard */*.c))))
ifeq ($(OS),Windows_NT)
ext := .exe
else
examples := $(filter-out snake,$(examples))
endif

.PHONY: all $(examples)
all: $(examples)
$(examples): %: build/%$(ext)

# Link sources by example, not by file (maze has four translation units).
define example_rule
build/$(1)$(ext): $(wildcard $(1)/*.c $(1)/*.h) $(BASICGOL_DIR)/include/basicgol.h | build
	$$(CC) $$(CPPFLAGS) -I"$$(BASICGOL_DIR)/include" $$(CFLAGS) -std=c11 $$(filter %.c,$$^) $$(LDFLAGS) -lm -o $$@
endef
$(foreach example,$(examples),$(eval $(call example_rule,$(example))))

build:
	mkdir -p $@

.PHONY: check
check: all
	sh tests/smoke.sh
