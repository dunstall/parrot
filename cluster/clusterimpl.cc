// Copyright 2020 Andrew Dunstall

#include "cluster/clusterimpl.h"

#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace parrotdb {

ClusterImpl::ClusterImpl(const std::vector<std::shared_ptr<Node>>& nodes)
    : nodes_{std::move(nodes)} {}

void ClusterImpl::Put(const std::vector<uint8_t>& key,
                      const std::vector<uint8_t>& value) {
  for (auto& node : nodes_) {
    // TODO(AD) Handle errors
    node->Put(key, value);
  }
}

void ClusterImpl::Delete(const std::vector<uint8_t>& key) {
  for (auto& node : nodes_) {
    // TODO(AD) Handle errors
    node->Delete(key);
  }
}

}  // namespace parrotdb
