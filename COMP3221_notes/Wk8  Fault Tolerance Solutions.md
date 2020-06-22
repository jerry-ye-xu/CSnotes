### __Concepts Overview__

**What is the difference between failure, fault and error.**

W.r.t a distributed system;

- __failure:__ is when the system does not meet its specified requirements 
- __error:__ is something that could potentially cause a system to failure
- __fault:__ is the result of an error 

---

**Explain the 3 different types of faults.**

- __transient:__ an unexpected, random fault that will likely never occur again
- __intermittent fault:__ a fault that occurs periodically and/or reoccurs often. 
- __permanent fault:__ a fault that persists indefinitely until it is fixed.

---

**In a distributed system we want our system to be dependable. Outline the 4 characteristics of dependability.**

- __availability:__ probability that a system is up and running (correctly)
- __reliability:__ ability for a system to run continuously 
- __safety:__ when a fault occurs e.g. the system goes down, no adverse affects occur to the data, users etc. you only lose access to the service.
- __maintainability:__ how easy is it to maintain/repair in the event of a fault.

---

**Define failure models and name and describe 4 failures.**

- __crash failure:__ when the system goes down and becomes unavailable.
- __omission failure:__ when the server fails to respond to incoming requests.
  - receive omission: when the client's response fails to receive
  - send omission: when the server's response fails to send
- __timing failure:__ when a server's response time is not within a specified time interval.
- __response failure:__ when the server's response is incorrect
  - value failure: the response's value is wrong
  - state transition failure: the server deviates from the correct flow of control

---

**What is the most serious type of failure, and what is it called?**

The most serious type of failure is called __Byzantine failure__, and it is an arbitrary failure of any type, any place and any time.

---

**Give 2 examples of the type of failure you defined above. **

1) The server produces an output that is not part of the pre-defined set of answers, but it cannot be caught as incorrect.
2) A single/group of servers that are maliciously producing incorrect answers everytime and bypassing checks.

---

### __Consensus Overview__

**Describe two high-level ways we can improve fault-tolerance in distrbuted systems.**

- __resilience by grouping:__ you can organise several processes/devices into a group and replicate them. Then a process can initiate as a backup when one goes down. When a message is sent, all members will receive the message.
- __group management:__ management several processes/nodes as a group. A process can join/leave anytime and be part of several groups. This flexibility will also help improve fault-tolerance.

---

**Define "k-fault tolerant".**

k-fault tolerance refers to how many nodes can be faulty before the system fails to meet its specifications.

---

**Define the consensus problem.**

The consensus problem is obtaining agreement amongst a number of processes for a single data value. Some of the processes could fail or be malicious attackers so in order to ensure that the correct value is always agreed upon, we need to use consensus protocols that are fault tolerance.

The processes need to announce their chosen value, communicate with each other and agree on a single value.

---

**What are the 3 requirements for solving a consensus problem?**

To solve a consensus problem, we need to ensure the following 3 things.

1) __Termination:__ in every admissible execution every non-faculty process $p_{i}$ eventually obtains some value $v_{i}$. That is, a correct process must decide on some value.
2) __Agreement:__ in every execution, if $p_{i}$ outputs $v_{i}$ and $p_{j}$ outputs $v_{j}$ $\forall i\neq j$, then $v_{i} = v_{j}$. That is, all processes must decide on the same value.
3) __Validity (integrity):__ in every execution, if, all correct processes $p_{i}$ propose $v_{i}$, then any correct process $p_{j}$ must also propose $v_{i}$. That is, the value that is processes by a correct process must be the same as other correct processes.

Note: The propose value initial is undefined or empty or null. It is up to the process to assign or propose a value.

---

**What are some of the challenges associated with distributed consensus?**

The general goal of consensus is to have all non-faulty processes reach consensus on some issue and to establish that consensus within a finite number of steps. 

However, whether distributed systems can actually reach consensus depends on their protocol. There are 4 main factors:

1) __Synchronous vs. asynchronous:__ a synchronous process operates in lock-step mode. That is, if a process is at step $c+1$, then every other process has taken at least 1 step, $\forall c\geq 1$.
2) __Bounded vs. unbounded communication delay:__ Bounded delay occurs when messages are delivered globally and a pre-determined time is known by all nodes.
3) __Order vs. unordered message delay:__ Ordered messages means that messages from different senders are delivered w.r.t real global time to all processes.
4) __Unicasting vs. multicasting message transmission:__ to one node or to multiple nodes.

Note: Most distributed systems in practice assume that processes behave asynchronously, message transmission is unicast and communication delays are unbounded. 

