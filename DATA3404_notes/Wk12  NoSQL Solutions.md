### __Concepts Overview__

**What are the 3 types of NoSQL databases we cover?**

We cover

- document stores (extremely flexible, nested schema)
- key-value stores 
- columnar stores

---

**What are some of the drivers for modern database technology?**

- **scalability** w.r.t data size and nodes
- **flexibility of schema**, grab all data and structure later for specific purpose, just collect first
- **de-coupling applications**, classic client-server model is insufficient
- **specific data models** e.g. network graphs 

---

**What advantages do these types of databases have over traditional SQL databases?**

The advantages are similar to the drivers of course, but a different perspective;

- **scalability** w.r.t much more suited for scaling-out instead of scaling up so cheaper as you're using commodity hardware.
- **flexibility of schema**, no need for full-fledged setup and expensive administrators to design and maintain
- **de-coupling applications**, classic client-server model is insufficient
- **more suited to agile**, good for frequent code pushes, quick iteration and agile sprints

---

**Draw up a table of characteristics for each of the aforementioned 4 types of NoSQL databases.**

![Screen Shot 2020-06-17 at 11.36.39 am.png](resources/662B0DAA26C2C21976C2E2F6BA550E4D.png =925x659)

---

### __Key-value Stores: DynamoDB and Cassandra__

**Describe Amazon DynamoDB. In your description, include:**

A Non-relational database that is a key/value (and document) store. AWS managements operating and scaling distributed systems e.g. hardware provisioning, setup and config, capacity planning, replication, software patching and clustering scaling. 

Dynamo by default supports eventual consistency and can be configured to have strongly consistent reads. Furthermore, it guarantees ACID properties at the user and regional level. 

For primary keys, Dynamo also supports a composite partition-sort key as a partition key element and a sort key element. For this multi-part key there is a hierarchy between the first and second component of the key, e.g. `UserID` and `Timestamp`. 

a) **Assumptions**

- most operations of simple read/write operations using primary keys
- no operation spans multiple entries
- data is small

b) **Implementation**

A huge dstributed hash table with replication at the nodes following the primary copy. 

![Screen Shot 2020-06-17 at 12.52.45 pm.png](resources/3E53324100CA9FAF2A433DF4C0E87C14.png =791x563)

Dynamo uses virtual nodes instead of physical nodes to help balance potentially uneven distribution of hashing. 

This way, we can also have load balancing - if a node goes down, we can disperse the workload (of virtual nodes) across other nodes.

c) **Versioning of data**

To access the data, the client execute read/write operations based on one of the two strategies:

1) We route read/write operations through a generic load balancer, which will select the node based on load information. In this case the client does not need to link Dynamo-specific code in their application.
2) Use a client library that is partition-aware and routes requests directly to the coordinator nodes. This results in lower latency. 

__Resolving conflicts__

- __Syntactic reconiliciation:__ system resolves conflicts automatically
- __Semantic reconciliation:__ conflict resolution pushed to application

> A load balancer is a device that acts as a reverse proxy and distributes network or application traffic across a number of servers. Load balancers are used to increase capacity (concurrent users) and reliability of applications.

Load balancers either operate at the transport layer level or the application layer level. Requests are distributed using some common algorithms. This includes:

- round robin
- weighted round robin
- least connects
- least response time

> Coordinator node manages read/write operations of a group of nodes.

Each data item is replicated at $N$ hosts where $N$ is an instance parameter. Each key $k$ is assigned to a coordinator node. This coordinator node locally stores each key within its range but also replicates the keys in the run at the $N-1$ clockwise successor nodes. Hence each node is responsible for the ring region between itself and its $N^{\text{th}}$ predecessor.

The list of nodes responsible for a particular key is called its preference list. This is done so that every node in the system is able to determine the identity of the nodes that should be in the list for any specific key. The preference list maintains more than $N$ nodes. 

The last caveat is that because Dynamo uses virtual nodes and hence it could be possible that all virtual nodes holding the replicas could be on one physical node, the preference list actually contains $N$ __physical nodes__.

Let's see how eventual consistency is supported during read/write operations.

d) **Supported operations and its management**

First we note that we have a quorum-like system of $R$ and $W$ nodes for read and write respectively, such that $R + W > N$.

Supports:
i) PUT: `put(k, obj)`.

The receiving coordinator generates the vector clock, writes locally and sends the request to all replicas on the top $N$ accessible nodes in the list.

The write fails if less than $W-1$ nodes respond.

ii) GET: `get(k)`

The coordinator sends a read for a key $k$ to the topmost $N$ reachable nodes in the preference list. It waits for $R$ responses. If successful then sends result to client.

