// Copyright 2020 Andrew Dunstall

#pragma once

#include <cstdint>
#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "cluster/clusterservice.h"
#include "db/db.h"
#include "store/store.h"

namespace parrotdb {

class ParrotDB {
 public:
  ParrotDB(const std::string& addr, const std::vector<std::string>& cluster,
           bool verbose = false);

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
  std::unique_ptr<ClusterService> service_;
};

}  // namespace parrotdb
