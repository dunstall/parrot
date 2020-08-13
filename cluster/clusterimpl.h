// Copyright 2020 Andrew Dunstall

#pragma once

#include <string>
#include <vector>

#include "cluster/cluster.h"
#include "cluster/node.h"

namespace parrotdb {

class ClusterImpl : public Cluster {
 public:
  ClusterImpl(const std::vector<std::string>& nodes);
  ~ClusterImpl() override {}

  void Put(const std::vector<uint8_t>& key,
           const std::vector<uint8_t>& value) override;

  void Delete(const std::vector<uint8_t>& key) override;

 private:
  std::vector<Node> nodes_;
};

}  // namespace parrotdb
