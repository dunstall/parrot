// Copyright 2020 Andrew Dunstall

#pragma once

#include <string>
#include <vector>

namespace parrotdb {

class Node {
 public:
  explicit Node(std::string addr);

  virtual ~Node() = default;

  Node(const Node&) = delete;
  Node& operator=(const Node&) = delete;

  Node(Node&&) = default;
  Node& operator=(Node&&) = default;

  std::string addr() const { return addr_; }

  virtual void Put(const std::vector<uint8_t>& key,
                   const std::vector<uint8_t>& value) = 0;

  virtual void Delete(const std::vector<uint8_t>& key) = 0;

 private:
  std::string addr_;
};

}  // namespace parrotdb
