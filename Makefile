.PHONY: format
format:
	find . -name "*.h" | xargs clang-format -i --style=Google
	find . -name "*.cc" | xargs clang-format -i --style=Google
	buildifier -r .

.PHONY: analyze
analyze:
	cpplint --recursive --exclude=lib/ --filter=-build/c++11,-whitespace/parens,-whitespace/line_length,-whitespace/braces .
