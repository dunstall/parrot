.PHONY: format
format:
	find . \( -name "*.cc" -o -name "*.h" \) -not -path "./third-party/*"  | xargs clang-format -i --style=Google
	buildifier -r .

.PHONY: analyze
analyze:
	# Requires cpplint (pip3 install cpplint)
	# TODO(AD) use clang-tidy
	cpplint --recursive --exclude=third-party/ --filter=-build/c++11,-whitespace/parens,-whitespace/line_length,-whitespace/braces .
