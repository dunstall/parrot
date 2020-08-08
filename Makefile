OBJ_DIR := build

INC_FLAGS := -Iinclude
CPPFLAGS := -std=c++17

DB_SRC_DIR := db
DB_SRC := $(wildcard $(DB_SRC_DIR)/*.cc)
DB_OBJ_DIR := $(OBJ_DIR)/db
DB_OBJ := $(patsubst $(DB_SRC_DIR)/%.cc,$(DB_SRC_DIR)/%.o,$(DB_SRC))

.PHONY: db
db: $(DB_OBJ_DIR)
	# TODO(AD) Do properly
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(INC_FLAGS) -c -o $(DB_OBJ_DIR)/db.o $(DB_SRC_DIR)/db.cc

.PHONY: format
fmt:
	find . -name "*.h" | xargs clang-format -i --style=Google
	find . -name "*.cc" | xargs clang-format -i --style=Google

.PHONY: analyze
analyze:
	cpplint --recursive --exclude=lib/ --filter=-build/c++11,-whitespace/parens,-whitespace/line_length,-whitespace/braces .

.PHONY: coverage
# TODO(AD) Use gcov

.PHONY: check
# TODO(AD) Check

# TODO(AD) static_lib shared_lib all debug(volatile logging and ggdb)

$(DB_OBJ_DIR):
	mkdir -p $@

.PHONY: clean
clean:
	$(RM) -r $(OBJ_DIR)
