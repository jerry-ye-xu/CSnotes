### __Concepts Overview__

**Describe the role and structure of query processing.**

When we provide a query to the DBMS, the query evaluation enginer must first parse and understand the query before choosing an optimised execution of the query.

The role of query processing is to maximise performance of our queries.

The structure is a series of steps, from parsing to choosing an execution plan for the query.

---

**Describe the key ideas in relational algebra. What symbols are used to represent these ideas?**

```{mysql}
SELECT S.name, U.uosname
  FROM Student S, Enrolled E, UosOffering U
    WHERE S.sid = E.sid 
      AND U.uoscode = E.uoscode
      AND U.semester = E.semester
      AND U.year = E.year
      AND E.mark BETWEEN 85 AND 100
```

- __projection:__ $\pi_{\text{column}}$ $\longleftarrow$ $\pi_{S.name, \;U.uoSname}$
- __selection:__ $\sigma_{\text{condition}}$ $\longleftarrow$ $\sigma_{E.mark \geq 85 \;\&\; E.mark\leq100}$
- __join:__ $\bowtie$ $\longleftarrow $E \bowtie_{\text{E.sid=S.sid}} S$
- __alias:__ $\rho$ $\longleftarrow $\rho_{E}, \rho_{S}, \rho_{U}$

---

**Write a relational algebra expression for the following SQL query:**

```{mysql}
SELECT S.name, U.uosname
  FROM Student S, Enrolled E, UosOffering U
    WHERE S.sid = E.sid 
      AND U.uoscode = E.uoscode
      AND U.semester = E.semester
      AND U.year = E.year
      AND E.mark BETWEEN 85 AND 100
```

$$ \pi_{\text{S.name, U.uosname}}\bigg(\sigma_{\text{condition}}\big(\rho_{S}(\text{Student})\times\rho_{E}(\text{Enrolled})\times\rho_{U}(\text{UosOffering})\big)\bigg) $$

where condition is equal to 

$$ \text{mark}\geq 85 \;\hat{}\; \text{mark}\leq 100 \;\hat{}\; \text{S.sid}=\text{E.sid} \;\hat{}\; \text{U.uoscode}=\text{E.uoscode} \;\hat{}\; \text{U.semester}=\text{E.semester} \;\hat{}\; \text{U.year}=\text{E.year} $$

**What is the difference between expression tree vs. query execution plan?**

An expression tree is a translation of the query using algebra operators. This represents the intermediate results.

An execution plan indicates how the ideas in the algebra operators will be carried out. That is, we have "ORDER BY" being equivalent to sort-merge etc.

---

**What is the difference between logical operations vs. RA (relational algebra) operators vs. physical operations?**

| logical | relational algebra | physical |
|:---:|:---:|:---:|
| access paths, selections | $\sigma$ | file, index scan, filter |
| projections | $\pi$ | simple projection, merge sort |
| inner, outer, cross joins | $\bowtie, \times$ | nested loops, nested index loop etc.

---

**Define "access path".**

An access path is a method of retrieving tuples.

**How is query costs measured? What is the tradeoff between the optimal query and executing the query in practice?**

Query costs are measured by time, with many factors such as I/O costs (disc access), CPU, network communication. 

__Disc access is the predominant cost in most cases!__

For simplicity you can use estimate using number of block transfers from disk as cost measure. We also ignore the different between random and sequential I/O for simplicity.

Some operations such as join or sort have varying cost depending on size.

**Define reduction factor**

$$\frac{\rvert{\;\text{output}\;\lvert}}{\rvert{\;\text{input}\;\lvert}}$$

where $\rvert\;A\;\lvert$ is the cardinality of the set $A$.

**What are the two ways records are passed between operations? Which kind of queries would invoke which?**

a) __Materialisation:__ for inner joins, sorts, hash joins and aggregations
b) __Pipelining:__ simplier queries that don't reduce or extend the dataset in some way, e.g. unary operators such as projections and selection

---

### __External Merge-sorting__ 

**Describe external merge sorting in detail. Use diagrams, and work through a small example.**

To sort a file with $N$ pages using $B$ buffer pages there are 2 main stages.

__Sort phase__

Use $B$ buffer pages to sort the $N$ pages, producing $M = \lceil\frac{N}{B}\rceil$ pages in total.

Denote the sorted partitions as $S_{1}, ..., S_{M}$. 

Each sorted partition might require several pages to be loaded inside.

The total cost is 

$$2N\times I/O$$

![Screen Shot 2020-06-10 at 10.50.05 pm.png](resources/1E64091CE3F8EFE468B0C2B23F8C68D3.png =720x399)

__Merge phase__

At each pass $i$:

Use $B-1$ buffers to load in $S_{1}$ and $S_{2}$ as $S_{1, i}$ and $S_{2, j}$ into the buffer pages. Denote the last buffer page as $B^{*}$

Then we use two pointers, one on each page and iterate through until $B^{*}$ used to hold the sorted values is full.

Then we flush $B^{*}$ and continue. When a pointer finishes a buffer page it moves to the next one and we write in the next $S_{1, i+1}$ or $S_{2, j+1}$ depending on who finished.

![Screen Shot 2020-06-10 at 10.50.18 pm.png](resources/208D6F9844A86731DA0553588865EF70.png =720x399)

We repeat until everything has been sorted.

At the end of every pass, the number of partitions that have been sorted individually halves (because we're combining them together).

**What is the complexity for external merge sort?**

$$2N \times \left(\Bigg\lceil\log_{B-1}\left(\frac{N}{B}\right)\Bigg\rceil + 1\right)$$

Note that the number of merge passes required is $\Bigg\lceil\log_{B-1}\left(\frac{N}{B}\right)\Bigg\rceil$ whereas the $+1$ is for the initial sorted run.

Note the change of base:

$$\log_{b}(a) = \frac{\log_{x}(a)}{\log_{x}(b)}$$

**When would using B+ trees for sorting be a good idea?**

- when the $B+$ tree index is in the order required by the file sort.
- when the $B+$ tree is clustered.