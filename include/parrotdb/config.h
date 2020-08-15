// Copyright 2020 Andrew Dunstall

#pragma once

#include <string>
#include <vector>

namespace parrotdb {

struct Config {
  std::string addr;
  std::vector<std::string> cluster;
  bool verbose;
};

}  // namespace parrotdb
