// Copyright 2020 Andrew Dunstall

#include "cluster/node.h"

#include <grpcpp/grpcpp.h>

#include <string>

#include "cluster/nodeconnection.h"

namespace parrotdb {

Node::Node(const std::string& addr) : addr_{addr} {
  channel_ = grpc::CreateChannel(addr, grpc::InsecureChannelCredentials());
}

void Node::Put(const std::vector<uint8_t>& key,
           const std::vector<uint8_t>& value) {
  auto conn = parrotdb::NodeConnection{channel_};
  conn.Put(key, value);
}

void Node::Delete(const std::vector<uint8_t>& key) {
  auto conn = parrotdb::NodeConnection{channel_};
  conn.Delete(key);
}

}  // namespace parrotdb
