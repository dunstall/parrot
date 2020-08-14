#!/bin/bash

if ! [[ "${0}" =~ "functional/build.sh" ]]; then
  echo "must be run from parrotdb/"
  exit 1
fi

bazel build //functional:functional-test
cp ./bazel-bin/functional/functional-test functional-test
docker build . -f functional/Dockerfile -t parrotdb-functional
rm -f functional-test

docker run --rm parrotdb-functional
