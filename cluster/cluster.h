// Copyright 2020 Andrew Dunstall

#pragma once

#include <cstdint>
#include <vector>

namespace parrotdb {

class Cluster {
 public:
  Cluster() = default;

  virtual ~Cluster() {}

  Cluster(const Cluster&) = delete;
  Cluster& operator=(const Cluster&) = delete;

  Cluster(Cluster&&) = default;
  Cluster& operator=(Cluster&&) = default;

  virtual void Put(const std::vector<uint8_t>& key,
                   const std::vector<uint8_t>& value) = 0;

  virtual void Delete(const std::vector<uint8_t>& key) = 0;
};

}  // namespace parrotdb
