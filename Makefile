# Copyright 2020 Andrew Dunstall

# TODO(AD) Read https://www.gnu.org/software/make/manual/html_node/.
# TODO(AD) Also see rocksdb makefile and other examples

INC_DIR := include
OBJ_DIR := build

INC_FLAGS := -Iinclude -I.

CPPFLAGS := -std=c++17 -Wall -Werror

SRC := $(filter-out %_test.cc,$(wildcard */*.cc))
TEST := $(wildcard */*_test.cc)
OBJ := $(patsubst %.cc,$(OBJ_DIR)/%.o,$(SRC))
OBJ_TEST := $(patsubst %.cc,$(OBJ_DIR)/test/%.o,$(TEST))

.PHONY: all
all: $(OBJ)
	ar -rv parrotdb.a $(OBJ)

$(OBJ_DIR)/%.o: %.cc
	mkdir -p $(shell dirname $@)
	$(CXX) $(CPPFLAGS) $(INC_FLAGS) -c -o $@ $<

GTEST := third-party/googletest
TEST_INC_FLAGS := -I$(GTEST)/googletest/include
TEST_LD_FLAGS := -L$(GTEST)/build/lib -lgtest -lgtest_main -lpthread

.PHONY: check
check: all $(OBJ_TEST)
	$(CXX) $(CPPFLAGS) $(OBJ) $(OBJ_TEST) -o gtest.out $(TEST_LD_FLAGS)
	./gtest.out

$(OBJ_DIR)/test/%.o: %.cc
	mkdir -p $(shell dirname $@)
	$(CXX) $(CPPFLAGS) $(INC_FLAGS) $(TEST_INC_FLAGS) -c -o $@ $<

.PHONY: format
format:
	find . -name "*.h" | xargs clang-format -i --style=Google
	find . -name "*.cc" | xargs clang-format -i --style=Google

.PHONY: analyze
analyze:
	# Requires cpplint (pip3 install cpplint)
	# TODO(AD) use clang-tidy
	cpplint --recursive --exclude=lib/ --filter=-build/c++11,-whitespace/parens,-whitespace/line_length,-whitespace/braces .

.PHONY: clean
clean:
	rm -rf $(OBJ_DIR)
