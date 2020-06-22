### __Concepts Overview__

**What is the difference between search key vs. candidate key.**

candidate key: set of attributes that uniquely identifies a record
search key: set of attributes used for searching

Note: primary keys are typically automatically indexed.

---

**What is an integrated index?**

An integrated index is an index that holds actual records in the index storage itself.

---

**What is the trade-off of using index data?**

We're hoping that

$$\text{index lookup cost} + \text{record retrieval cost} < \text{file scan cost} $$

---

**What is the difference between **
a) **Cluster and non-clustered data structure?**

![Screen Shot 2020-06-13 at 10.21.02 pm.png](resources/C8CAF2326B09BA4658CC3909855FD856.png =721x230)

A clustered index is when (most) of the logical sorts of the data directly corresponds to the physical storage of the data (see LHS of diagram above).

We say "most" because we tend to leave some free space for the heap files that store the data records for future inserts. Hence we may have some overflow. 

The main index is always clustered.

In practice, there is a maximum of one clustered index for one table. It is very good for range searches and minimises page transfers and maximises likelihood of cache hits. 

b) **Sparse and dense?**

Dense: has index entry for each data record. Unclustered $\rightarrow$ dense. Clustered $\rightarrow$ need not be dense.
sparse: has index entry for each page of data file

c) **Primary and secondary?**

An index whose search key specifies the sequential order of the file. It is typically implemented by index entries containing actual data rows. If an index is not a primary index then it is called a secondary index.

d) **Unique and non-unique?**

If we are indexing over candidate keys (which are required to be unique w.r.t each record), then the index will be unique. Conversely, the index will be called non-unique.

---

**What are some downsides of using indexes?**

- additional I/O is required to access the index page
- indexes must be updated accordingly when the table it's indexing is updated
- not all query types are supported by all index types e.g. equality vs. range scan, regex matching, prefix searches on multi-attribute indexes, negation.

---

### __Tree-based Indexes__

**Intuitively describe tree-based indexing.**

![Screen Shot 2020-06-13 at 9.58.08 pm.png](resources/436403E052DDF0013B94AC0506DA1142.png =560x244)

For tree indexes, the none-leaf nodes contains pointers to the index pages. For each index page, you have pointers on the LHS and RHS of entries.

The LHS of an entry $k_{i}\in\mathbb{R}$ contains a pointer to the index page with entries $x \geq k_{i-1}$ and $x > k_{i}$  whereas the RHS of the entry contains a pointer to the index with entries $x >= k_{i}$ and $x < k_{i+1}.

A set of a pointer $p_{i}$ and its corresponding and $k_{i}$ values is called a separator entry, $(p_{i}), k_{i})$.

---

**Describe ISAM (indexed sequential access method).**

The ISAM refers to the method of accessing an index on the tree-index described above.

This index is good for equality and range searches, since leaf pages are stored sequentially in file when storage structure is created. If the pages are also positioned on disk to support a scan, a range search can be very fast.

It supports multiple attribute search keys and partial key searches.

---

**What is an issue with ISAM access?**

The issue with ISAM access is that its index is static. This presents a problem with pages overflowing in the leaf nodes. The overflow pages can result in an undesirably long chain that is unsorted and scattered on disk. Hence this is very inefficient.

It is also inefficient is if the table is dynamic and being subject to constant change.

![Screen Shot 2020-06-13 at 10.13.47 pm.png](resources/6E3F6EB3E3947C4AF2EC01F2B42A874D.png =689x270)

---

**Describe B-tree indexing. What is the definition? How does the data structure handle insertion/deletion?**

The B+ tree is a dynamic multi-level index structure that responds to changes in the table (data). The big advantage is that we do not need to reorganise the entire index to maintain performance. In addition, we can ensure there's no overflowing chains.

The main difference to ISAM is that the tree must be balanced, and that all paths from root to leaf must have the same length and entries are in the leaves only. Another cool thing is that there are sibling pointers between leaf-nodes, which makes the leaf nodes like a sorted linked-list. They do not need to be physically contiguous though.

__Definition__

The definition varies by textbook. We go with what was in the lecturer slides.

A B+ tree of __order d__ and __height h__ is a tree with the following properties:

- h = len(path(root $\rightarrow$ leaf))
- internal node has $d+1$ children
- root node either is a leaf node or has at least 2 children
- the internal node and root node have at most 2d + 1 children
- leaf nodes hold between $d$ and $2d$ index entries. 
- leaf nodes form a doubly linked list.
- entries in each node are sorted. That is, $\forall (k_{i}, p_{i})$ we have $k_{i} \leq k_{i} < k_{i+1}$, $\forall k\in \text{subtree}(p_{i})$ 

__Searching__

![Screen Shot 2020-06-13 at 10.36.20 pm.png](resources/A55AEEA275265BFC0F6B5C97AAC4B264.png =620x83)

```{pseudocode}
Searching for value L.

Start at root.

foundNodePosition = False

while not reached leaf node:
  # Go to the first pointer
  if L < k[0]:
    foundNodePosition = True
    access(p[0])
  else:
    for i in [1, ..., n]:
      if k[i-1] < L and k[i] > L:
        foundNodePosition = True
        access(p[i])
    
    # Go to the last pointer
    if not foundNodePosition:
      access(p[n])

while true:  
  if k[i] == L:
    add to list
    i += 1
  else:
    break
  
if list is empty then no record with value L exists.

```

__Insertion__

Please see this Youtube video [here](https://www.youtube.com/watch?v=_nY8yR6iqx4). It is too good.

__Deletion__

For deletion, if the leaf $L$ is at least half full then we are done.

Otherwise:

- try to re-distribute by borrowing from sibling (adjacent node with same parent as $L$) 
  - if that fails, try to merge L and the sibling. 
    - if the merge occurred, delete the entry pointing to L or the sibling from parent of L
      - the merge could propagate to the root, decreasing height. 

---

**What are the advantage/disadvantages of using B-trees?**

__Advantages__

- supports equality and range searches
- tree is balanced so cost is consistent and logarithmic to the fanout of the index nodes.
- can be used for either secondary index or the basis for an integrated storage structure.

__Disadvantages__

- insertion overhead
- deletion overhead

---

**What does "fan-out" mean?**

The "fan-out" of a B+ tree is the average number of children per node. 

---

**What is the access cost of a B+ tree?**

$$\log_{F}(B+1)$$

where $F$ = fan-out and $B$ = number of leaf pages.

---

**What are some properties of B-trees in practice?**

| Typical property | Typical value |
|:---:|:---:|
|order|100|
|fill-factor| 67%|
|average fan-out | 133 |
|h=3|$133^{3}$ records|
|h=4|$133^{4}$ records|
|level 1|1 page = 8Kb|
|level 2|133 pages = 1MKb|
|level 3|17689 pages = 133Mb|

---