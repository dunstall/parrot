// Copyright 2020 Andrew Dunstall

#pragma once

#include <mutex>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

#include "parrotdb/db.h"

namespace parrotdb {

class InMemoryDB : public DB {
 public:
  InMemoryDB() {}

  ~InMemoryDB() override {}

  // Not copy-assignable as owns a mutex.
  InMemoryDB(const InMemoryDB&) = delete;
  InMemoryDB& operator=(const InMemoryDB&) = delete;

  InMemoryDB(InMemoryDB&&) = default;
  InMemoryDB& operator=(InMemoryDB&&) = default;

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
