// Copyright 2020 Andrew Dunstall

#include "parrotdb/parrotdb.h"
#include "gtest/gtest.h"
#include "parrotdb/options.h"

namespace parrotdb {

class TestParrotDB : public ::testing::Test {};

TEST_F(TestParrotDB, GetNotFound) {
  ParrotDB db{ClusterOptions{}, StoreOptions(true)};
  EXPECT_FALSE(db.Get({1, 2, 3}));
}

TEST_F(TestParrotDB, GetInsertedValue) {
  ParrotDB db{ClusterOptions{}, StoreOptions(true)};
  const std::vector<uint8_t> key{1, 2, 3};
  const std::vector<uint8_t> value{4, 5, 6};
  db.Put(key, value);
  EXPECT_EQ(value, db.Get(key));
}

TEST_F(TestParrotDB, DeleteInsertedValue) {
  ParrotDB db{ClusterOptions{}, StoreOptions(true)};
  const std::vector<uint8_t> key{1, 2, 3};
  const std::vector<uint8_t> value{4, 5, 6};
  db.Put(key, value);
  db.Delete(key);
  EXPECT_FALSE(db.Get(key));
}

}  // namespace parrotdb
