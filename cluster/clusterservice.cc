// Copyright 2020 Andrew Dunstall

#include "cluster/clusterservice.h"

#include <grpcpp/grpcpp.h>

#include <memory>
#include <string>
#include <thread>
#include <vector>

#include "api/cluster.grpc.pb.h"

namespace parrotdb {

ClusterService::ClusterService(std::shared_ptr<Store> store,
                               const std::string& addr)
    : pb::Cluster::Service{}, store_{store}, addr_{addr} {
  grpc::ServerBuilder builder;
  builder.AddListeningPort(addr_, grpc::InsecureServerCredentials());
  builder.RegisterService(this);
  server_ = std::unique_ptr<grpc::Server>(builder.BuildAndStart());
}

ClusterService::~ClusterService() { Stop(); }

void ClusterService::Start() {
  thread_ = std::thread(&ClusterService::Run, this);
}

void ClusterService::Stop() {
  // TODO(AD) Need to recreate server obj?
  server_->Shutdown();
  if (thread_.joinable()) {
    thread_.join();
  }
}

void ClusterService::Run() { server_->Wait(); }

grpc::Status ClusterService::Put(grpc::ServerContext* context,
                                 const pb::PutRequest* request,
                                 pb::PutResponse* reply) {
  const std::vector<uint8_t> key(request->key().begin(), request->key().end());
  const std::vector<uint8_t> val(request->value().begin(),
                                 request->value().end());
  store_->Put(key, val);
  return grpc::Status::OK;
}

grpc::Status ClusterService::Delete(grpc::ServerContext* context,
                                    const pb::DeleteRequest* request,
                                    pb::DeleteResponse* reply) {
  const std::vector<uint8_t> key(request->key().begin(), request->key().end());
  store_->Delete(key);
  return grpc::Status::OK;
}

}  // namespace parrotdb
