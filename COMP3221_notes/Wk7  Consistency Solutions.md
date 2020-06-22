### __Concepts Overview__

**Why is the idea of consistency important w.r.t data storage and replication?**

The idea of consistency is to ensure that data replicated throughout the system is identical and changes are made to all the replicas within a reasonable timeframe.

From a user perspective, a user should be able to read the latest version for any copy and write the latest version.

Data replication across nodes provides scalability for performance and fault tolerance.

---

**When does a "conflict" occur?**

A conflict occurs when two nodes attempt to access the data independently and concurrently, and one of them wants to write (i.e. change) to the data.

---

**Define a consistency model and specify the two main types of consistency models.**

A consistency model is a contract between processes and the data store s.t. if the processes only certain rules, the data store promises to work correctly.

There are two main types of consistency models:

a) __data-centric consistency:__ focusing on the data itself - strict, sequential and causal consistency. Updates to the data are defined and considered in isolation.
b) __client-centric consistency:__ focusing on the end-user experience. This model ensures that for a single client there is consistency, as long as there are the client does not trigger multiple concurrent updates. Another perspective is we focus more on datastores that are mainly read and write-write conflicts rarely occur e.g. DNS.

---

**Define (memory) coherence. What is the difference between coherence and consistency?**

Memory coherence concerns one memory location, or the expected/desired behaviour of a single data item. Consistency focuses on read/write operations for a set of data items, and guarantees consistency defined by the consistency model for that set of data items.

For memory coherence, it is like a sequentially consistent model applied to a single data item. In other words, we are able to serialise all operations in that location s.t. the operations performed by processor appear in program order. 

---

**What are some examples of types of consistency models for both data-centric and client-centric approaches?**

__Data-centric__
- sequential consistency
- causal consistency
- eventual consistency
- continuous consistency

__Client-centric__
- monotonic read consistency
- monotonic write consistency
- read-your-writes consistency
- writes-follows-reads consistency

---

**Define "program order".**

The program order is the order in which events apear to be executed locally in the program.

```{Python}
x = 1 
y = 5
z = 23
```

The program order specifies that `x` is set before `y` before `z`. You cannot execute `z = 23` before `x` or `y` because that will violate program order.

---

**Define execution and serial execution.**

Execution is a sequence of read and writes on a set of data items executed by a set of processes.

Serial execution is an execution where each process executes all its operations one after another. So in order, no concurrency.

---

**Define equivalent execution.**

Two executions are equivalent if 

- they contain exactly the same read and writes
- if they are executed form the same process
- if all writes have the same input values
- if all reads have the same output values

---

### __Data-centric Consistency__

**Briefly describe the idea of sequential consistency. Draw a diagram with a example that violates sequential consistency.**

> The result of any execution is the same as if the (read and write) operations by all proceses on the data-store were executed in the same sequential order and the operations of each individual process appear in this sequence in the order specified by its program.

The idea of sequential consistency does not involve the notion of absolute time (as you will see in the example below).

Essentially, we want to ensure that each processes read values in the same order as all the other nodes.

If a process sees C, B and then A, then all other processes should see this order as well when reading the value.

Consider the example below.

![Screen Shot 2020-06-13 at 4.36.33 pm.png](resources/E0708036338A01E0C902C2178097B2D9.png =871x201)

It doesn't matter that `W(x)a` was written first and seen later, what matters is that all the processes see `b` before `a`. 

In this case, process 2 appears to have occurred before process 1.

If one sees `a` then `b` and the other `b` then `a` we have failed the sequential consistency model.

You can do `a` then `b` of course for all processes.

---

**Draw a diagram that is coherent but not consistent.**

Consider this example.

![Screen Shot 2020-06-13 at 4.42.42 pm.png](resources/65F692DFB2FB4B1D045CC6D99285DC5D.png =515x152)

![Screen Shot 2020-06-13 at 4.42.49 pm.png](resources/77D13CC86245E622F7EBCFB3EC8C7D10.png =740x152)

Here, we can never see the value of `A` begin read as zero, because the while loop holds until process 0 sets `flag = 1`.

So here although we have coherence w.r.t each individual process, the timeline diagram above is sequentially inconsistent.

---

