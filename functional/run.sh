#!/bin/bash

if ! [[ "${0}" =~ "run.sh" ]]; then
  echo "must be run from parrotdb/functional/"
  exit 1
fi

bazel build //functional:functional-test
rm -f ../functional-test.out
cp ../bazel-bin/functional/functional-test ../functional-test.out
docker-compose up --build
