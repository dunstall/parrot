// Copyright 2020 Andrew Dunstall

#pragma once

#include <grpcpp/grpcpp.h>

#include <memory>
#include <string>
#include <vector>

#include "cluster/node.h"
#include "rpc/cluster.grpc.pb.h"

namespace parrotdb {

class GrpcNode : public Node {
 public:
  explicit GrpcNode(const std::string& addr);

  ~GrpcNode() override = default;

  GrpcNode(const GrpcNode&) = delete;
  GrpcNode& operator=(const GrpcNode&) = delete;

  GrpcNode(GrpcNode&&) = default;
  GrpcNode& operator=(GrpcNode&&) = default;

  void Put(const std::vector<uint8_t>& key,
           const std::vector<uint8_t>& value) override;

  void Delete(const std::vector<uint8_t>& key) override;

 private:
  std::string addr_;

  std::shared_ptr<grpc::Channel> channel_;

  std::unique_ptr<pb::Cluster::Stub> stub_;
};

}  // namespace parrotdb
