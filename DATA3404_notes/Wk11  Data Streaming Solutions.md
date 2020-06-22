### General

__Define "data stream”.__

A data stream is a continuous, potentially unbounded input of tuples (of n-length) into a system. Data entering from the data stream does not necessarily follow a fixed sequence of time, there may be periods where throughput is high conversely low.

A typical example of data stream is anything that occurs continuously over time e.g. payment transactions, sensor readings etc.

---

__What are some properties for "queries" for data streaming systems?__

Querying data streams are different to typical queries of stored data. Because data is flowing through continuously, our operations on the data must not contain any actions involving ordering.

The operations must also be monotonic, that is, it must be w.r.t an increasing attribute e.g. time. This could be time or another non-strictly increasing attribute.

---

__Give an example of a stateful and stateless operator for data streaming processing.__

A stateless operator could be a sensor reading. Reading and processing its value is independent from past and future.

A stateful operator would be a stream processing function that outputs results based on multiple events e.g. windows, joins, aggregates etc.

---

__Decribe the different types of windows used.__

1) Sliding windows: t1-10, t5-15, t10-20 i.e. a sliding window of size 10 with interval 5.

2) Agglomerative window: t1-10, t1-15, t1-20 i.e. an expanding window.

3) Tumbling window: t1-10, t11-20, t21-30 i.e. contiguous, non-overlapping fixed side window.

4) Punctuation window: \<start\> DATA \<end\> \<start\> DATA \<end\> \<start\> DATA \<end\> i.e. data dependent window with “end-of-processing” marked by application that feeds the stream. 

---

__Explain the difference between event time and processing time.__

Event time is when data point occured and processing time is when the data po processed.

---

__Describe the 3 message delivery semantics__

1) At most once: Every tuple is read either 0 or 1 times

2) At least once: Every tuple is read 1 or more times

3) Exactly once: Every tuple is read exactly once.

Kafka guarantees “at least once” message semantic.

### Kafka

__Descibe Kafka and its major components. In your description, include:__

Kafka is a messaging system that employs the publish-subsribe model. Essentially you have a bunch of producers that push data into Kafka under pre-defined topic. Each message can only have 1 topic.

Each message is an individual data record. Each node in the Kafka cluster is called a broker.

The consumers will subscribe to particular topics in Kafka and retrieve the data from the Kafka intermediary storage. 

Typically you would also have an analytics engine on top on Kafka e.g. Spark/Flink.

__a) its 3 key capabilities__

The 3 main capabilities of Kafka is allowing messages to be published by applications and subscribed to by users according to the topic they are interested in.

The streams of records (messages) are replicated and fault-tolerant.

Users can process the streams of records as they occur hence it is possible to build a real-time analytics engine infront of it.

__b) its data model__

It utilises "dataflow programming" model.

<p align=center>
producer --> transformation --> sink
</p>

__c) replication model__

Replication is at the level of Kafka topics. Each Kafka topic is partitioned into multiple logs stored in different nodes. This means that we can access the data in parallel using multiple brokers. These brokers are able to interact with multiple consumers in a single consumer group to read in parallel the data.

In a single partition, each message has a single offset id that Kafka maintains. This allows for consumers to specify where they want to start reading and identify which messages they want.

Each specific message in Kafka can be identified as a tuple of `(topic, partition, offset)`.

Each data log is maintained for a configurable period of time.

A single replica of a partition is elected to be the leader. All read-writes go through the leader and it coordinates updating the follower partitions. When a leader fails, a new repica takes over.

Producers will write to the leader, as mentioned previously.

Note that you can have a consumer group with every consumer instances inside the group that reads each unique partition from the storage.

__d) performance guarantees__

The message order is maintained by Kafka. Often it is the case that hash partitioning by a partiticular attribute is desirable e.g. customer ID s.t. the order of customer activity is allocated to the same topic. Ordering is not necessarily preserved across topics.

With $n$ replicas, $n-1$ server failures are acceptable.

The message delivery guarantee is "at least once". 

---

### Flink

__Describe Apache Flink and why its useful for processing data streams.__

Flink uses pipelining for its execution. The records are forwarded immediately to the next stepp when the operator becomes available, rather than its processing being clearly separated a-la Spark.

---

__Describe the 3 different windows that Apache Flink has.__

As you would expect, sliding, fixed and session windows (basically punctuation windows)

---

__Describe the 3 notions of time that Apache Flink supports.__

1) Event time: Timestamps attached to the occurence of the event.
2) Ingestion time: Assigns wall clock timestamps when the record arrives.
3) Window processing time: windows are defined w.r.t to the wall clock of the machine e.g. a 1-minute processing time window collects elements for exactly one minute. 

These notions of time are used to define windows. 

---

__What are some of the differences between Apache Spark and Apache Flink?__

For fault-tolerance, Flink uses Chandy-Lamport distributed snapshots. That is,

1) The observer process saves its local state and sends out a snapshot token to other processes
2) Each process, if it is the first time it encounters the token, forwards its own state back to the observer and attachs the snapshot token to its subsequent messages to help propagate the token. 
3) When a process that has seen the token already receives a message that does not have the token, it forwards it to the observer process. This is because that message was sent because the snapshot "cut-off" and we need to save its state. 

---