// Copyright 2020 Andrew Dunstall

#include "cluster/clusterimpl.h"

#include <string>
#include <vector>

namespace parrotdb {

ClusterImpl::ClusterImpl(const std::vector<std::string>& nodes) : nodes_{} {
  // for (const auto& addr : nodes) {
  // nodes_.push_back(Node(addr));
  // }
}

void ClusterImpl::Put(const std::vector<uint8_t>& key,
                      const std::vector<uint8_t>& value) {
  for (auto& node : nodes_) {
    node.Put(key, value);
  }
}

void ClusterImpl::Delete(const std::vector<uint8_t>& key) {
  for (auto& node : nodes_) {
    node.Delete(key);
  }
}

}  // namespace parrotdb
