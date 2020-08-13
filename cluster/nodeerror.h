// Copyright 2020 Andrew Dunstall

#pragma once

#include <exception>
#include <string>

namespace parrotdb {

class NodeError : public std::exception {
 public:
  explicit NodeError(const std::string& msg);

  const char* what() const noexcept override;

 private:
  std::string msg_;
};

}  // namespace parrotdb
