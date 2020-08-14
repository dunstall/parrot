// Copyright 2020 Andrew Dunstall

#include <chrono>
#include <thread>
#include <vector>

#include "gtest/gtest.h"
#include "parrotdb/parrotdb.h"

namespace parrotdb {

class TestParrotDB : public ::testing::Test {};

TEST_F(TestParrotDB, ReplicateToMultipleNodes) {
  ParrotDB db2{"localhost:3110", {"localhost:3111", "localhost:3112"}};
  ParrotDB db3{"localhost:3111", {"localhost:3110", "localhost:3112"}};

  ParrotDB db1{"localhost:3112", {"localhost:3110", "localhost:3111"}};
  const std::vector<uint8_t> key{1, 2, 3};
  const std::vector<uint8_t> val{4, 5, 6};
  db1.Put(key, val);

  ASSERT_TRUE(db2.Get(key));
  EXPECT_EQ(val, *db2.Get(key));

  ASSERT_TRUE(db3.Get(key));
  EXPECT_EQ(val, *db3.Get(key));
}

TEST_F(TestParrotDB, ReplicateToUnreachableNode) {
  ParrotDB db2{"localhost:3111", {"localhost:3110", "localhost:3112"}};

  ParrotDB db1{"localhost:3112", {"localhost:3110", "localhost:3111"}};
  const std::vector<uint8_t> key{1, 2, 3};
  const std::vector<uint8_t> val{4, 5, 6};
  db1.Put(key, val);

  ASSERT_TRUE(db2.Get(key));
  EXPECT_EQ(val, *db2.Get(key));

  ParrotDB db3{"localhost:3110", {"localhost:3111", "localhost:3112"}};

  std::this_thread::sleep_for(std::chrono::seconds(1));

  const std::vector<uint8_t> key2{7, 8, 9};
  const std::vector<uint8_t> val2{10, 11, 12};
  db1.Put(key2, val2);

  ASSERT_TRUE(db3.Get(key2));
  EXPECT_EQ(val2, *db3.Get(key2));
}

}  // namespace parrotdb
