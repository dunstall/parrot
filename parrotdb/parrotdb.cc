// Copyright 2020 Andrew Dunstall

#include "parrotdb/parrotdb.h"

#include <memory>
#include <optional>
#include <vector>

#include "cluster/cluster.h"
#include "store/inmemorystore.h"

namespace parrotdb {

ParrotDB::ParrotDB() : db_{nullptr, nullptr} {
  db_ = DB{nullptr, std::make_unique<InMemoryStore>()};

  // TODO(AD) Start anti-entropy background (gossip?)
}

std::optional<std::vector<uint8_t>> ParrotDB::Get(
    const std::vector<uint8_t>& key) {
  return Get(key);
}

void ParrotDB::Put(const std::vector<uint8_t>& key,
                   const std::vector<uint8_t>& value) {
  return Put(key, value);
}

void ParrotDB::Delete(const std::vector<uint8_t>& key) { return Delete(key); }

}  // namespace parrotdb
