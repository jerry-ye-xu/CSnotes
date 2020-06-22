__Key questions__

- Define hash based indexes.
- Describe static hashing. What are its limitations?
- Describe extendible hashing.
- Describe linear hashing.

- Describe bitmap indexing.
 
- Explain what is meant by a cluster index
- What are some considerations for choosing what type of index to use?
- What is a composite search key?
- When does an index match a query condition?
- What conditions are desired such that the index scan with a B+ tree is preferred over general merge sort when sorting a file?

### __Hashing Indexes__

**Define hash based indexes.**

> An array of $N$ buckets, each one containing a pointer to a row in the database. Hash indexes use a hash function `h(k, n)` to map the key $k$ to on of $n$ buckets.

If index entries contains rows, the set of buckets forms an integrated index

---

**Describe static hashing. What are its limitations?**

Static hashing is the simplest form of hashing. 

For every row, apply the hash function to the attribute you are partitioning by and store the key into the appropriate bucket determined by the output to the hash function. 

If the bucket is full, add a pointer to an new empty bucket. This is called a overflow bucket (page). 

When searching for a key, the process will have to traverse through the linked list of overflowed pages. Hence the more overflowed pages, the worse the performance of the hash index.

![Screen Shot 2020-06-16 at 11.27.39 pm.png](resources/90B411FC1721ED7EA7299144D8A3D1DB.png =435x226)

---

**Describe extendible hashing.**

The previous method could be tweaked to avoid using overflow pages.

Instead of adding overflow buckets, we increase the number of buckets and partition the key using a more fine-grain hash key.

The basic idea is this:

Here the hash function $h(k)$ returns a string of bits. 

The first $i$ bits of the string will be used as indicies to determine where they will go in the hash table.

The hash table uses a directory of pointers, the possible combination of the first $i$ bits.

Here we have a __global depth;__ the number of bits required to determine which bucket an entry belongs to, and a __local depth;__ the number of bits required to determine if an entry belongs to the bucket.

$i$ increases as buckets overflow and we are required to double the directory size. Every time we double the directory size, we use $i+1$ bits, so one more bit than before.

This way, adding a new list of pointers is cheaper than double the buckets required as it will double the memory (because it needs to reserve it). 

Each pointer directory points to a specific bucket. You can have multiple pointers pointing to the same bucket if the bucket's local depth is less than the global depth.

__When the bucket overflows__

When the bucket overflows, another bucket is created, and the pointers involved are re-routed appropriately, and the keys in side the overflowed bucket are re-allocated.

Consider the example below:

![Screen Shot 2020-06-16 at 11.42.00 pm.png](resources/8C7A1E99ECF3A987E94753C8E5232308.png =394x346)

Here we have Bucket A being full. Suppose we were to add a key $k$ s.t. $h(k) = 20$.

Then since $20 = 10100$, it goes into Bucket A with global depth equal to 2.

This causes an overflow, then we would split that bucket. We double the pointer directories and use $i = 3$ bits as our index. 

By considering the first 3rd bits (starting from left), we can split the bucket as you can see in the diagram below.

![Screen Shot 2020-06-16 at 11.39.43 pm.png](resources/6D786E5145503CCF384D345D32B41AEA.png =713x386)

Finally, we do not forget to update the local depth of the buckets that are involved in the split. 

The result of this is that we add in one bucket at a time, instead of doubling the number of buckets whenever one bucket overflows.

__Deleting keys__

If the removal of a data entry makes the bucket empty, then we can merge the buckets appropriately. If each directory element points to the same bucket as its split image, the we can halve the directory.

The alternative to avoid this directory of pointers is linear hashing.

---

**Describe linear hashing.**

In linear hashing, a pointer directory is avoided by using overflow pages as in static hashing but also round-robin split.

The idea is taking the modulus based on how many current buckets we have.

Let's define a few key ideas that are required.

- __hash function:__ combines a hash function and takes a modulus equal to number of buckets currently used.

$$h_{i} = h(k) \; \text{mod}(2^{i}\times M)$$

where $k$ is the key, the $i^{\text{th}}$ round and $M = 2^{d_{0}}$ where $d_{0}$ is the number of bits required to uniquely identify a bucket.

Furthermore, we define a $d_{i} = d_{0} + i$ where $d_{i}$ is the number of bits you need to look at to uniquely identify a bucket in the $i^{\text{th}}$ round.

So for example, if we start with 2 buckets, then $d_{0} = 1$ and the first round (indexing starts at zero) will require $d_{0} = 0 + 1$ bits.

