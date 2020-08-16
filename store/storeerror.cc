// Copyright 2020 Andrew Dunstall

#include "store/storeerror.h"

#include <string>
#include <utility>

namespace parrotdb {

StoreError::StoreError(std::string msg) : msg_{std::move(msg)} {}

const char* StoreError::what() const noexcept { return msg_.c_str(); }

}  // namespace parrotdb
