// Copyright 2020 Andrew Dunstall

#include <chrono>
#include <string>
#include <thread>

#include "cluster/cluster.h"
#include "cluster/clusterimpl.h"
#include "cluster/clusterservice.h"

#include "cluster/node.h"
#include "gtest/gtest.h"
#include "store/inmemorystore.h"

namespace parrotdb {

class TestCluster : public ::testing::Test {
 protected:
  const std::string kAddr = "localhost:3110";

  TestCluster() : service_{std::make_shared<InMemoryStore>(), kAddr} {}

  void SetUp() override;

  void TearDown() override;

  ClusterService service_;
};

void TestCluster::SetUp() { service_.Start(); }

void TestCluster::TearDown() { service_.Stop(); }

TEST_F(TestCluster, X) {
  ClusterImpl cluster{{kAddr}};
  // cluster.Put(

  // parrotdb::Node node{kAddr};

  // auto conn = node.Connect();
  cluster.Put({1, 2, 3}, {1, 2, 3});
  cluster.Delete({1, 2, 3});
}

}  // namespace parrotdb