Hence we would require ordered (reliable) message delivery.

---

**Map out a table of possibilities for distributed consensus, with a/sync vs. un/ordered vs. uni/multicast vs. un/bounded messages. Label the boxes "N/A" for any combination where it is impossible to reach consensus.**

It has been theoretically proven that configurations of a distributed system are impossible to reach consensus with.

![Screen Shot 2020-06-15 at 9.53.14 pm.png](resources/B9EF4F64010843E687D7BE658FDF8957.png =735x331)

---

### __Consensus Algorithms__

**Describe a crash-tolerant synchrnous solution. Include in your description**
a) __The main idea__

A crash-tolerant solution assumes a few things. The most important is that the only failure is a crash-failure and not a Byzantine failure etc.

Furthermore, only a maximum of $f$ processes can fail by crashing. Then the algorithm runs for $f+1$ rounds. Hence with no failures, it runs for 1 round.

b) __The algorithm__

$P = \big\{p_{1}, p_{2}, \cdots, p_{m}\big\}$ be a set of proceses.

$V = \big\{x_{1}\big\}$ be a set of known values, where $x_{1}$ be an initial proposed value of $p_{i}$

```{pseudocode}
for k in [1, ..., f+1]:
  broadcast values 'v' of process P to all other processes P'
  for all P' not P:
    receive 'v' from P
    V = V + 'v'

y = min(V)
```
where $y$ is the output of the consensus.

c) __A brief proof for the algorithm__

To prove that this is a valid consensus, we need to show that the validity, agreement and terminations hold.

- __validity__: we take the minimum of the set $V$, and it is a proposed value by at least one of the processes.
- __agreement__: as per the algorithm, the consensus value is $y=\min(V)$ for all non-faulty processes.
- __termination__: the algorithm ends after $f+1$ rounds and since theoretically we have a finite number of nodes in the system, termination is guaranteed in a finite number of steps.

d) __A brief example__

![Screen Shot 2020-06-15 at 10.36.35 pm.png](resources/DD22A272C654E80173657D6373FFA656.png =153x109)

Consider this example where $p_{i}$ will broadcast it's value $i$.

Suppose $p_{1}$ fails and never recovers.

In the first round, $p_{3}$ receives 2 and $p_{2}$ receives 3. Then $p_{2}$ and $p_{3}$ have $V = \big\{2, 3\big\}$. 

In the second round, if $p_{1}$ does not recover, then $V$ remains the same and we take $y = \min(V) = 1$.

However, if $p_{1}$ recovers, then it broadcasts it's value to everyone and we need up with $V = \big\{1, 2, 3\big\}$ and hence $y = \min(V) = 1$.

---

**Describe a Byzantine-tolerant synchronous solution. Illustrate the ideas with a small example.**

In a Byzantine-tolerant synchronous solution, we have synchronous unicast. 

A maximum of $f < \frac{n}{3}$ processes can fail, and the failure is Byzantine. Because of this requirement, Byzantine-tolerant consensus cannot be achieved with $n \leq 3$ processes. 

Now, how this works is every process sends its values to every other process, and we take the majority. So fairly straightforward.

Assume that $p_{3}$ is a faulty process and sends letters instead of numbers.

![Screen Shot 2020-06-15 at 11.02.52 pm.png](resources/758C6F150B70907C41333FA6F0B785A3.png =352x362)

So let's have a look at what the nodes received

| Sender/Received| 1 | 2 | 3 | 4 |
|:---:|:---:|:---:|:---:|:---:|
| 1 | | (1, 2, x, 4) | ? | (1, 2, x, 4) | 
| 2 | (1, 2, y, 4) | | ? | (1, 2, y, 4) | 
| 3 | (a, b, c, d) | (e, f, g, h) | ? | (i, j, k, l) |
| 4 | (1, 2, z, 4) | (1, 2, z, 4) | ? | |

Let's discuss this. So $p_{1}$ broadcasts $1$ to all other processes, and when the other processes receives those values, it constructs a vector of values to determine if it has a majority.

The faulty $p_{3}$ sends all letters, and that is why we obtain $(a, b, c, d)$ etc. Since the system knows it's supposed to get numbers, you could send the same letters to all other processes - the different letters just illustrate the Byzantine failure of $p_{3}$. 
The individual processes determine the majority but comparing the vectors. So they obtain

| Process | Majority |
|:---:|:---:|
| 1 | (1, 2, x, 4) |
| 2 | (1, 2, y, 4) |
| 3 | (1, 2, 3, 4) |
| 4 | (1, 2, z, 4) |
| Consensus | (1, 2, $\perp$, 4) |

