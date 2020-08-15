#!/bin/bash

echo "Running clang-format..."
find . \( -name "*.cc" -o -name "*.h" \) | xargs clang-format -i --style=Google

echo "Running buildifier..."
buildifier -r .
