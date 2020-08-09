// Copyright 2020 Andrew Dunstall

#include "parrotdb/parrotdb.h"

#include <optional>
#include <vector>

namespace parrotdb {

ParrotDB::ParrotDB(const ClusterOptions& cluster, const StoreOptions& store) {
  // TODO(AD) Construct DB with store options - if dev use in memory
  // TODO(AD) Start anti-entropy background
}

std::optional<std::vector<uint8_t>> ParrotDB::Get(
    const std::vector<uint8_t>& key) {
  // TODO(AD) Call Get with default read options
  return std::nullopt;
}

std::optional<std::vector<uint8_t>> ParrotDB::Get(
    const std::vector<uint8_t>& key, const ReadOptions& options) {
  // TODO(AD) Request from N replicas (including locally) (N in options)
  // TODO(AD) Handle read repair (this can be in cluster)
  return std::nullopt;
}

void ParrotDB::Put(const std::vector<uint8_t>& key,
                   const std::vector<uint8_t>& value) {
  // TODO(AD) Call Put with default write options
}

void ParrotDB::Put(const std::vector<uint8_t>& key,
                   const std::vector<uint8_t>& value,
                   const WriteOptions& options) {
  // TODO(AD) Write to local storage
  // TODO(AD) Replicate to the cluster - either sync or async based on options
  // TODO(AD) If sync and cannot replicate roll back?
}

void ParrotDB::Delete(const std::vector<uint8_t>& key) {
  // TODO(AD) Call Delete with default write options
}

void ParrotDB::Delete(const std::vector<uint8_t>& key,
                      const WriteOptions& options) {
  // TODO(AD) Write to local storage
  // TODO(AD) Replicate to the cluster - either sync or async based on options
  // TODO(AD) If sync and cannot replicate roll back?
}

}  // namespace parrotdb
