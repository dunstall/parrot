// Copyright 2020 Andrew Dunstall

#include <vector>

#include "gtest/gtest.h"  // NOLINT
#include "store/inmemorystore.h"

namespace parrotdb {

class TestInMemoryStore : public ::testing::Test {};

TEST_F(TestInMemoryStore, GetNotFound) {
  InMemoryStore db{};
  EXPECT_FALSE(db.Get({1, 2, 3}));
}

TEST_F(TestInMemoryStore, GetInsertedValue) {
  InMemoryStore db{};
  const std::vector<uint8_t> key{1, 2, 3};
  const std::vector<uint8_t> value{4, 5, 6};
  db.Put(key, value);
  EXPECT_EQ(value, db.Get(key));
}

TEST_F(TestInMemoryStore, DeleteInsertedValue) {
  InMemoryStore db{};
  const std::vector<uint8_t> key{1, 2, 3};
  const std::vector<uint8_t> value{4, 5, 6};
  db.Put(key, value);
  db.Delete(key);
  EXPECT_FALSE(db.Get(key));
}

}  // namespace parrotdb