**Define causal consistency and explain how it is different from sequential consistency.**

> Writes that are causally related (i.e., one happens before the other)
must be seen by all processes in the same order. Concurrent writes may be seen in a
different order on different machines.

First we should note that

$$\text{Sequential consistency} \Rightarrow \text{Causal consistency}$$

and that the implication is not $\iff$. We can see this in the example below.

![Screen Shot 2020-06-13 at 5.11.09 pm.png](resources/D0B5E184FD20195CF27F1D631696F2C9.png =733x180)

For casual consistency, we deal with dependences between data items and guarantee that the order will occur sequentially.

So we need to be able to identify when two processes are concurrent and when two processes are causally related.

Let's look at the example.

![Screen Shot 2020-06-13 at 5.11.18 pm.png](resources/957773CE50B594B8BF7E697E67EF29E0.png =907x180)

So here, we note that `R(x)a` and `W(x)b` occur sequentially on the same process. Hence, it may be that writing b to x depends on a computation involving reading the value of x. 

Hence we say that the 2 writes are causally related. Then all processes must see the reads in the same order, and thus (a) violates causal consistency.

For (b), the difference is that process 2 does not have `R(x)a`. Hence the two writes are treated as concurrent.

Hence there is no violation of causal consistency (only sequential consistency is violated).

For shared memory mulitiprocessors, commercialised memory models guarantee causal consistency.

![Screen Shot 2020-06-13 at 5.52.05 pm.png](resources/1C9BDD7DBE7ABD4E1A03270C517E6FB8.png =701x151)

![Screen Shot 2020-06-13 at 5.52.14 pm.png](resources/1EB0E9B83D0AFC739AF98264D18B2B69.png =724x140)

We can see the processes are dependent on each other, but we don't get any violates of causal consistency since the write in process 3 occurs after flag 1 and flag 2 are set.

---

**Define FIFO consistency and explain how it is different from causal consistency.**

> Writes done by a single process are seen by all other processes in the order in which they were issued, but writes from different processes may be seen in a different order by different processes.

This one is easy to undersyand. Writes done in a single process must be sequentially consistent, but writes from different processes don't need to be.

![Screen Shot 2020-06-13 at 5.48.16 pm.png](resources/E461A6B77BE0326ED95747DEAA8E5779.png =616x202)

As you can see in the example below, causal consistency is violated because `R(x)a` occurs before the other 2 writes, and sequential consistency is definitely violated.

However, for FIFO consistency, only `W(x)b` and `W(x)c` are considered causally related since they are from the same process. Hence the diagram does not violate FIFO consistency.

---

**Describe eventual consistency. What is the assumption that eventual consistency makes?**

Eventual consistency is a model that allows for non-simultaneous updates to replicas for write operations. When a read operation finishes, the local copy is the only updated one and the process exits without waiting for other replicas to be updated.

Then depending on the method, the replicas are all updated in due course further down the line. 

Eventual consistency assumes __no concurrent updates__. So if there are no updates for a very long time, all replicas will gradually become consistent.

If there are concurrent updates, then it will need to be resolved. This model assumes that such events rarely happen.

---

### __Replication__

**What is the idea of replication, and why does totally-ordered broadcast not scale well?**

The idea of replication is to keep multiple copies of the same data in various locations for scalability (network performance) and fault-tolerance (no single point of failure).

Totally-ordered broadcast uses Lamport's clock solution and that doesn't scale well.

---

**Describe the "primary backup" and "local write primary backup". What is the advantage of the "local write" version?**

__Primary backup__ 

All write operations for a data set is forwarded to the primary server that handles it. Then the primary updates and forwards write request to backup servers.

Each backup executes updates and acknowledges the primary. The primary the sends response back to client.

This guarantees sequential consistency but blocks on the backup updates because they need to respond to the primary server.

__Local write primary backup__

Similar to the previous except that a process will move the data item to its location and the process will become the new primary server.

Then it will update locally and acknowledge the client. This means the process will not block.

Finally it alerts the backups to execute the updates locally and the backups will respond to the primary accordingly.

---

**Describe quorum-based read-write replication. In particular, describe the constraints that must be followed and explain their purpose.**

