// Copyright 2020 Andrew Dunstall

#include "parrotdb/parrotdb.h"

#include <optional>
#include <vector>

#include "cluster/cluster.h"
#include "cluster/clusterimpl.h"
#include "cluster/grpcnode.h"
#include "cluster/node.h"
#include "parrotdb/config.h"
#include "spdlog/spdlog.h"
#include "store/inmemorystore.h"

namespace parrotdb {

// This is a thin wrapper around DB to construct the production database and
// cluster - so DB can be better tested with dependency injection.

ParrotDB::ParrotDB(const Config& conf) : db_{nullptr, nullptr} {
  ConfigureLogging(conf.verbose);

  std::shared_ptr<Store> store = std::make_shared<InMemoryStore>();
  db_ = DB{CreateCluster(conf), store};

  service_ = std::make_unique<ClusterService>(store, conf.addr);
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

void ParrotDB::ConfigureLogging(bool verbose) const {
  spdlog::info("running ParrotDB");
  if (verbose) {
    spdlog::set_level(spdlog::level::debug);
    spdlog::debug("verbose logging enabled");
  }
}

std::unique_ptr<Cluster> ParrotDB::CreateCluster(const Config& conf) const {
  std::vector<std::shared_ptr<Node>> nodes{};
  for (const std::string& a : conf.cluster) {
    spdlog::info("adding node: {}", a);
    nodes.push_back(std::make_shared<GrpcNode>(a));
  }
  return std::make_unique<ClusterImpl>(std::move(nodes));
}

}  // namespace parrotdb
