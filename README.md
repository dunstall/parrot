# ParrotDB
Eventually consistent replication layer above RocksDB.

Possible techniques:
* Replicated writes
* Anti-entropy:
  * merkle trees
  * read repair
  * hinted handoff
  * bitmap version vector
* Quorum
* Witness replicas
* Conflict resolution (LWW or Vector Clocks) - make configurable

Provide a C++ library not an API.

## v0.1.0
* Basic async replication
* Functional testing

## Next
* Work though each class for make sure well factored, tested and logged
* Full functional testing