where $\perp$ is `null`. 

---

**Describe a fault-tolerant asynchronous solution. Do they exist?**

Trick question! 

You cannot have a asynchronous solution with unicast (or any cast) that has a bounded communication delay. 

A single crash will prevent consensus from being achieved.

---

### __Practical Consensus Algorithms__

**What is the distributed commit problem?**

The distributed commit problem deals with ensuring a "all or nothing" commit. That is, either all processes involved finish the operation succesfully or none of them at all.

The operation can be the delivery of a message - reliable multicast, or it can be comitting a transaction (e.g. DBMS).

We solve this with a special process called the __coordinator__.

---

**Describe the two-phase distributed commit procedure (2PC).**

1) __Voting Phase__

Coordinator an invite for "commit" to all processes and awaits their response.

The participants answer the coordinator with either "commit" or "abort"

2) __Commit Phase__

If ALL participants agree to commit, then coordinator will "commit" and send "commit" message to all participants.

Otherwise, it aborts and sends "abort" message to all participants.

Naturally, the participants respond accordingly.

---

**What is the limitation of the 2PC?**

The main limitation of this process is the necessity for an absence of failures of the process.

Suppose one of the processes fail then the coordinator won't receive "commit" message from all participants and will "abort".

Alternatively, if the coordinator fails, then the participants will not know what to do, The only time we can be sure is when all the participants are still functioning and they have not received a "commit" request then we know that nothing has happened.

Suppose a coordinator AND a participant both fail. Then we cannot be sure that there is no commit because the participant could have been the first to be notified before itself and the coordinator failed. 

Even if a new coordinator is selected, we still cannot proceed until the last participant has recovered, since we require a reponse from all members.

This is a problem as you would be blocking until the coordinator AND the participant return. And what if the either don't come back... 

![Screen Shot 2020-06-16 at 12.31.06 am.png](resources/0899C4895123647CF35A1EB6560893F4.png =782x258)

---

**Describe the three-phase distributed commit procedure (3PC).**

The 3PC protocol is designed to tackle this problem, by introducing a "pre-commit" state.

1) __Voting Phase__

Coordinator an invite for "commit" to all processes and awaits their response.

The participants answer the coordinator with either "prepare-commit" or "abort"

2) __Pre-commit Phase__

The coordinator goes to "pre-commit" status if it receives "prepare-commit" from all participants, otherwise is goes to "abort" status. When a response is heard it sends this information to all participants who then respond accordingly.

Participants abort if the coordinator aborts or if a time-out period is reached. If the coordinator is in "pre-commit" status, then the participants will acknowledge that. 

3) __Commit Phase__

If ALL participants acknowledge the "pre-commit", then coordinator will "commit" and send "commit" message to all participants.

Participants will "commit" once they receive this message.

__Solving the issues with 2PC__

Consider the previous case where one participant has heard "pre-commit" from the coordinator before it crashed. Assume then that this participant also crashed.

In this case, we know that it hasn't committed because they are in the pre-commit" phase. 

Even if they crash during phase 3, the other participants have already received the "pre-commit" message, and so when they contact each other or elect a new coordinator, they will unamiously agree to commit since that's what was agreed upon.

The failed participant can also just commit once it comes back, since it has been in  "pre-commit" state.

If the coordinator crashed, then similarly we just have to check with the participants whether they are in the "pre-commit" state, which then implies that everyone has agreed to commit. Then the participants can be sherperded to commit.

__Disadvantages__

- most practical systems have unbounded delay and process pauses, and thus this does not guarantee atomicity (some participant can just go down indefinitely and thus be out of date)
- this protocol requires 3 round-trip-times to finish. This is potentially a big cost in terms of latency.

![Screen Shot 2020-06-16 at 12.31.19 am.png](resources/F727A4ADC188742AA2788B6226A551DC.png =723x240)

---

### __Paxos Algorithm__

This algorithm is guaranteed to work as long as a majority of acceptors are working

**Describe the Paxos consensus algorithm.**

We have 4 roles:

- **client:** issues request to distributed system and awaits a response
- **acceptor (voter):** nodes in the system that act as fault-tolerant memory. They are collected into groups called quorums. Every member of a quorum receives the same message, and any message must be sent to the entire quorum. Otherwise the message is ignored
- **proposer:** advocates client request and attempts to convince acceptors to agree.
- **learner:** acts as the replication factor for the protocol. Once a client request has been agreed upon by acceptors, the learn takes action (execute request and send response to client)

