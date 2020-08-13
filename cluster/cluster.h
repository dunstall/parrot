// Copyright 2020 Andrew Dunstall

#pragma once

#include <cstdint>
#include <vector>

namespace parrotdb {

// Cluster module
// - connections pool to replicas
// - failure detection (?)

// TODO(AD) Latest think about SEDA and queues between multiple threads. For
// now just have a simple implementation class.
// TODO(AD) Write shitty impl first then rewrite properly
class Cluster {
 public:
  virtual ~Cluster() {}

  // TODO(AD) Handle quorum and read-repair (request all replicas and take
  // latest from N responses and repair stale)

  virtual void Put(const std::vector<uint8_t>& key,
                   const std::vector<uint8_t>& value) = 0;

  virtual void Delete(const std::vector<uint8_t>& key) = 0;
};

}  // namespace parrotdb
