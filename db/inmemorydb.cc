// Copyright 2020 Andrew Dunstall

#include "db/inmemorydb.h"

#include <mutex>
#include <optional>
#include <vector>

namespace parrotdb {

std::optional<std::vector<uint8_t>> InMemoryDB::Get(
    const std::vector<uint8_t>& key) {
  const std::string s(key.begin(), key.end());
  std::lock_guard<std::mutex> lk(mut_);
  if (entries_.find(s) != entries_.end()) {
    return entries_.at(s);
  }
  return std::nullopt;
}

void InMemoryDB::Put(const std::vector<uint8_t>& key,
                     const std::vector<uint8_t>& value) {
  const std::string s(key.begin(), key.end());
  std::lock_guard<std::mutex> lk(mut_);
  entries_[s] = value;
}

void InMemoryDB::Delete(const std::vector<uint8_t>& key) {
  const std::string s(key.begin(), key.end());
  std::lock_guard<std::mutex> lk(mut_);
  entries_.erase(s);
}

}  // namespace parrotdb