If we start with 8 buckets, then $d_{0} = 3$ and the first round (indexing starts at zero) will require $d_{0} = 0 + 3$ bits.

- __round:__ The round refers to the set of buckets that need to be split. The pointer at the $i^{\text{th}}$ round, assuming you start with 2 buckets only goes from the $0^{\text{th}}$ to the $(2^{i}-1)^{\text{th}}$ bucket. 

- __bucket capacity:__ Number of elements a single bucket can hold (both primary and overflowed)

- __bucket pointer:__ the pointer $p$ which specifies the bucket which should be split next. It moves to the next bucket  $[p \mod (N)]$ style. 

So suppose you have 4 buckets, [0, 1, 2, 3]. Then you might be splitting your buckets as you add extra elements so as the pointer increments to $p = 2$ you will have $[0, 1, 2, 3, 4, 5]$ buckets. However, once the pointer finishes splitting bucket 3, it resets and the round is increased. 

- __split policy:__ A policy that decides when to split the bucket. This could be __load policy__

$$ \text{load policy} = \frac{\text{number of elements}}{\text{bucket capacity}\times\text{number of buckets}} $$

Note: The number of buckets refers to the main buckets only and NOT the overflowed buckets.

You can also choose to split when any bucket is overflowed. That is also another split policy.

__Search__

Given the $i^{\text{th}}$, the relevant hash functions are $h_{i}$ and $h_{i+1}$.

If $h_{i}(k) < p$ then we use $h_{i}$ otherwise we use $h_{i+1}$.

__Insertion__

Given the $i^{\text{th}}$, the relevant hash functions are $h_{i}$ and $h_{i+1}$. If bucket doesn't exist yet for $h_{i+1}(k)$ then we can simply use $h_{i}(k)$.

![Screen Shot 2020-06-17 at 2.03.57 am.png](resources/318212E5DCC4CDA3CB78980336DF9267.png =727x318)

For an example, see this [YouTube tutorial](https://www.youtube.com/watch?v=Yw1ts57uL7c).

---

### __Bitmap Indexing___

**Describe bitmap indexing.**

Bitmap indexing is a special type of indexing in which we use $n$ bits to represent the a particular element in a set of values. 

For example, see the table below.

![Screen Shot 2020-06-16 at 11.55.50 pm.png](resources/7E0659259D69B4CA98B3767A2B0F36BB.png =675x231)

This is fairly intuitive. 

__Answering queries__

To answer queries, we perform bitwise logical operations on these bitmaps. E.g. if you wanted to filter the females in the example table then just perform 

`??? AND 100` check across the entire row (parallelisable). This comparison can be much faster than the B+ tree (especially when there are lots of duplicates values).

__Limitations__

First of all, if the unique values change then the length of the vector has to change which meanms we need to update the table. Deletion of a unique value or changing requires changing the bit index too. 

Secondly, the bitmap index is fairly inefficient for than traditional B+ tree indexes for frequently updated data. Hence they are more often employed in read-only systems specialising in fast query times, e.g. data warehouses. 

You should also consider using Bitmap indexes if an attribute has many duplicated values. If the attribute contains mostly unique columns, B+ trees are very good. 

__Compressing bitmap indexes__

The space requirement is $O(m\times n)$ where $n$ is the number of records, and $m$ is the number of unique values for the attribute. As $m$ increases, the bit vector becomes more sparse. 

Instead, we can compress the bitmap vectors by using __run-length-encoded bitmap vectors__.

__Going through an example__

See worksheet wk4 Q3.

---

### __Concepts Overview__

**What are some considerations for choosing what type of index to use?**

- Consider the most frequent queries and what attributes they demand.
- Trade-off between space for extra index/lookup time vs. using current index/storage structure
- Trade-off between read and updates speed?
- Fill-factor for the index nodes?

- exact match condition: hash index
- range query: tree index
- where clause with several conditions: multi-attribute 
- index-only strategies

---

**What is a composite search key?**

A composite search key is a search key created from multiple attributes in the data. This is exactly akin to a composite key, except we use to for search.

---

**What is a covering index?**

A cover index is a special case of an index where all required fields for a query are included in the index. In other words, the index itself contains the required data to execute the queries without having to execute additional reads.

---

**When does an index match a query condition?**

An index matches a query condition when the index is able to correctly return all tuples that satisfy the query condition.

---

**What conditions are desired such that the index scan with a B+ tree is preferred over general merge sort when sorting a file?**

- the B+ tree index is in the order required by the file sort
- the B+ tree is clustered

---