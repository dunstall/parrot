// Copyright 2020 Andrew Dunstall

#pragma once

#include <optional>
#include <vector>

#include "gmock/gmock.h"
#include "store/store.h"

namespace parrotdb {

class MockStore : public Store {
 public:
  MOCK_METHOD(std::optional<std::vector<uint8_t>>, Get,
              (const std::vector<uint8_t>& key), (override));
  MOCK_METHOD(void, Put,
              (const std::vector<uint8_t>& key,
               const std::vector<uint8_t>& value),
              (override));
  MOCK_METHOD(void, Delete, (const std::vector<uint8_t>& key), (override));
};

}  // namespace parrotdb