In the case of inconsistencies, then it evaluates the causality of the set and returns all causally unrelated versions. For the conflicting data items, it goes into reconciliation process and eventually the older versions are overwritten.

iii) DELETE `delete(k)`

e) **Trade-offs vs. other databases**

Dynamo emphasises scalability, partition tolerance and availability. It aims to ensure that it is always possible to write to the database. In Amazon's philosophy, "when a customer offers us money we must take it".

Hence we use eventual consistency as per the CAP theorem.

Furthermore, query operations don't usually include scans, transactions etc. 

__Querying on non-primary key attributes__

Dynamo also supports querying on non-primary key attributes using global secondary indexes and local secondary indexes.

---

**What data structure is used to implement a key-value table? Explain how the table stores, deletes and replicates its contents.**

See answer in "describe DynamoDB".

---

**Hashing can lead to uneven distribution of data. How does Amazon Dynamo attempt to overcome this problem?**

See answer in "describe DynamoDB".

---

**Describe Apache Cassandra. In your description, include:**
a) **Data model**

The data model of Cassandra is optimised for querying. The tables are built based on what queries are required and not using relational database practices like normalisation, foreign keys etc. 

Tables may be de-normalised and in a "joined" form so we don't have to goal multiple tables before running a query.

In fact, joins are NOT supported in Cassandra.

If joins are required Cassandra leaves it to the client-side to implement.

b) **Supported operations and its management**

Cassandra supports 

- SELECT (table, key, columnName)
- INSERT (table, key, row)
- UPDATE (table, key, columnName)
- DELETE (table, key, columnName)
- BATCH: groups multiple INSERT, UPDATE AND DELETE executions into a single statement.

- CREATE INDEX
- DROP INDEX

c) **Properties for data replication and partitioning**

__Partitioning__

A partition is used with a consistent hashing function. By default, the key used is the primary key for rapid lookup. The fewer the partitions used the faster the response time.

You can also use a composite partition key using the primary key and another attribute.

Typically, the primary key is hashed to generate the partition key and the remaining fields are used as clustering keys to sort the data within a partition. 

The other fields that are not primary key fields can be indexed separately to improve query performance.

__Replication__

Cassandra uses multi-master replication with versioned data (similar in ideas to Dynamo - infact Cassandra mentions that it borrows many techniques from Amazon's Dynamo) and tunable consistency.

In fact, for tunable consistency you can specify how many replicas must respond with how many replicas you want e.g. `ONE`, `QUORUM`, `ALL` `EACH_QUORUM` (majority for each data centre) etc. 

Writes are always sent to all replicas, regardless of consistency level. The only difference is how many responses the coordinator waits before responding to the client.

For reads, the coordinator only requires enough replicas to respond to satisfy the consistency level.

The __replication factor__ specifies how many replicas should a data item have. The replicas that are written to must exist in distinct physical nodes (as opposed to virtual nodes). 

You can configure this to the rack or data centre level.

When a mutation occurs, the coordinator finds out the token range the data belongs to (nodes in a DHT) and executes the mutation on the replicas according to the __ReplicationStrategy__.

Replication strategies include 

__Network topology strategy__

This allows you to customise a replication strategy for each data centre in the cluster. This is recommended even if you use only a single data centre. 

This strategy also attempts to choose replicas within a datacentre on different racks. There are some surprisingly implications for "rack-aware" behaviour so instead admins choose to configure all nodes in a single availability zone or failure domain as a single "rack".

__SimpleStrategy__

The straightforward approach. You specify a replication factor and Cassandra creates that number of replicas in any node, ignoring any network topology.

d) **Cluster management**

__Gossip__

Replication and partitioning protocols rely on knowing which nodes are dead or alive inn the cluster so that operations can be optimally routed.

Cassandra uses a gossip protocol that propagates basic information to neighbouring nodes. The gossip dissemination is run independently and periodically. 

It uses seed nodes (nodes that can bootstrap into a particular cluster/ring without seeing other nodes) and these seed nodes also act as hotspots as any node will try to gossip with a seed node if it can't gossip with non-seed nodes.

__Failure Detection__

Every node in Cassandra runs a variant of the __Phi Accrual Failure Detector__. The main mechanism to detect failure is using a heartbeat. 

The main point is that whether a node is `UP` or `DOWN` is a decision made by each independent node. This information is not propagated with via gossiping.

Heartbeats are propagated but nodes do not consider each other as `UP` until they can successfully contact each other. 

---

### __HBase__

**Describe HBase. In your description, include:**
a) **Data model**

The basic structure of HBase requires a slightly deeper dive as it is beyond just rows and columns of a typical relational database.

Have a look at the two diagrams below. They give an idea of HBase's basic structure.

