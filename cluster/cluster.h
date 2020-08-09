// Copyright 2020 Andrew Dunstall

#pragma once

#include <vector>

namespace parrotdb {

// Cluster module
// - connections pool to replicas
// - failure detection (?)

class Cluster {
 public:
  virtual ~Cluster() {}

  // TODO(AD) Handle quorum and read-repair (request all replicas and take
  // latest from N responses and repair stale)

  virtual std::optional<std::vector<uint8_t>> Get(
      const std::vector<uint8_t>& key) = 0;

  virtual void Put(const std::vector<uint8_t>& key,
                   const std::vector<uint8_t>& value) = 0;

  virtual void Delete(const std::vector<uint8_t>& key) = 0;
};

}  // namespace parrotdb
