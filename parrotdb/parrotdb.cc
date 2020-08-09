// Copyright 2020 Andrew Dunstall

#include "parrotdb/parrotdb.h"

#include <memory>
#include <optional>
#include <vector>

#include "store/inmemorystore.h"

namespace parrotdb {

ParrotDB::ParrotDB(const ClusterOptions& cluster, const StoreOptions& store) {
  if (store.dev) {
    // TODO(AD) Handle non-dev (use RocksDB)
    store_ = std::make_shared<InMemoryStore>();
  }

  // TODO(AD) Start anti-entropy background (gossip?)
}

std::optional<std::vector<uint8_t>> ParrotDB::Get(
    const std::vector<uint8_t>& key) {
  return Get(key, ReadOptions{});
}

std::optional<std::vector<uint8_t>> ParrotDB::Get(
    const std::vector<uint8_t>& key, const ReadOptions& options) {
  // TODO(AD) Handle quorum and read-repair (request all replicas and take
  // latest from N responses and repair stale)
  return store_->Get(key);
}

void ParrotDB::Put(const std::vector<uint8_t>& key,
                   const std::vector<uint8_t>& value) {
  return Put(key, value, WriteOptions{});
}

void ParrotDB::Put(const std::vector<uint8_t>& key,
                   const std::vector<uint8_t>& value,
                   const WriteOptions& options) {
  store_->Put(key, value);
  // TODO(AD) Handle quorum. Just async for now. Need to roll back if < N
  // available?
}

void ParrotDB::Delete(const std::vector<uint8_t>& key) {
  return Delete(key, WriteOptions{});
}

void ParrotDB::Delete(const std::vector<uint8_t>& key,
                      const WriteOptions& options) {
  store_->Delete(key);
  // TODO(AD) Handle quorum. Just async for now. Need to roll back if < N
  // available?
}

}  // namespace parrotdb
