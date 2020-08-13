// Copyright 2020 Andrew Dunstall

#include <memory>
#include <string>

#include "cluster/clusterservice.h"
#include "cluster/grpcnode.h"
#include "cluster/nodeerror.h"
#include "gtest/gtest.h"
#include "store/mock/store_mock.h"
#include "store/storeerror.h"

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

TEST_F(TestClusterService, NodePutUnreachable) {
  const std::vector<uint8_t> key{1, 2, 3};
  const std::vector<uint8_t> val{4, 5, 6};
  GrpcNode node{kAddr};
  EXPECT_THROW(node.Put(key, val), NodeError);
}

TEST_F(TestClusterService, NodeDeleteUnreachable) {
  const std::vector<uint8_t> key{1, 2, 3};
  GrpcNode node{kAddr};
  EXPECT_THROW(node.Delete(key), NodeError);
}

TEST_F(TestClusterService, PutDatabaseError) {
  const std::vector<uint8_t> key{1, 2, 3};
  const std::vector<uint8_t> val{4, 5, 6};
  std::shared_ptr<MockStore> store = std::make_shared<MockStore>();
  EXPECT_CALL(*store, Put(key, val))
      .WillOnce(::testing::Throw(StoreError("mock store error")));

  ClusterService service{store, kAddr};
  service.Start();

  GrpcNode node{kAddr};
  EXPECT_THROW(node.Put(key, val), NodeError);
}

TEST_F(TestClusterService, DeleteDatabaseError) {
  const std::vector<uint8_t> key{1, 2, 3};
  std::shared_ptr<MockStore> store = std::make_shared<MockStore>();
  EXPECT_CALL(*store, Delete(key))
      .WillOnce(::testing::Throw(StoreError("mock store error")));

  ClusterService service{store, kAddr};
  service.Start();

  GrpcNode node{kAddr};
  EXPECT_THROW(node.Delete(key), NodeError);
}

// TODO(AD)
// - Node reboots and reconnects
// - ...

}  // namespace parrotdb
