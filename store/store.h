// Copyright 2020 Andrew Dunstall

#pragma once

#include <cstdint>
#include <optional>
#include <vector>

namespace parrotdb {

// Facade for the underlying database storage engine.
class Store {
 public:
  Store() = default;

  virtual ~Store() = default;

  Store(const Store&) = delete;
  Store& operator=(const Store&) = delete;

  Store(Store&&) = delete;
  Store& operator=(Store&&) = delete;

  virtual std::optional<std::vector<uint8_t>> Get(
      const std::vector<uint8_t>& key) = 0;

  virtual void Put(const std::vector<uint8_t>& key,
                   const std::vector<uint8_t>& value) = 0;

  virtual void Delete(const std::vector<uint8_t>& key) = 0;
};

}  // namespace parrotdb
