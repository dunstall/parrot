// Copyright 2020 Andrew Dunstall

#include <string>
#include <vector>

#include "parrotdb/parrotdb.h"

int main(int argc, char** argv) {
  std::vector<std::string> cluster{};
  for (int i = 1; i != argc; ++i) {
    cluster.push_back(argv[i]);
  }

  parrotdb::ParrotDB db{"0.0.0.0:3112", cluster};
  while (true) {
    const std::vector<uint8_t> key{1, 2, 3};
    const std::vector<uint8_t> val{4, 5, 6};
    db.Put(key, val);
  }
}
