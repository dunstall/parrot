// Copyright 2020 Andrew Dunstall

#include <chrono>
#include <thread>
#include <vector>

#include "gtest/gtest.h"
#include "parrotdb/parrotdb.h"

namespace parrotdb {

class TestParrotDB : public ::testing::Test {};

TEST_F(TestParrotDB, X) {
  ParrotDB db2{"localhost:3110", {"localhost:3111"}};

  std::this_thread::sleep_for(std::chrono::seconds(1));

  ParrotDB db1{"localhost:3111", {"localhost:3110"}};
  const std::vector<uint8_t> key{1, 2, 3};
  const std::vector<uint8_t> val{4, 5, 6};
  db1.Put(key, val);
  std::cout << "PUT" << std::endl;

  std::this_thread::sleep_for(std::chrono::seconds(1));

  ASSERT_TRUE(db2.Get(key));
  EXPECT_EQ(val, *db2.Get(key));
}

// TODO can test node failures by stopping nodes

}  // namespace parrotdb
