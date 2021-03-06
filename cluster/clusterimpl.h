// Copyright 2020 Andrew Dunstall

#pragma once

#include <memory>
#include <string>
#include <vector>

#include "cluster/cluster.h"
#include "cluster/node.h"

namespace parrotdb {

class ClusterImpl : public Cluster {
 public:
  explicit ClusterImpl(std::vector<std::shared_ptr<Node>> nodes);

  ~ClusterImpl() override = default;

  ClusterImpl(const ClusterImpl&) = delete;
  ClusterImpl& operator=(const ClusterImpl&) = delete;

  ClusterImpl(ClusterImpl&&) = default;
  ClusterImpl& operator=(ClusterImpl&&) = default;

  void Put(const std::vector<uint8_t>& key,
           const std::vector<uint8_t>& value) override;

  void Delete(const std::vector<uint8_t>& key) override;

 private:
  std::vector<std::shared_ptr<Node>> nodes_;
};

}  // namespace parrotdb
