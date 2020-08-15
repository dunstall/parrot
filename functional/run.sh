#!/bin/bash

if ! [[ "${0}" =~ "run.sh" ]]; then
  echo "must be run from parrotdb/functional/"
  exit 1
fi

bazel build //functional:functional-test
cp ../bazel-bin/functional/functional-test ../functional-test
docker-compose up --build
# docker build . -f functional/Dockerfile -t parrotdb-functional
rm -f ../functional-test

# docker network create parrotdb
# docker run --rm -it --network parrotdb parrotdb-functional
