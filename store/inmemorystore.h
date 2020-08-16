// Copyright 2020 Andrew Dunstall

#pragma once

#include <mutex>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

#include "store/store.h"

namespace parrotdb {

class InMemoryStore : public Store {
 public:
  InMemoryStore() = default;

  ~InMemoryStore() override = default;

  // Not copy-assignable as owns a mutex.
  InMemoryStore(const InMemoryStore&) = delete;
  InMemoryStore& operator=(const InMemoryStore&) = delete;

  InMemoryStore(InMemoryStore&&) = delete;
  InMemoryStore& operator=(InMemoryStore&&) = delete;

  std::optional<std::vector<uint8_t>> Get(
      const std::vector<uint8_t>& key) override;

  void Put(const std::vector<uint8_t>& key,
           const std::vector<uint8_t>& value) override;

  void Delete(const std::vector<uint8_t>& key) override;

 private:
  std::unordered_map<std::string, std::vector<uint8_t>> entries_;

  std::mutex mut_;
};

}  // namespace parrotdb
