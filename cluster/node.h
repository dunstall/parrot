// Copyright 2020 Andrew Dunstall

#pragma once

#include <string>
#include <vector>

namespace parrotdb {

class Node {
 public:
  virtual ~Node() {}

  virtual void Put(const std::vector<uint8_t>& key,
                   const std::vector<uint8_t>& value) = 0;

  virtual void Delete(const std::vector<uint8_t>& key) = 0;
};

}  // namespace parrotdb
