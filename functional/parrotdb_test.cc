// Copyright 2020 Andrew Dunstall

#include <random>
#include <string>
#include <vector>

#include "parrotdb/config.h"
#include "parrotdb/parrotdb.h"

std::vector<uint8_t> GenerateRandom(size_t n) {
  // First create an instance of an engine.
  std::random_device rnd_device;
  // Specify the engine and distribution.
  std::mt19937 mersenne_engine{rnd_device()};  // Generates random integers
  std::uniform_int_distribution<uint8_t> dist{0, 0xff};

  auto gen = [&dist, &mersenne_engine]() { return dist(mersenne_engine); };
  std::vector<uint8_t> b(n);
  std::generate(b.begin(), b.end(), gen);
  return b;
}

int main(int argc, char** argv) {
  std::vector<std::string> cluster{};
  for (int i = 1; i != argc; ++i) {
    cluster.push_back(argv[i]);
  }

  parrotdb::Config config{"0.0.0.0:3112", cluster, true};
  parrotdb::ParrotDB db{config};
  while (true) {
    const std::vector<uint8_t> key{GenerateRandom(10)};
    const std::vector<uint8_t> val{GenerateRandom(25)};
    db.Put(key, val);
  }
}
