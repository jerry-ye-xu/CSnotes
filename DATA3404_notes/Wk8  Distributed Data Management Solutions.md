### __Concepts Overview__

**What are the 3 distributed DBMS architectures? How do they differ? When would you use each one?**

The 3 distributed DBMS architectures are:

1) Shared memory
2) Shared disk
3) Share nothing

1) __Shared memory:__ In a shared memory network, nodes are simply CPUs and every node shares a common storage location and memory. Any data stored in memory can be shared with every other processor. This allows efficient interprocess communication (via the main memory). 

However, the communication between memory and processes becomes a bottleneck, and typically does not scale past 32-64 processors.

Hence this is used for lower degress of parallelism.

2) __Shared disk:__ In a shared disk architecture, the different nodes (processors) in the network are connected to an identical storage disk, with each individual node having its own CPU.

This provides some fault tolerance since a new node can take-over the intermediary operation in a failed node since all storage is shared. 

This avoids the "memory bus" problem, but now the intercommunication between processors is slower.

3) __Share nothing:__ In a share nothing architecture, each individual node posses its private memory and storage disk. This means that there exists no bottleneck as in the previous two cases, but IPC will be slower. This is because if we want to access data from another node this would involve securing a connection and transferring the request and the data. 

Note: Shared disks and shared architectures can be write limited in different ways. For shared disks, caching locally in memory is essential for performance but when a client issues a write, we would need to lock all cached copies in the memory, which slows down the system non-linearly as you scale. You typically don't lock on disk beecause of performance.

For share nothing, the limitation occurs when the data is replicated or partitioned across clusters. Then we would require a a distributed lock for transactional writes that span data on multple nodes (i.e. a distributed two-phase commit)

---

**Give an example of each of the architectures.**

Shared memory: Linux/Mac OS/Windows operation systems are all shared-memory, as you might have guessed.
Shared disk: Oracle
Share nothing: Cluster of linux nodes 

---

**What are the 3 goals for a shared data system?**

The 3 goals are:
1) Consistency: When data is read and written to, how do we ensure that the replicates across the system are always the same when accessed by the client?
2) Availability: How do we ensure that the system is always up and running and we are able to read/write to our data without failure?
3) Partition Tolerance: We want to ensure that if communication between two nodes drop during execution, the cluster continues to function. 

As will be alluded to in the CAP theorem, in order to obtain partition tolerance, you would have to give up consistency because when communication drops, the nodes will be out of sync.

---

**State the CAP theorem.**

You can at most have two of the three following properties: consistency, availability and partition tolerance.

- What is a general rule of thumb for latency across networks?

LAN: 1x $\approx$ 0.5ms
co-LAN: 2-7x $\approx$ 1-3.5ms
WAN: 22-360x $\approx$ 44-720ms

---

### __Data Partitioning__

**What are the two types of data partitioning? Describe the ways a dataset can be partitioned.**

A data set can be partitioned horizontally or vertically.

In a horizontal partition, we split the table by rows such that each partition contains the same schema but unique rows. 

In vertical partitioning, we split the table by columns. As such we have that each partition contains an ID reference and a part of the columns associated with the ID. You can think of it as "dividing up the schema".

---

**Describe data sharding. What are some of its advantages and disadvantages?**

Data sharding is a type of horizontal partitioning. The data is broken up into "logical shards" that are then distributed across the network as "physical shards".

Partitioning strategies are executed on a particular attribution in the data. The different methods of partitioning include range, hash and list partitioning. 

You can also do round-robin partitioning, but this makes index/range access queries much more inefficient.

Note: List partitioning is partitioning based on membership within sets.

Sharding is useful because it allows for easy horizontal scaling and fault tolerance. If your queries require access to only one shard, then it will be very fast. If joining two non-located tables are necessary then it may not be as efficient.

However, sharding may lead to imbalanced partitions, which then need to be re-adjusted overtime. Another drawback is that it is very difficult to revert back to the original unsharded architecture. Lastly, sharding isn't supported by every database engine.



---

**Define inter-query vs. intra-query parallelism.**

Inter: different queries accessing different partitions that are stored in different nodes.
Intra: same queries accesing several places in parallel.

---

**What is the difference in query optimisation considerations between distributed and local optimisation plans?**

For distributed query optimisation, we also have to consider 
a) communication costs
b) local site autonomy

Local site autonomy refers to the ability for a remote database to be fully independent. This would mean that the local DBMS manages the intregity, security and storage of the data.

There is a trade-off of both local autonomy and location transparency, since the later requires 100% availability of data at the remote location.

To improve location transparency, companies like Oracle will introduce snapshots to store a local copy of a remote table. In theory this can be refreshed very frequently e.g. 1/sec but in practical there may be downtime or latency.

c) distributed join methods

---

**What are the two evaluation strategies for query evaluation? How do they differ and what is the advantage of each?**

a) Materialisation
b) Pipelining

