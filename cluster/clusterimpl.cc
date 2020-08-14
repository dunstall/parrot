// Copyright 2020 Andrew Dunstall

#include "cluster/clusterimpl.h"

#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "cluster/nodeerror.h"

namespace parrotdb {

ClusterImpl::ClusterImpl(const std::vector<std::shared_ptr<Node>>& nodes)
    : nodes_{std::move(nodes)} {}

void ClusterImpl::Put(const std::vector<uint8_t>& key,
                      const std::vector<uint8_t>& value) {
  for (auto& node : nodes_) {
    try {
      node->Put(key, value);
    } catch (const NodeError& e) {
      // TODO(AD) Log
    }
  }
}

void ClusterImpl::Delete(const std::vector<uint8_t>& key) {
  for (auto& node : nodes_) {
    try {
      node->Delete(key);
    } catch (const NodeError& e) {
      // TODO(AD) Log
    }
  }
}

}  // namespace parrotdb
