// Copyright 2020 Andrew Dunstall

#include "cluster/nodeerror.h"

#include <string>

namespace parrotdb {

NodeError::NodeError(const std::string& msg) : msg_{msg} {}

const char* NodeError::what() const noexcept {
  return msg_.c_str();
}

}  // namespace parrotdb
