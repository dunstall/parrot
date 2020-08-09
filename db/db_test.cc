// Copyright 2020 Andrew Dunstall

#include <memory>
#include <optional>
#include <utility>
#include <vector>

#include "db/db.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "store/store.h"

namespace parrotdb {

class MockCluster : public Cluster {
 public:
  MOCK_METHOD(std::optional<std::vector<uint8_t>>, Get,
              (const std::vector<uint8_t>& key), (override));

  MOCK_METHOD(void, Put,
              (const std::vector<uint8_t>& key,
               const std::vector<uint8_t>& value),
              (override));

  MOCK_METHOD(void, Delete, (const std::vector<uint8_t>& key), (override));
};

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

class TestDB : public ::testing::Test {};

TEST_F(TestDB, X) {
  std::unique_ptr<MockCluster> cluster = std::make_unique<MockCluster>();
  std::unique_ptr<MockStore> store = std::make_unique<MockStore>();

  DB db{std::move(cluster), std::move(store)};
}

}  // namespace parrotdb
