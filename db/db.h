// Copyright 2020 Andrew Dunstall

#pragma once

#include <cstdint>
#include <memory>
#include <optional>
#include <vector>

#include "cluster/cluster.h"
#include "store/store.h"

namespace parrotdb {

class DB {
 public:
  DB(std::unique_ptr<Cluster> cluster, std::unique_ptr<Store> store);

  // Not copy-assignable.
  DB(const DB&) = delete;
  DB& operator=(const DB&) = delete;

  DB(DB&&) = default;
  DB& operator=(DB&&) = default;

  std::optional<std::vector<uint8_t>> Get(const std::vector<uint8_t>& key);

  void Put(const std::vector<uint8_t>& key, const std::vector<uint8_t>& value);

  void Delete(const std::vector<uint8_t>& key);

 private:
  std::unique_ptr<Cluster> cluster_;

  std::unique_ptr<Store> store_;
};

}  // namespace parrotdb