__Phase 1: Propose__

a) Prepare

Proposer creates a message $\langle \text{seqNum}, \text{value} \rangle$. The **seqNum** is an increasing value that uniquely identifies the message sent by the proposer to the acceptors.

This number must be greater than any previous number used by this current proposer.

In this step, the proposer only sends the seqNum through. It should not initiate Paxos unless it can communicate with an accepted number of acceptors in the quorum.

The proposer sends the seqNum as a "prepare" message.

b) Promise

When an acceptor receives the "prepare" message and checks the seqNum. Either

i) seqNum is greater than every previous seqNum received the acceptor returns "promise" message to say that all is good. Then the acceptor will not accept a seqNum less than the seqNum it just received. 

__If the acceptor accepted a proposal in the past__ it must send back a message containing the previous seqNum, e.g. $m$, and the corresponding accepted value, say $v$.

The above statement is key, as if another user tries to propose something that is incorrect or conflicting, the proposer will be informed.

ii) Else the acceptor will ignore the proposal, since the seqNum is less than the last seqNum it replied with a "promise" message.

__Phase 2: Accepting__

a) Accept

If a propose receives a majority, then it sets $v$ to be the value for its proposal. As we mentioned, if the acceptor has previously accepted a proposal, then the proposer will have received this proposal. 

It then sets its value to be identical to the acceptor with the highest seqNum. That way, we have updated. 

Regardless of whether the proposer uses its own proposed value or the acceptor's highest value, it sends an "accept" message to the quorum of acceptors consisting of $\langle \text{seqNum}, \text{value} \rangle$.

b) Accepted

Each acceptor receives the "accept" message and accepts the new value $\iff$ it has not already promised to consider proposals greater than the seqNum received in the "accept" message.

If that is the case, the accceptor will register $\langle \text{seqNum}, \text{value} \rangle$ and send an "accepted" message to proposer and every learner (typically be the proposer itself).

Otherwise it will ignore the accept message or request.

__Rounds failing__

When rounds fail, e.g. multiple proposers send conflicting "prepare" messages or when proposer does not receive a quorum of responses another round is started with a higher proposal number (seqNum).

__Byzantine failure handling__

To handle Byzantine failures, we add a "verify" message. 

This is beyond the scope of the course but is worth looking into. 

__Example__

Suppose we have 5 nodes: [A, B, C, D, E]. We require a majority of nodes at each step. Suppose you're a client that wants to get a lock.

__a) 5 nodes working__

Suppose the client Jerry submits a timestamp request for the lock `(ts=13, Jerry)` at node C. Since there is no one holding a lock at the moment, the nodes all unanimously agree. 

So the nodes sends a 'promise' message to node C to reserve the lock for Jerry.

| Node | Timestamp | Stage |
|:---:|:---:|:---:|
| A | (ts=13, Jerry) | Promise |
| B | (ts=13, Jerry) | Promise |
| C | (ts=13, Jerry) | Promise |
| D | (ts=13, Jerry) | Promise |
| E | (ts=13, Jerry) | Promise |

At this point, node C liases behalf of Jerry and sends a 'commit' message to all the other nodes letting them know that it will give the lock to Jerry.

__b) 3 nodes working__

Similar to the previous case, we have a majority so Jerry will successfully acquire the lock. However, the table will be different. Suppose that node B and node E are down.

| Node | Timestamp | Stage |
|:---:|:---:|:---:|
| A | (ts=13, Jerry) | Promise |
| B | | |
| C | (ts=13, Jerry) | Promise |
| D | (ts=13, Jerry) | Promise |
| E | | |

Now suppose node B comes back.

Suppose Paul requests for the lock on node B. Since node B went down earlier it doesn't know that Jerry has the lock.

So node B sends out the message `(ts=22, Paul)` but the nodes that have the previous timestamp will send this information back to node B, since the timestamp is higher. If the timestamp is lower than the request will be automatically rejected.

So now node B knows what happened and updates its timestamp to make sure the future requests need a greater ID. 

| Node | Timestamp | Stage |
|:---:|:---:|:---:|
| A | (ts=22, Jerry) | Promise |
| B | (ts=22, Jerry) | Promise |
| C | (ts=22, Jerry) | Promise |
| D | (ts=22, Jerry) | Promise |
| E | | |

Once Jerry is done, Paul is then next in line for the lock.

---

**Give some examples of its application.**

- Google: Chubby distributed lock service
- Google: Spanner SQL database and megastore
- Microsoft: Autopilot cluster management system
- Neo4j: graph database

---