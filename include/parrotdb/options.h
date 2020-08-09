// Copyright 2020 Andrew Dunstall

#pragma once

namespace parrotdb {

struct ClusterOptions {};

struct StoreOptions {
  StoreOptions(bool _dev = false) : dev{_dev} {}

  bool dev = false;
};

struct ReadOptions {};

struct WriteOptions {};

}  // namespace parrotdb
