// Copyright 2020 Andrew Dunstall

#include "cluster/grpcnode.h"

#include <grpcpp/grpcpp.h>

#include <memory>
#include <string>
#include <vector>

#include "api/cluster.grpc.pb.h"
#include "cluster/nodeerror.h"

namespace parrotdb {

GrpcNode::GrpcNode(const std::string& addr) {
  // TODO(AD) Handle exceptions
  channel_ = grpc::CreateChannel(addr, grpc::InsecureChannelCredentials());
  stub_ = pb::Cluster::NewStub(channel_);
}

void GrpcNode::Put(const std::vector<uint8_t>& key,
                   const std::vector<uint8_t>& value) {
  pb::PutRequest request;
  request.set_key(key.data(), key.size());
  request.set_value(value.data(), value.size());

  pb::PutResponse reply;
  grpc::ClientContext context;

  // TODO(AD) Async
  const grpc::Status status = stub_->Put(&context, request, &reply);
  if (!status.ok()) {
    throw NodeError{status.error_message()};
  }
}

void GrpcNode::Delete(const std::vector<uint8_t>& key) {
  pb::DeleteRequest request;
  request.set_key(key.data(), key.size());

  pb::DeleteResponse reply;
  grpc::ClientContext context;

  // TODO(AD) Async
  grpc::Status status = stub_->Delete(&context, request, &reply);
  if (!status.ok()) {
    throw NodeError{status.error_message()};
  }
}

}  // namespace parrotdb
