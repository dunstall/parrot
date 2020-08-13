// Copyright 2020 Andrew Dunstall

#pragma once

#include <grpcpp/grpcpp.h>

#include <memory>
#include <string>
#include <thread>

#include "api/cluster.grpc.pb.h"
#include "store/store.h"

namespace parrotdb {

class ClusterService final : public pb::Cluster::Service {
 public:
  ClusterService(std::shared_ptr<Store> store, const std::string& addr);

  ~ClusterService();

  ClusterService(const ClusterService&) = delete;
  ClusterService& operator=(const ClusterService&) = delete;

  ClusterService(ClusterService&&) = delete;
  ClusterService& operator=(ClusterService&&) = delete;

  void Start();

  void Stop();

 private:
  grpc::Status Put(grpc::ServerContext* context, const pb::PutRequest* request,
                   pb::PutResponse* reply) override;

  grpc::Status Delete(grpc::ServerContext* context,
                      const pb::DeleteRequest* request,
                      pb::DeleteResponse* reply) override;

  void Run();

  std::shared_ptr<Store> store_;

  std::string addr_;

  std::thread thread_;

  std::unique_ptr<grpc::Server> server_;
};

}  // namespace parrotdb
