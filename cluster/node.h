// Copyright 2020 Andrew Dunstall

#pragma once

#include <grpcpp/grpcpp.h>

#include <string>

#include "cluster/nodeconnection.h"

namespace parrotdb {

class Node {
 public:
  explicit Node(const std::string& addr);

  // NodeConnection Connect();

  void Put(const std::vector<uint8_t>& key,
           const std::vector<uint8_t>& value);

  void Delete(const std::vector<uint8_t>& key);

 private:
  std::string addr_;

  std::shared_ptr<grpc::Channel> channel_;
};

}  // namespace parrotdb
