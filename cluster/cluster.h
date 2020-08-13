// Copyright 2020 Andrew Dunstall

#pragma once

#include <cstdint>
#include <vector>

namespace parrotdb {

// TODO(AD) Handle quorum and read-repair (request all replicas and take
// latest from N responses and repair stale)
class Cluster {
 public:
  virtual ~Cluster() {}

  virtual void Put(const std::vector<uint8_t>& key,
                   const std::vector<uint8_t>& value) = 0;

  virtual void Delete(const std::vector<uint8_t>& key) = 0;
};

}  // namespace parrotdb
