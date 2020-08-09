// Copyright 2020 Andrew Dunstall

#pragma once

#include <vector>
#include "parrotdb/options.h"

namespace parrotdb {

// Cluster module
// - connections pool to replicas
// - failure detection (?)

class Cluster {
 public:
  Cluster(const ClusterOptions& options) {}

  // TODO(AD) Handle quorum and read-repair (request all replicas and take
  // latest from N responses and repair stale)

  std::optional<std::vector<uint8_t>> Get(const std::vector<uint8_t>& key,
                                          const ReadOptions& options) {
    return std::nullopt;
  }

  void Put(const std::vector<uint8_t>& key, const std::vector<uint8_t>& value,
           const WriteOptions& options) {}

  void Delete(const std::vector<uint8_t>& key, const WriteOptions& options) {}
};

}  // namespace parrotdb
