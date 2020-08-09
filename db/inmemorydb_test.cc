// Copyright 2020 Andrew Dunstall

#include <vector>

#include "db/inmemorydb.h"
#include "gtest/gtest.h"

namespace parrotdb {

class TestInMemoryDB : public ::testing::Test {};

TEST_F(TestInMemoryDB, GetNotFound) {
  InMemoryDB db{};
  EXPECT_FALSE(db.Get({1, 2, 3}));
}

TEST_F(TestInMemoryDB, GetInsertedValue) {
  InMemoryDB db{};
  const std::vector<uint8_t> key{1, 2, 3};
  const std::vector<uint8_t> value{4, 5, 6};
  db.Put(key, value);
  EXPECT_EQ(value, db.Get(key));
}

TEST_F(TestInMemoryDB, DeleteInsertedValue) {
  InMemoryDB db{};
  const std::vector<uint8_t> key{1, 2, 3};
  const std::vector<uint8_t> value{4, 5, 6};
  db.Put(key, value);
  db.Delete(key);
  EXPECT_FALSE(db.Get(key));
}

}  // namespace parrotdb
