###############################################################################
HEADERS := $(wildcard ./include/*/*.h)
SRC_FILES := $(wildcard ./src/*/*.c ./test/*.c)
OS := $(shell uname)
###############################################################################
C_FLAGS := -g -Wall -O0 -std=c99
C_INCLUDES := ./include
###############################################################################
GCOV_FLAGS := -fprofile-arcs -ftest-coverage
GCOV_OUT := ./gcov_out
GCOV_BINARY := gcov_tester
GCOV_SRCS := $(subst ./, ../, $(SRC_FILES))
###############################################################################
BINARY := tester
###############################################################################
all: deps format $(BINARY)

%:%.c
	gcc -o $@ $<

$(BINARY):format
	gcc $(C_FLAGS) -I$(C_INCLUDES) -o $@ $(SRC_FILES) -lcunit -lncurses

$(GCOV_BINARY):format
	rm -rf $(GCOV_OUT)
	mkdir $(GCOV_OUT) && cd $(GCOV_OUT) && gcc $(C_FLAGS) $(GCOV_FLAGS) -I../$(C_INCLUDES) -o $@ $(GCOV_SRCS) -lcunit -lncurses
###############################################################################
.PHONY: deps

deps:
	@echo "checking deps..."
ifeq ($(OS), Darwin)
	@# on mac
	@which clang-format || brew install clang-format
	@# @which valgrind || brew install --HEAD valgrind
	@which lcov || brew install lcov
	@which genhtml || brew  install genhtml
	@ls /usr/local/include/CUnit/CUnit.h 2>/dev/null || brew  install cunit
else
	@# on debain linux
	@which clang-format || sudo apt-get install clang-format
	@which valgrind || sudo apt-get install valgrind
	@which lcov || sudo apt-get  install lcov
	@which genhtml || sudo apt-get install genhtml
	@ldconfig -p|grep cunit || sudo apt-get  install libcunit1 libcunit1-dev
endif
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
cd $(GCOV_OUT) && ./$(1) && lcov -d . -t '$(1)' -o '$(1).info' -b . -c && genhtml -o report $(1).info
endef

.PHONY: cov
cov:$(GCOV_BINARY)
	@echo "coverage testing..."
	@$(call coverage,$(GCOV_BINARY))
	@echo "success ! coverage report at: $(GCOV_OUT)/report/index.html"

###############################################################################
ifeq ($(OS), Darwin)
# on mac
define mem_check
	@echo "valgrind still not available yet!"
endef
else
# on debain linux
define mem_check
	valgrind --tool=memcheck --leak-check=full --show-reachable=yes ./$(1)
endef
endif

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
	@rm -rf $(GCOV_OUT) $(BINARY) *.DSYM
