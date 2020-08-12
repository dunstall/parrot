// Copyright 2020 Andrew Dunstall

#pragma once

#include <condition_variable>
#include <mutex>
#include <optional>
#include <queue>
#include <utility>

namespace parrotdb {

template <class T>
class Queue {
 public:
  Queue() : data_queue_{}, cv_{} {}

  Queue(const Queue& conn) = delete;
  Queue& operator=(const Queue& conn) = delete;

  Queue(Queue&& conn) = delete;
  Queue& operator=(Queue&& conn) = delete;

  void Push(T val) {
    std::lock_guard<std::mutex> lk(mut_);
    // TODO(AD) Block if full
    data_queue_.push(val);
    cv_.notify_one();
  }

  T WaitAndPop() {
    std::unique_lock<std::mutex> lk(mut_);
    cv_.wait(lk, [this] { return !data_queue_.empty(); });
    T val = std::move(data_queue_.front());
    data_queue_.pop();
    return val;
  }

  template <typename R, typename P>
  std::optional<T> WaitForAndPop(const std::chrono::duration<R, P>& dur) {
    std::unique_lock<std::mutex> lk(mut_);
    if (cv_.wait_for(lk, dur, [this] { return !data_queue_.empty(); })) {
      T val = std::move(data_queue_.front());
      data_queue_.pop();
      return val;
    }
    return std::nullopt;
  }

  std::optional<T> TryPop() {
    std::lock_guard<std::mutex> lk(mut_);
    if (data_queue_.empty()) {
      return std::nullopt;
    }
    T val = std::move(data_queue_.front());
    data_queue_.pop();
    return val;
  }

  bool empty() {
    std::lock_guard<std::mutex> lk(mut_);
    return data_queue_.empty();
  }

 private:
  std::queue<T> data_queue_;

  std::condition_variable cv_;

  std::mutex mut_;
};

}  // namespace parrotdb
