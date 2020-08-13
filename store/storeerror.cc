// Copyright 2020 Andrew Dunstall

#include "store/storeerror.h"

#include <string>

namespace parrotdb {

StoreError::StoreError(const std::string& msg) : msg_{msg} {}

const char* StoreError::what() const noexcept { return msg_.c_str(); }

}  // namespace parrotdb
