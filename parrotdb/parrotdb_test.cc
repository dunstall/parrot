// Copyright 2020 Andrew Dunstall

#include "parrotdb/parrotdb.h"
#include "gtest/gtest.h"
#include "parrotdb/options.h"

namespace parrotdb {

class ParrotDBTest : public ::testing::Test {};

TEST_F(ParrotDBTest, TestDevStorage) {
  ParrotDB db{ClusterOptions{}, StoreOptions(true)};
}

}  // namespace parrotdb
