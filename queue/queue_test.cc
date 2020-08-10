// Copyright 2020 Andrew Dunstall

#include <chrono>
#include <future>
#include <thread>

#include "gtest/gtest.h"
#include "queue/queue.h"

namespace wombat::broker::util {

using namespace std::chrono_literals;  // NOLINT

class QueueTest : public ::testing::Test {};

TEST_F(QueueTest, Empty) {
  Queue<int> queue{};
  EXPECT_TRUE(queue.empty());
}

TEST_F(QueueTest, WaitAndPopOk) {
  int val;
  Queue<int> queue{};
  queue.Push(val);
  EXPECT_EQ(val, queue.WaitAndPop());
}

TEST_F(QueueTest, WaitAndPopFillsWhileWaiting) {
  int val;
  Queue<int> queue{};
  std::async(std::launch::async, [&] {
    std::this_thread::sleep_for(10ms);
    queue.Push(val);
  });
  EXPECT_EQ(val, queue.WaitAndPop());
}

TEST_F(QueueTest, WaitForAndPopOk) {
  int val;
  Queue<int> queue{};
  queue.Push(val);
  EXPECT_EQ(val, queue.WaitForAndPop(100ms));
}

TEST_F(QueueTest, WaitForAndPopEmpty) {
  Queue<int> queue{};
  EXPECT_FALSE(queue.WaitForAndPop(10ms));
}

TEST_F(QueueTest, WaitForAndPopFillsWhileWaiting) {
  int val;
  Queue<int> queue{};
  std::async(std::launch::async, [&] {
    std::this_thread::sleep_for(10ms);
    queue.Push(val);
  });
  EXPECT_EQ(val, queue.WaitForAndPop(50ms));
}

TEST_F(QueueTest, TryPopOk) {
  int val;
  Queue<int> queue{};
  queue.Push(val);

  std::optional<int> res = queue.TryPop();
  EXPECT_TRUE(res);
  EXPECT_EQ(*res, val);
}

TEST_F(QueueTest, TryPopEmpty) {
  Queue<int> queue{};
  EXPECT_FALSE(queue.TryPop());
}

}  // namespace wombat::broker::util
