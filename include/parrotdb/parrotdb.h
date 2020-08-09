// Copyright 2020 Andrew Dunstall

#pragma once

#include <cstdint>
#include <optional>
#include <vector>

#include "db/db.h"
#include "store/store.h"

namespace parrotdb {

class ParrotDB {
 public:
  ParrotDB();

  ~ParrotDB() {}

  // Not copy-assignable.
  ParrotDB(const ParrotDB&) = delete;
  ParrotDB& operator=(const ParrotDB&) = delete;

  ParrotDB(ParrotDB&&) = default;
  ParrotDB& operator=(ParrotDB&&) = default;

  std::optional<std::vector<uint8_t>> Get(const std::vector<uint8_t>& key);

  void Put(const std::vector<uint8_t>& key, const std::vector<uint8_t>& value);

  void Delete(const std::vector<uint8_t>& key);

 private:
  DB db_;
};

}  // namespace parrotdb
