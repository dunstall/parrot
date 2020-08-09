// Copyright 2020 Andrew Dunstall

#include "store/inmemorystore.h"

#include <mutex>
#include <optional>
#include <vector>

namespace parrotdb {

std::optional<std::vector<uint8_t>> InMemoryStore::Get(
    const std::vector<uint8_t>& key) {
  const std::string s(key.begin(), key.end());
  std::lock_guard<std::mutex> lk(mut_);
  if (entries_.find(s) != entries_.end()) {
    return entries_.at(s);
  }
  return std::nullopt;
}

void InMemoryStore::Put(const std::vector<uint8_t>& key,
                        const std::vector<uint8_t>& value) {
  const std::string s(key.begin(), key.end());
  std::lock_guard<std::mutex> lk(mut_);
  entries_[s] = value;
}

void InMemoryStore::Delete(const std::vector<uint8_t>& key) {
  const std::string s(key.begin(), key.end());
  std::lock_guard<std::mutex> lk(mut_);
  entries_.erase(s);
}

}  // namespace parrotdb
