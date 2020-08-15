# ParrotDB
C++ database API with asynchronous replication.

## Install
**Bazel**
```
$ bazel build //parrotdb
```
Also run unit tests with
```
$ bazel test ...
```

## Features
* In memory storage engine
* Asynchronous replication across the cluster (leaderless) using LWW

### Future
* Anti-entropy:
  * merkle trees
  * read repair
  * hinted handoff
  * bitmap version vector
* Quorum / sync writes
* Witness replicas
* Conflict resolution with vector clocks
* RocksDB data storage engine

## Example
```c++
...

#include "parrotdb/config.h"
#include "parrotdb/parrotdb.h"

int main() {
  const std::vector<std::string> cluster{
    "192.168.40.122:3112",
    "192.168.40.123:3112"
  };
  const parrotdb::Config config{"0.0.0.0:3112", cluster, true};
  parrotdb::ParrotDB db{config};

  const std::vector<uint8_t> key{1, 2, 3};
  const std::vector<uint8_t> val{4, 5, 6};
  db.Put(key, val);

  assert(*db.Get(key) == val);

  db.Delete(key);

  assert(*db.Get(key) == std::nullopt);
}
```
