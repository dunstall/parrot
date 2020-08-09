// Copyright 2020 Andrew Dunstall

#include "parrotdb/parrotdb.h"

#include <memory>
#include <optional>
#include <vector>

#include "cluster/cluster.h"
#include "store/inmemorystore.h"

namespace parrotdb {

// TODO(AD) Make as thin an possible. Just create cluster and store, then
// pass to DB.

ParrotDB::ParrotDB(const ClusterOptions& cluster, const StoreOptions& store)
    : db_{nullptr, nullptr} {
  // TODO(AD) Handle non-dev (use RocksDB)
  if (store.dev) {
    db_ = DB{std::make_unique<Cluster>(cluster),
             std::make_unique<InMemoryStore>()};
  }

  // TODO(AD) Start anti-entropy background (gossip?)
}

std::optional<std::vector<uint8_t>> ParrotDB::Get(
    const std::vector<uint8_t>& key) {
  return Get(key, ReadOptions{});
}

std::optional<std::vector<uint8_t>> ParrotDB::Get(
    const std::vector<uint8_t>& key, const ReadOptions& options) {
  return db_.Get(key, options);
}

void ParrotDB::Put(const std::vector<uint8_t>& key,
                   const std::vector<uint8_t>& value) {
  return Put(key, value, WriteOptions{});
}

void ParrotDB::Put(const std::vector<uint8_t>& key,
                   const std::vector<uint8_t>& value,
                   const WriteOptions& options) {
  db_.Put(key, value, options);
}

void ParrotDB::Delete(const std::vector<uint8_t>& key) {
  return Delete(key, WriteOptions{});
}

void ParrotDB::Delete(const std::vector<uint8_t>& key,
                      const WriteOptions& options) {
  db_.Delete(key, options);
}

}  // namespace parrotdb
