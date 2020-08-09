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

TEST_F(TestDB, GetOk) {
  std::unique_ptr<MockCluster> cluster = std::make_unique<MockCluster>();
  std::unique_ptr<MockStore> store = std::make_unique<MockStore>();

  const std::vector<uint8_t> key{1, 2, 3};
  const std::vector<uint8_t> val{4, 5, 6};
  EXPECT_CALL(*store, Get(key)).WillOnce(::testing::Return(val));

  DB db{std::move(cluster), std::move(store)};
  EXPECT_EQ(val, db.Get(key));
}

TEST_F(TestDB, GetNotFound) {
  std::unique_ptr<MockCluster> cluster = std::make_unique<MockCluster>();
  std::unique_ptr<MockStore> store = std::make_unique<MockStore>();

  const std::vector<uint8_t> key{1, 2, 3};
  EXPECT_CALL(*store, Get(key)).WillOnce(::testing::Return(std::nullopt));

  DB db{std::move(cluster), std::move(store)};
  EXPECT_FALSE(db.Get(key));
}

TEST_F(TestDB, Put) {
  std::unique_ptr<MockCluster> cluster = std::make_unique<MockCluster>();
  std::unique_ptr<MockStore> store = std::make_unique<MockStore>();

  const std::vector<uint8_t> key{1, 2, 3};
  const std::vector<uint8_t> val{1, 2, 3};
  EXPECT_CALL(*cluster, Put(key, val)).Times(1);
  EXPECT_CALL(*store, Put(key, val)).Times(1);

  DB db{std::move(cluster), std::move(store)};
  db.Put(key, val);
}

TEST_F(TestDB, Delete) {
  std::unique_ptr<MockCluster> cluster = std::make_unique<MockCluster>();
  std::unique_ptr<MockStore> store = std::make_unique<MockStore>();

  const std::vector<uint8_t> key{1, 2, 3};
  const std::vector<uint8_t> val{1, 2, 3};
  EXPECT_CALL(*cluster, Delete(key)).Times(1);
  EXPECT_CALL(*store, Delete(key)).Times(1);

  DB db{std::move(cluster), std::move(store)};
  db.Delete(key);
}

}  // namespace parrotdb