Another method of replication that doesn't rely on the use of a primary server is called quorum replication.

This idea requires a voting system, where clients request and acquire permission from multiple servers before reading and writing a replicated data item.

Define a quorum system to be a set $S$ quorums that are mutually intersecting sets. That is, $\forall Q_{i}, Q_{j} \subseteq S, \; i \neq j, Q_{i} \cap Q_{j} \neq \varnothing$.

![Screen Shot 2020-06-13 at 7.30.53 pm.png](resources/14834F128E1E771B06DD721BAB98D7AB.png =757x278)

Let $N$ be the total number of replicas. 

Let $N_{R}$ be the number of read servers (a read quorum), and $N_{W}$ be the number of write servers (a write quorum). Then for each 

__For writes:__ forward update request along with `(version, node identifier)`. Once a sufficient number of quorum members have acknowledged it, respond to the client.

Requires 

$$N_{W} > \frac{N}{2}$$

to prevent write-write conflicts (you can't have 2 majorities at the same time).

__For reads:__ forward request to all replicas belonging to a quorum and pick the respoinse with maximum timestamp to show to the client (i.e. most recent copy).

Requires 

$$N_{W} + N_{R} > N$$

to prevent read-write issues i.e. you're either reading with a majority read quorum or a majority write quorum hence there is no issue. In addition, it also ensures that there is an overlap between the 2 quorums and hence the latest data is available. 

With both rules combined, they ensure that one-copy serialisability is maintained.

---

### __Multi-access Operations__

**What are multi-access operations and why do the previously mentioned consistency models fail?**

Multi-access operations are operations that access multiple data items per single operation. Previously our models have not considered that.

---

**What does ACID stand for and why is it important?**

A = atomicity
C = consistency
I = isolated
D = durable

ACID is a set of properties that combined guarantee database transactions being processed reliably.

A = all or nothing.
C = data is consistent.
I = concurrent operations don't interfere with each other, one transaction cannot read from any other transaction that has not yet completed.
D = a committed transaction remains in the system, i.e. it is permanent. Hence if the system says the transaction has succeeded then the transaction must have succeeded.

---

**Define serialisability.**

> the result of an execution (of multi-access
operations) is serializable if there exists an equivalent sequential
execution.

---

**Define sequential execution.**

Sequential execution occurs when a program has no loops or cycles in their program order.

Consider the two examples below.

---

**Give an example of serialisable and non-serialisable executions.**


![Screen Shot 2020-06-13 at 8.00.16 pm.png](resources/1D2B4E22F4587D7EB65108C09A97498F.png =795x293)

In the diagram above, we see that the program is not serialisable since we are writing `W(y)2` and reading `R(y)2` in the two different operations, which we assume here run concurrently.

![Screen Shot 2020-06-13 at 8.00.22 pm.png](resources/14AC362150A19F57D8B786E1B5F5F9C6.png =795x293)

This above diagram shows `R(y)0` which is serialisable in the direction of the arrows, assuming that y is initialised to zero.

**What is "real time precedence"?**

> if an operation o1 returns before another operation o2 is invoked (at a potentially different process) then o1 precedes o2 with respect (w.r.t) to real-time.

That is, we have serialisability w.r.t to real atomic time (loosely speaking).

![Screen Shot 2020-06-13 at 8.14.51 pm.png](resources/9D69BC434B06DDB36C54C87C9D71E726.png =724x132)

---

**Define linearisability. How it is different to serialisability?**

According to the lecture slides, linearisability is equivalent to sequential execution in the sense that it respects real-time precedence. 

---

**Give an example of both a linearisable and non-linearisable sequence of executions. **

![Screen Shot 2020-06-13 at 8.16.43 pm.png](resources/332DDBF69AA15099431197538E7C9A90.png =724x132)

In the diagram above `W(x)1` precedes the second `R(x)0` in real time. Hence this is not linearisable.

![Screen Shot 2020-06-13 at 8.16.49 pm.png](resources/64C43730A06F38E50EC804E3197DAC5F.png =724x132)

Hence we can see that first `R(x)1` and `W(x)1` technically are concurrent since `R(x)1` does not strictly precede `W(x)1`. Hence the first `R(x)1` returning either zero or one without violating linearisability.