![Screen Shot 2020-06-17 at 4.12.00 pm.png](resources/D574C441B100DF2E7C7AD523C185D549.png =703x265)

![Screen Shot 2020-06-17 at 4.12.12 pm.png](resources/A89B5A6C684C00B8D0E4CE93C1CBD445.png =683x499)

So we have the following components:

- __Row:__ consists of a row key and one or more columns with values. Rows are sorted alphabetically by the row key. 

This is important as the row key should allow related rows to be stored near each other e.g. website domains (in the diagrams above). 

- __Column:__ The column consists of __column family__ and __column qualifier__
  - column family: physically co-located set of columns and their values (for performance). Each column family has a set of storage properties e.g. caching, compression, encoding. Each row in a table has identical column families but a column family could be empty for a particular row.
  - column qualifier: indexes a given piece of data in the column family. 

Column families are fixed at table creation but column qualifiers are dynamic and can be changed and thus are often different between rows.

- __Cell:__ The components above combine to form a cell. Each cell contains a value and timestamp, which represent's the version history.

The timestamp by default represents the time on the `RegionServer` when the data was written. However, you can specify a different timestamp value  when you put data into the cell.

b) **Supported operations**

- GET
- PUT
- SCAN
- DELETE
- CheckAndPut
- CheckAndDelete

Note: Most operations are based on `(row-key, column, timestamp)` triples. 

c) **Storage implementation** (conceptual i.e. the tuple and physical hierarchy)

Because most values stored inside a column family differ greatly and column qualifiers are mutable, it makes sense for HBase to be a __column store__.

In this case, the empty values of a column qualifier are not stored at all, and neither are empty cells.

The tables are partitioned into regions over a continuous range with a defined start and end row. Regions are disjoint and served only by a single region server at any point in time.

A region consists of many __stores__ which correspond to column families. A store contaihns one memstore (for update logging) and zero or more file stores (StoreFiles, wriitten as a file into HDFS). The data for each column family is stored and accessed separately.

When a table is first created, HBase will allocate one region for the table by default.

**Regions are the units of distribution around a cluster.**

The diagram below gives an intuitiion of what the storage implementation looks like

![Screen Shot 2020-06-17 at 4.58.25 pm.png](resources/6A5EEFA8E5A4805DA8EE1B57725B4F5F.png =683x464)

The RegionServer process manages the regions that are distrbuted around the cluster. For HBase, there is Master node and multiple RegionServers. This configuration is built on-top of HDFS and Zookeeper. Hence the fail-safety comes through HDFS replication. 

![Screen Shot 2020-06-17 at 5.07.41 pm.png](resources/4B3DFC0B448D1404D42F511FD74F3AAB.png =672x398)

The Master manages schema edits and reallocation of regions when crashes happen. It holds a light load.

The hierarchy is like

- Master: assigns table regions to RegionServers
  -  RegionServer: Holds $0 - m$ regions
      - the RegionServer keeps commit log of every update
      - Updates go to RegionServer's commit log first before Region
      - Regions are periodically moved by Master's LoadBalancer.
      - Regions are split when they are too big and RegionServer manages this.
    - Cluster:
        - carries $0 - n$ labelled tables.
      - Stores:
          - one store for each column family
          - all values for the same column family are stored together
          - sparse rows are not stored
          - has __MemStore__ that takes on Region writes and is flushed when full
          - Flush adds a __StoreFile__; no in-place updates or inserts to existing StoreFiles needed and is also not supported by HDFS

![Screen Shot 2020-06-17 at 5.13.19 pm.png](resources/CEDE07921CB3B7ED8B4A5A07CA08A673.png =700x441)

d) **With its storage implementation in mind, describe the implementation of its operations**

The request flow works something like:

1) Client goes to Master for a specific region
2) Master supplies client with Region specification and host
3) **Client caches this** and goes directly to RegionServer afterwards. If there is a fault asks Master for new info to refresh cache.
4) Region locations are stored in catalog tables.

e) **Restrictions of HBase's data model**

- HBase tables use only the primary index, the row key. There are no integrity constraints or secondary indexes
- No column typing, just straight byte arrays
- Scans and queries can only select a subset of available columns, even by using a wildcard
- Only 3 main types of lookup is supported
  1) Point-lookup using row key (and timestamp)
  2) Full table scan
  3) Range scan from region start to end

---

### __MongoDB__

**Describe MongoDB. In your desciption, include:**
a) **Some advantages of its document-model storage**

MongoDB uses a document storage model that contains nested key-value pairs for maximum flexibility. Just think JSON files.

![Screen Shot 2020-06-17 at 5.22.52 pm.png](resources/517805B00A8E50827347425ECDE4B87E.png =584x319)