Materialisation refers to the storage of intermediate results on disc before feeding it as input to the next operator. This used to be the only way because of memory constraints. 

Pipelining is passing intermediate results (the tuples) to the next operator and executing immediately if it is not blocked. The intermediate results are not stored on disk.


Pipelining requires large amount of memory buffers. If there is insufficient buffering, thrashing will occur, that is the virtual MMS will swap memory pages in and out of the disk, which is extremely expensive. If this is severe, the query performance could be potentially worse than materialisation. 

---

**State the 4 different types of distributed joins.**

a) Local reference tables
b) Broadcast join
c) Distributed-shuffle join
d) Fragment-and-replicate join

---

### __Data Replication__

**What some different models for data replication?**

We have, synchronous replication and asynchronous replication.

Synchronous: the transaction does not commit until all replicates have been updated. The data distribution is made transparent.
Asynchronous: the transaction is committed to one node and the need to update is propagated to other nodes. The other nodes are updated periodicially. In this case, the user must be aware of this. 

---

**What is the key principle for data replication?**

If we replicate, then we must ensure that we can read from any replica and it should be as up to date as possible.

---

**What are the two main different types of replication concerning storage requirements for replication?**

One can engage in complete replication, where each table is replicated completely and there are multiple copies of every record.

In partial replication, only some of the data is replicated. This could be based on importance, usage etc. The system design for partial replication is much more complex.

---

**What are the levels of consistency we can provide in a DBMS?**

There are two levels of consistency:
a) Always consistent
b) Eventually consistent

---

**How are writes propagated? What about propagating to replicas?**

There are two methods of write propagations.

a) __Procedural capture:__ The SQL is executed at the replica when invoked by a trigger. This could be an issue if the state of the local copy is different when the original query was first executed.
b) __Log-based capture:__ You store the values and update directly at the replica. The challenge with log-based capture is that the implementation must account for the structure of the log, and thus may not be transferrable across different DBMS.

Note: This is for primary site asynchronous replication.

---

**What is the difference between lazy (asynchronous) and eager (synchronous) replication?**

For synchronous replication, we update all the replicas inside original transaction. This is clearly good for consistency but not as good for performance. 

Asynchronous replication refers to the practice of updating only one copy and then returning to the client. The DBMS then proceeds to apply the writes to other replicas in its own time. This violates the principle of "distributed data independence" - that is, as mentioned earlier, the user must be aware of this fact.

---

**How does a DBMS ensure that transactions see the same value regardless of which replicas they access?**

Typically one of two techniques are used:
a) __Voting:__ The transaction requires a majority of copies to be written. That is, if there are 10 copies and we update 7 of them, then at least 4 copies must be read to ensure we have the latest value. As you might expect, the copies have a version number.
b) __Read-any-write-all:__ This idea states that we must write to all copies when we update. This is generally more attractive as you often don't want to be reading multiple copies of the data to discern whether you have the most update-to-date values. This technique is more attract when reads are far more frequent than writes. 

--

**What is the different between primary copy and multi-master replication?**

Pirmary copy and multi-master replication are two different flavours of asynchronous replication.

For primary copy replication, we have one replca be the primary copy. All writes completed on this replica first and then propagated. The remaining copies are called secondary copies. The other copies will __subscribe__ to the primary copy. The two steps involed are 1. capture (changes) and 2. apply (changes).

For P2P replication, any replica can assume the role of a primary copy. The changes must be propagated later, but we now have an additional problem of conflict resolution, we it is possible to simultaneously write to two "primary" copies.

One of the ways to overcome this is to sever the roles of replicas. A particular replica is only allowed to update a certain portion of the data. Another way is to lock all updates by alerting other replicas s.t. only one master node can be assumed at a time. 

---

**What the advantages and disadvantages of synchronous replication?**

The obvious advantage is strong consistency. 

The disadvantages are (time) performance and availability. We will need to send locks to remote sites and while waiting for the response, hold onto other locks. 

If sites or links fail, the transaction cannot commit until the nodes are back up.

The **commit protocol** that is required is expensive. 

There have been ideas of using **group communication protocols** to overcome this. Essentially, 

**Describe MongoDB's replication model.**

MongoDB uses primary-copy asynchronous replication. 

---

**What is the ideal scenario and most common approach in practice w.r.t. data replication?**

| | Primary copy | Multi-master
|---|:---:|:---:|
| Sync | most approaches in practice | |
| Async | | ideal world |

---

**Describe the fundamental components of a distributed file system (DFS)**

A DFS is a client-server architecture that allows storage and access of files. 

The DFS uses a uniform naming convention and mapping scheme to keep track of where files are.

Some examples include Ceph, HDFS and Alluxio.

Typically, a barebones DFS does not have replication and migration capabilities and thus lacks in reliability and availability.

---

**What are some requirements for big data analysis?**

- Scalability
- Reliability

