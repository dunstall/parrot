// Copyright 2020 Andrew Dunstall

#include "cluster/clusterimpl.h"

#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "cluster/nodeerror.h"
#include "spdlog/spdlog.h"

namespace parrotdb {

ClusterImpl::ClusterImpl(std::vector<std::shared_ptr<Node>> nodes)
    : nodes_{std::move(nodes)} {}

void ClusterImpl::Put(const std::vector<uint8_t>& key,
                      const std::vector<uint8_t>& value) {
  for (auto& node : nodes_) {
    try {
      node->Put(key, value);
      spdlog::debug("replicated PUT to node {}", node->addr());
    } catch (const NodeError& e) {
      spdlog::warn("failed to replicate PUT to node {}: {}", node->addr(),
                   e.what());
    }
  }
}

void ClusterImpl::Delete(const std::vector<uint8_t>& key) {
  for (auto& node : nodes_) {
    try {
      node->Delete(key);
      spdlog::debug("replicated DELETE to node {}", node->addr());
    } catch (const NodeError& e) {
      spdlog::warn("failed to replicate DELETE to node {}: {}", node->addr(),
                   e.what());
    }
  }
}

}  // namespace parrotdb
