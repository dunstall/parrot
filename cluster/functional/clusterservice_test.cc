// Copyright 2020 Andrew Dunstall

#include <memory>
#include <string>

#include "cluster/clusterservice.h"
#include "cluster/grpcnode.h"
#include "gtest/gtest.h"
#include "store/mock/store_mock.h"

namespace parrotdb {

class TestClusterService : public ::testing::Test {
 protected:
  const std::string kAddr = "localhost:3110";
};

TEST_F(TestClusterService, NodePutRecord) {
  const std::vector<uint8_t> key{1, 2, 3};
  const std::vector<uint8_t> val{4, 5, 6};
  std::shared_ptr<MockStore> store = std::make_shared<MockStore>();
  EXPECT_CALL(*store, Put(key, val)).Times(1);

  ClusterService service{store, kAddr};
  service.Start();

  GrpcNode node{kAddr};

  node.Put(key, val);
}

TEST_F(TestClusterService, NodeDeleteRecord) {
  const std::vector<uint8_t> key{1, 2, 3};
  std::shared_ptr<MockStore> store = std::make_shared<MockStore>();
  EXPECT_CALL(*store, Delete(key)).Times(1);

  ClusterService service{store, kAddr};
  service.Start();

  GrpcNode node{kAddr};

  node.Delete(key);
}

// TODO(AD)
// - Put db error
// - Delete db error
// - Node unreachable
// - ...

}  // namespace parrotdb
