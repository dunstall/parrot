// Copyright 2020 Andrew Dunstall

#include "cluster/node.h"

#include <string>

namespace parrotdb {

Node::Node(const std::string& addr) : addr_{addr} {}

}  // namespace parrotdb
