#!/bin/bash

echo "Running clang-tidy..."
clang-tidy -header-filter=.* -extra-arg=-std=c++17 -fix **/*.cc -- -I. -Iinclude

echo "Running analyze..."
cpplint --recursive --exclude=third-party/ --filter=-build/c++11,-whitespace/parens,-whitespace/line_length,-whitespace/braces .