For example the JSON can look like this:

![Screen Shot 2020-06-17 at 5.28.35 pm.png](resources/B8EC17AE27DEDF8546C7DE52ADCD65D2.png =392x418)

The data is strongly typed and adaptable to change (polymorphic, dynamic and govern (enforcing structure with JSON schema)).

Given that JSON-style documents map to objects then it is good for applications that look for just a persistent data store.

However, the consequence of this data structure is that it does not support SQL queries as we know it.

![Screen Shot 2020-06-17 at 5.28.12 pm.png](resources/EA9167D9139542E576037B33DBC3BD77.png =584x319)

b) **Supported operations**

- insertion: `CreateOne()`

![Screen Shot 2020-06-17 at 5.43.27 pm.png](resources/C65282CC0FB591DDBBFCF2EF68AC42AE.png =483x122)

- get: `find()`

![Screen Shot 2020-06-17 at 5.43.38 pm.png](resources/F86C96D4C88958D31A31ECC870326498.png =570x73)

- Implicity equality predicate and implicit conjunction (__and__)

![Screen Shot 2020-06-17 at 5.44.55 pm.png](resources/74321DBE16072BD9EB452FB7D4A85570.png =558x46)

- Sorting

![Screen Shot 2020-06-17 at 5.44.50 pm.png](resources/D499546DEF7B8EC06EA17494319F8A51.png =598x30)

- aggregations

![Screen Shot 2020-06-17 at 5.45.06 pm.png](resources/E6A313924F19C5B692313D63C173614E.png =530x385)

c) **Ideas behind implementation of its scalability**

Scalability of MongoDB utilises several ideas

__Automatic data partitioning__

Data is automatically sharded and placed into multiple machines whilst preserving order. As a user, you can create zones of sharded data based on the shard key.

Each zone can have one or more shards and a shard can associate with any number of zones (many:many).

This helps with deployment configurations e.g. isolate specific subset of data on a specific set of shards, move relevant shards to geographically closer region to client base and routing data to shards based on performance of shard hardware.

Zones cannot share ranges or have overlapping ranges. 

__Master-slave replication__

Asynchronous, primary-server replication within one 'shard'. The master receives updates and propagates to slave nodes.

The main goal is availability and or query slaves directly which guarantees only eventual consistency. This is called __read preference__ (read either primary, secondary or nearest node)

__Load balancing__

As you would expect.

d) **Indexing**

MongoDB's data model supports secondary indexes e.g. B+ trees on any attribute, even nested ones. Multi-column indexes are good too.

![Screen Shot 2020-06-17 at 5.59.40 pm.png](resources/1AE707A9AC8A68A0BC71D3113E8E4D0A.png =707x385)

e) **Internal optimiser**

MongoDB's optimiser uses __First-Past-the-Post (FPTP)__ idea where the optimiser will generate potential execution plans and MongoDB will actually test these plans with data in parallel, round-robin scheduling to determine which plan is best. The first one to return the $101^{\text{th}}$ row result is chosen as the winner.

This is a practical method that considers hardware and system load but initialisation of index plans counts as a step but does not return a row, and thus it disadvantages index plans.

You can use `db.collection.explain()` to understand the query.

---

f) **Storage layer and its API**

MongoDB's storage API allows different stores to be used e.g. WiredTiger main-memory vs. Memory mapped files (mmap).

The big picture looks like this:

![Screen Shot 2020-06-17 at 6.05.21 pm.png](resources/2793354773B6CFD10AC8196D0F00FBE6.png =592x312)

The mmap structure looks like this:

![Screen Shot 2020-06-17 at 6.06.52 pm.png](resources/6F63712468508DA364F9798AD6F0E320.png =653x333)

Let's discuss using mmap vs. WiredTiger storage

__Mmap__

Mmap uses OS cache and storage. So we don't need to double buffer and there is support for page faults.

However, the OS is not optimised for database-style access and you cannot change the replacement policy of the OS buffer.

You also need WAL (write-ahead log) for consistency for in-place updates, and OS system don't do this naturally either.

Mmap also loves using alot of RAM, and if you run out of memory sharding/scale-out is necessary. 

__WiredTiger storage engine__

![Screen Shot 2020-06-17 at 6.09.42 pm.png](resources/A2534FEE2752EF907F0F35A4DCA1F006.png =342x486)

WiredTiger provides many features, including:

- document-level concurrency
- block-based caching
- tree-based data ccess
- disc compression
- consistency without journaling (WAL) with no in-place updates, in-memory consistency via snapshots, writing a page combines previous page image with in-memory changes
- it performs better on some workloads e.g. multi-threaded, write-heavy.

---