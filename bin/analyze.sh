#!/bin/bash

echo "Running analyze..."
# TODO(AD) clang-tidy
cpplint --recursive --exclude=third-party/ --filter=-build/c++11,-whitespace/parens,-whitespace/line_length,-whitespace/braces .
