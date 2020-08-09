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
  // TODO(AD)
  // cluster_->Get(key);
  // store_->Get(key);
  return std::nullopt;
}

void DB::Put(const std::vector<uint8_t>& key,
             const std::vector<uint8_t>& value) {
  // TODO(AD)
  // cluster_->Put(key, value, options);
  // store_->Put(key, value);
}

void DB::Delete(const std::vector<uint8_t>& key) {
  // TODO(AD)
  // cluster_->Delete(key, options);
  // store_->Delete(key);
}

}  // namespace parrotdb
