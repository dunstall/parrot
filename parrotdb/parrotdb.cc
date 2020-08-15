// Copyright 2020 Andrew Dunstall

#include "parrotdb/parrotdb.h"

#include <optional>
#include <vector>

#include "cluster/cluster.h"
#include "cluster/clusterimpl.h"
#include "cluster/grpcnode.h"
#include "cluster/node.h"
#include "spdlog/spdlog.h"
#include "store/inmemorystore.h"

namespace parrotdb {

ParrotDB::ParrotDB(const std::string& addr,
                   const std::vector<std::string>& cluster, bool verbose)
    : db_{nullptr, nullptr} {
  if (verbose) {
    spdlog::set_level(spdlog::level::debug);
    spdlog::debug("ParrotDB verbose logging");
  }
  std::vector<std::shared_ptr<Node>> nodes{};
  for (const std::string& a : cluster) {
    nodes.push_back(std::make_shared<GrpcNode>(a));
  }
  std::shared_ptr<Store> store = std::make_shared<InMemoryStore>();
  db_ = DB{std::make_unique<ClusterImpl>(std::move(nodes)), store};
  service_ = std::make_unique<ClusterService>(store, addr);
  service_->Start();
}

std::optional<std::vector<uint8_t>> ParrotDB::Get(
    const std::vector<uint8_t>& key) {
  return db_.Get(key);
}

void ParrotDB::Put(const std::vector<uint8_t>& key,
                   const std::vector<uint8_t>& value) {
  return db_.Put(key, value);
}

void ParrotDB::Delete(const std::vector<uint8_t>& key) { return Delete(key); }

}  // namespace parrotdb