Consistency is not as important.

---

**Describe the fundamental components of Hadoop distributed file system (HDFS)**

HDFS has a master-slave architecture. 

The master node takes care of name space, access control, data location control, metadata and data replication. The master node is also known as the **NameNode**.

The NameNode constantly updates the "data location" information to know where the slave nodes are.

Typically TCP is used for client-node communication, and often directly to slaves. The slave nodes are known as **DataNodes**. THey are responsible for serving read/write requests to and from the client. They perform block creation, deletion and replication upon instruction from the NameNode.

HDFS files are partitioned into blocks and replicated, with 64MB/block and 3 replicas  asthe default.

HDFS assumes a write-once-read-many model. 

---

**How does HDFS handle scalability issues?**

NameNodes are a potential bottleneck for scalability. We can minimise storage requirements for each file and involvement in read/write (restrict it to be only at the beginning) but eventually you will hit a ceiling.

Note that the actual data movement is independent of the NameNode.

HDFS addresses the scalability issue associated with have a single NameNode (in fact, a single NameNode can accommodate for a thousand or so servers) by using "Federated HDFS" which essentially has multiple NameNodes that store details of all blocks but only manage a specific portion of the namespace and/or blocks.

---

**Describe the HDFS architecture.**

It is described in the answer above.

---

**Describe how read/write are implemented in HDFS.**

__Read__

The client translates the file name and byte offset to a "data block index" and sends this information to the NameNode requesting for the location. The NameNode replies with "block handle" and the location of the replicas. The client caches this information so that it doesn't need to ask the NameNode next time.

Then it sends a request to the nearby replica specifying block handle and byte range. The DataNode sends the blocks through.

__Write__

Writes are cached locally in a buffer and delayed until a new block is full. When the block is full a request to the NameNode is made, asking the address of the DataNode. 

To avoid conflicting rights, NameNodes issue a "lease" (a lock essentially) when clients request to open a file for a write operation.

Replication is done by replica-to-replica pipeline. This maximises the client's abilty to stream. 

Essentially the data flow is 

a) Client will obtain the lease (or wait) and the NameNode replies with identity of the primary copy AND the replicas. The client pushes the data to all of the replicas. The client sends a write request to the primary node N1.

N1 will update the file and pushes the write request to N2 after it's done and tells N2 that N3 still needs to be updated. Then N2 will push to N3 when it is done.

---

**How is replication implemented in HDFS?**

The NameNode makes all decisions regarding replication:
- where
- when (i.e. if a block needs another replica)
- migration

The usual, except for one interesting part.

HDFS replication uses "rack awareness" to put replicas 2 and 3 on the same rack. This is because the probability of a rack failing is much less than a node. Hence if a node fails the network latency is not increased as much as the next replica is within the same rack.

This especially improves write performance.

**What are the 3 reasons for data replication in HDFS and why are they important?**

1) Block creation: used to balance disk utilisation and creation events
2) Re-replication: Ensure # of replicas are maintained. Replicas can be prioritised or rate-limited to reduce impact on client traffic. Replica placement heuristics similar to block creation
3) Rebalancing: periodically examines distribution and moves replicas around.

---

**What are some common CLI commands for HDFS?**

```{bash}
hdfs dfs -ls <dir>
hdfs dfs -mkdir <dir>
hdfs dfs -rm <file>
```
etc.

---

**How can the `DistributedCache` in Apache Hadoop be used for distributed join processing?**

> Hadoop's DistributedCache can be used for a Broadcast Join by loading a (small) join table into this cache which then gets used in a number of JoinMappers.

Essentially, you load the smaller of the two tables into the `DistributedCache` and then write a Join-Mapper function that locally joins each tuple with every tuple of the local copy.

As from the docs:

"""
`DistributedCache` is a facility provided by the `Map-Reduce` framework to cache files (text, archives, jars etc.) needed by applications.

Applications specify the files, via urls (`hdfs://` or `http://`) to be cached via the JobConf. The `DistributedCache` assumes that the files specified via urls are already present on the `FileSystem` at the path specified by the url and are accessible by every machine in the cluster.

The framework will copy the necessary files on to the worker node before any tasks for the job are executed on that node. Its efficiency stems from the fact that the files are only copied once per job and the ability to cache archives which are un-archived on the workers.

`DistributedCache` can be used to distribute simple, read-only data/text files and/or more complex types such as archives, jars etc. Archives (`zip`, `tar` and `tgz/tar.gz` files) are un-archived at the worker nodes. Jars may be optionally added to the classpath of the tasks, a rudimentary software distribution mechanism. Files have execution permissions. In older version of `Hadoop Map/Reduce` users could optionally ask for symlinks to be created in the working directory of the child task. In the current version symlinks are always created. If the URL does not have a fragment the name of the file or directory will be used. If multiple files or directories map to the same link name, the last one added, will be used. All others will not even be downloaded.
"""

