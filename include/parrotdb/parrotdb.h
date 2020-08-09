// Copyright 2020 Andrew Dunstall

#pragma once

#include <cstdint>
#include <memory>
#include <optional>
#include <vector>

#include "parrotdb/options.h"

namespace parrotdb {

class ParrotDB {
 public:
  explicit ParrotDB(const ClusterOptions& cluster, const StoreOptions& store);

  ~ParrotDB() {}

  // Not copy-assignable.
  ParrotDB(const ParrotDB&) = delete;
  ParrotDB& operator=(const ParrotDB&) = delete;

  ParrotDB(ParrotDB&&) = default;
  ParrotDB& operator=(ParrotDB&&) = default;

  std::optional<std::vector<uint8_t>> Get(const std::vector<uint8_t>& key);

  std::optional<std::vector<uint8_t>> Get(const std::vector<uint8_t>& key,
                                          const ReadOptions& options);

  void Put(const std::vector<uint8_t>& key, const std::vector<uint8_t>& value);

  void Put(const std::vector<uint8_t>& key, const std::vector<uint8_t>& value,
           const WriteOptions& options);

  void Delete(const std::vector<uint8_t>& key);

  void Delete(const std::vector<uint8_t>& key, const WriteOptions& options);

 private:
  // std::shared_ptr<Store> store_;
};

}  // namespace parrotdb
