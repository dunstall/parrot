// Copyright 2020 Andrew Dunstall

#include "cluster/node.h"

#include <string>
#include <utility>

namespace parrotdb {

Node::Node(std::string addr) : addr_{std::move(addr)} {}

}  // namespace parrotdb
