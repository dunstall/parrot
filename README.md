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

Provide a C++ library not an API.
