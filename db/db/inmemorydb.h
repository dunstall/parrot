// Copyright 2020 Andrew Dunstall

#pragma once

#include <vector>

#include "parrotdb/db.h"

namespace parrotdb {

class InMemoryDB : public DB {
 public:
  ~InMemoryDB() override {}

  std::optional<std::vector<uint8_t>> Get(
      const std::vector<uint8_t>& key) override;

  void Put(const std::vector<uint8_t>& key,
           const std::vector<uint8_t>& value) override;

  void Delete(const std::vector<uint8_t>& key) override;
};

}  // namespace parrotdb
