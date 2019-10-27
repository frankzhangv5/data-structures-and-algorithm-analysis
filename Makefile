###############################################################################
HEADERS := $(wildcard ./include/*/*.h)
SRC_FILES := $(wildcard ./src/*/*.c ./test/*.c)
###############################################################################
C_FLAGS := -g -Wall -O0 -fprofile-arcs -ftest-coverage
C_INCLUDES := ./include
###############################################################################
BINARY := test_main
###############################################################################
all: deps format $(BINARY)

%:%.c
	gcc -o $@ $<

test_main:
	gcc $(C_FLAGS) -I$(C_INCLUDES) -o $@ $(SRC_FILES) -lcunit -lncurses
###############################################################################
.PHONY: deps
deps:
	@echo "checking deps..."
	@which clang-format || sudo apt-get install clang-format
	@which valgrind || sudo apt-get install valgrind
	@which lcov || sudo apt-get install lcov
	@which genhtml || sudo apt-get install genhtml
	@ldconfig -p|grep cunit || sudo apt-get install libcunit1 libcunit1-dev
###############################################################################
.PHONY: format
format:
	@echo "formating..."
	@clang-format -i $(SRC_FILES) $(HEADERS)
###############################################################################
.PHONY: test
test: $(BINARY)
	@echo "test..."
	@./$(BINARY)
###############################################################################
define coverage
lcov -d . -t '$(1)' -o 'test.info' -b . -c
genhtml -o coverage_$(1) test.info
endef

.PHONY: cov
cov:test
	@echo "coverage testing..."
	@$(call coverage,test_main)
	@echo "done."

###############################################################################
define mem_check
valgrind --tool=memcheck --leak-check=full --show-reachable=yes ./$(1)
endef

.PHONY: memcheck
memcheck:$(BINARY)
	@echo "memchecking..."
	@$(call mem_check,$(BINARY))
	@echo "done."
###############################################################################
.PHONY: wc
wc:
	@wc -l $(HEADERS) $(SRC_FILES)

.PHONY: clean
clean:
	@rm -rf coverage_*
	@rm -rf $(BINARY) *.gcno *.gcda test.info
