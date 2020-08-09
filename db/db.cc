// Copyright 2020 Andrew Dunstall

#include "db/db.h"

#include <memory>
#include <optional>
#include <utility>
#include <vector>

#include "store/inmemorystore.h"

namespace parrotdb {

DB::DB(std::unique_ptr<Cluster> cluster, std::unique_ptr<Store> store)
    : cluster_{std::move(cluster)}, store_{std::move(store)} {}

std::optional<std::vector<uint8_t>> DB::Get(const std::vector<uint8_t>& key) {
  // TODO(AD) For now just use local store, later handle read quorum and read
  // repair (pass store->Get() to cluster for read repair).
  return store_->Get(key);
}

void DB::Put(const std::vector<uint8_t>& key,
             const std::vector<uint8_t>& value) {
  cluster_->Put(key, value);
  store_->Put(key, value);
}

void DB::Delete(const std::vector<uint8_t>& key) {
  cluster_->Delete(key);
  store_->Delete(key);
}

}  // namespace parrotdb
