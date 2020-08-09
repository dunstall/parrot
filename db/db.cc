// Copyright 2020 Andrew Dunstall

#include "db/db.h"

#include <memory>
#include <optional>
#include <utility>
#include <vector>

#include "store/inmemorystore.h"

namespace parrotdb {

DB::DB(std::unique_ptr<Cluster> cluster, std::unique_ptr<Store> store)
    : cluster_{std::move(cluster)}, store_{std::move(store)} {
  // if (store.dev) {
  // TODO(AD) Handle non-dev (use RocksDB)
  // store_ = std::make_shared<InMemoryStore>();
  // }

  // TODO(AD) Start anti-entropy background (gossip?)
}

std::optional<std::vector<uint8_t>> DB::Get(const std::vector<uint8_t>& key) {
  return Get(key, ReadOptions{});
}

std::optional<std::vector<uint8_t>> DB::Get(const std::vector<uint8_t>& key,
                                            const ReadOptions& options) {
  // TODO need to test this:w
  //
  cluster_->Get(key, options);
  return store_->Get(key);
}

void DB::Put(const std::vector<uint8_t>& key,
             const std::vector<uint8_t>& value) {
  return Put(key, value, WriteOptions{});
}

void DB::Put(const std::vector<uint8_t>& key, const std::vector<uint8_t>& value,
             const WriteOptions& options) {
  store_->Put(key, value);
  // TODO(AD) Handle quorum. Just async for now. Quorum must be atomic (each
  // replica ends in same state so if fails all roll back).
}

void DB::Delete(const std::vector<uint8_t>& key) {
  return Delete(key, WriteOptions{});
}

void DB::Delete(const std::vector<uint8_t>& key, const WriteOptions& options) {
  store_->Delete(key);
  // TODO(AD) Handle quorum. Just async for now. Quorum must be atomic (each
  // replica ends in same state so if fails all roll back).
}

}  // namespace parrotdb
