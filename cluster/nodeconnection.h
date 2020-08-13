// Copyright 2020 Andrew Dunstall

#pragma once

#include <grpcpp/grpcpp.h>

#include <memory>
#include <vector>

#include "api/cluster.grpc.pb.h"

namespace parrotdb {

class NodeConnection {
 public:
  explicit NodeConnection(std::shared_ptr<grpc::Channel> channel);

  void Put(const std::vector<uint8_t>& key, const std::vector<uint8_t>& value);

  void Delete(const std::vector<uint8_t>& key);

 private:
  std::unique_ptr<pb::Cluster::Stub> stub_;
};

}  // namespace parrotdb
