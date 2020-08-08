// Copyright 2020 Andrew Dunstall

#include "db/inmemorydb.h"

#include <optional>
#include <vector>

namespace parrotdb {

std::optional<std::vector<uint8_t>> InMemoryDB::Get(
    const std::vector<uint8_t>& key) {
  return std::nullopt;
}

void InMemoryDB::Put(const std::vector<uint8_t>& key,
                     const std::vector<uint8_t>& value) {}

void InMemoryDB::Delete(const std::vector<uint8_t>& key) {}

}  // namespace parrotdb
