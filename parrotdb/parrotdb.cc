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

  // TODO(AD) Start anti-entropy background
}

std::optional<std::vector<uint8_t>> ParrotDB::Get(
    const std::vector<uint8_t>& key) {
  return Get(key, ReadOptions{});
}

std::optional<std::vector<uint8_t>> ParrotDB::Get(
    const std::vector<uint8_t>& key, const ReadOptions& options) {
  // TODO(AD) Request from N replicas (including locally) (N in options)
  // TODO(AD) Handle read repair (this can be in cluster)
  return store_->Get(key);
}

void ParrotDB::Put(const std::vector<uint8_t>& key,
                   const std::vector<uint8_t>& value) {
  return Put(key, value, WriteOptions{});
}

void ParrotDB::Put(const std::vector<uint8_t>& key,
                   const std::vector<uint8_t>& value,
                   const WriteOptions& options) {
  // TODO(AD) Write to local storage
  // TODO(AD) Replicate to the cluster - either sync or async based on options
  // TODO(AD) If sync and cannot replicate roll back?
  store_->Put(key, value);
}

void ParrotDB::Delete(const std::vector<uint8_t>& key) {
  return Delete(key, WriteOptions{});
}

void ParrotDB::Delete(const std::vector<uint8_t>& key,
                      const WriteOptions& options) {
  // TODO(AD) Write to local storage
  // TODO(AD) Replicate to the cluster - either sync or async based on options
  // TODO(AD) If sync and cannot replicate roll back?
  store_->Delete(key);
}

}  // namespace parrotdb
