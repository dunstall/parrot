// Copyright 2020 Andrew Dunstall

#include "cluster/nodeconnection.h"

#include <grpcpp/grpcpp.h>

#include <memory>
#include <vector>

#include "api/cluster.grpc.pb.h"

namespace parrotdb {

NodeConnection::NodeConnection(std::shared_ptr<grpc::Channel> channel)
    : stub_(pb::Cluster::NewStub(channel)) {}

void NodeConnection::Put(const std::vector<uint8_t>& key,
                         const std::vector<uint8_t>& value) {
  pb::PutRequest request;
  request.set_key(key.data(), key.size());
  request.set_value(value.data(), value.size());

  pb::PutResponse reply;
  grpc::ClientContext context;

  // TODO(AD) Async
  grpc::Status status = stub_->Put(&context, request, &reply);
  if (!status.ok()) {
    // TODO(AD) Handle
  }
}

void NodeConnection::Delete(const std::vector<uint8_t>& key) {
  pb::DeleteRequest request;
  request.set_key(key.data(), key.size());

  pb::DeleteResponse reply;
  grpc::ClientContext context;

  // TODO(AD) Async
  grpc::Status status = stub_->Delete(&context, request, &reply);
  if (!status.ok()) {
    // TODO(AD) Handle
  }
}

}  // namespace parrotdb
