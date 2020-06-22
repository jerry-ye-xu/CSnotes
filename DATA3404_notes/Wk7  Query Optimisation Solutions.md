### __Cost-based Query Optimisation__

**Describe cost-based query optimisation.**

Query is declarative, and thus we need an execution plan.

The goal of query optimisation is to find a suitable execution plan. Practically, we want to avoid the worst plans as opposed to over-fixate on finding the most optimal plan.

Note: the time used for query optimisation adds to total query execution time.

Query optimisation involves a few steps:

1) generate logically equivalent expressions $\leftarrow$ equivalent one.
2) annotating resultant expressions to get alternative query plans
3) choose cheapest plan based on estimated cost.

Two issues:

1) What plans are considered? The search space is exponential and much too large. We limit this.
2) How is the cost of a plan estimated? Now, typically disc access is predominant cost and relatively easy to estimate. Then, you have disc I/O as cost measure.

---

**Explain how the DBMS can estimate query costs for each query.**

- estimate cost of each operation in a execution plan (the expression tree)
  - estimate input cardinalities
  - estimate cost of operations e.g. sequential scan, index, joins
  - estimate size of result for each operation
- database statistics
  - distribution of data
  - periodic samplings for up to date statistics
  - data inter-dependencies?? Difficult to fully utilise.

Alternative: use rule-based optimisation!

---

### __Equivalence Rules__

**Define equivalence rules and describe some situations where the following types of operators would have an equivalence:**

a) **Selection equivalence**

Selections with conditions joined with $\hat{}$ (AND) __cascade__:
$$ \sigma_{c_{1} \hat{} c_{1} \hat{} \dots \hat{} c_{n}}(R) = \sigma_{c_{1}}(\sigma_{c_{2}}(\dots \sigma_{c_{n}}(R))) $$

Nested selections __commute__:
$$ \sigma_{c_{1}}(\sigma_{c_{2}}(\dots \sigma_{c_{n}}(R)))  = \sigma_{c_{n}}(\sigma_{c_{n-1}}(\dots \sigma_{c_{1}}(R)))$$

b) **Projection equivalence**

Projection operations __cascade__:

$$\pi_{a_{1}}(R) = \pi_{a_{1}}(\pi_{a_{1}a_{2}}\dots(\pi_{a_{1},\dots,a_{n}}(R)))$$

Technically as long as the projections do not conflict in terms of attributes being filtered, then the most selective projection will be the final result. We only need to run one projection.

However, if one projection removes an attribute but another requires it then there will be a conflict.

c) **Projections and selections** 

A projection commutes with a selection that uses only attributes retained by the projection.

![Screen Shot 2020-06-12 at 12.17.01 am.png](resources/47F68CBD0CD91E9DE4039FA2D6B4955B.png =671x313)

d) **Join equivalence**

Joins __commute__

$$R\bowtie_{\sigma}S = S\bowtie_{\sigma}$$

and are __associative__

$$(R\bowtie_{\sigma}S)\bowtie_{\sigma}T = R\bowtie_{\sigma}(S\bowtie_{\sigma}T)$$

---

**Explain what optimisation heuristics are and why they are necessary. Give some examples.**

Optimisation often includes heuristics to restrict the search span. This includes

- perform selection early
- perform projection early
- perform most restrictive selection and join operations before other similar operations

---

### __Join Ordering__

**Describe various methods of join optimisation.**

A join over $n+1$ relations of $R_{1},\cdots,R_{n+1}$ requires $n$ binary joins.

Define $C_{k}$ as the $k^{\text{th}}$ __Catalan number__, where

$$C_{n} = \frac{1}{n+1} {2n\choose n} = \frac{(2n)!}{(n+1)!n!} = \prod_{k=2}^{n}\frac{n+k}{n}$$

Then the number of possibilities to construct a binary tree of $n$ inner nodes is

$$C_{n} = \sum_{k=0}^{n-1}C_{k}\cdot C_{n-k-1}$$

---

**Why do we typically choose left-join orders?**

For left-join orders, the RHS input is a relation and never the result of an intermediate join.

Furthermore, left-join trees allow us to generate all fully pipelined plans.

This way, the only difference between the joins is 

- order of relations
- access method for each relation
- join method used for each join

This makes it much easier. We can use a DP approach.

The algorithm is as follows:

```
There are RR = {R1, R2, ..., Rn} relations to be joined.

for i in [1, 2, ..., n]:
  opt(Ri) = findBestAccessPlan(Ri)
  
for i in [2, 3, ..., n]:
  for all S subset of RR s.t. |S| = i:
    tempBest = infinity
    for all Sj, Rj s.t. SS = {Rj} + Sj:
      p = findBestJoinPlan(opt(Sj), Rj):
        if cost(p) < cost(tempBest):
          tempBest = p
      opt(SS) = tempBest

return optPlan(RR)
```

---

**What is an SQL query block?**

> An SQL query block is an SQL query without nesting, and serves as a unit of query optimization. 

---

### __In Practice__

**How does a DBMS typically optimise for nested queries?**

A nested block is optimised independently, with the outer tuple considered as providing a selection condition.

The outer block is optimised with the cost of 'calling' nested block computation taken into account.

This implicit ordering may miss out on some good strategies.

---

**How does a DBMS typically optimise for dynamic queries?**

Dynamic queries is more secure than static SQL. 

Furthermore, the query is only parsed once, so we don't reconstruct a plan from scratch everytime new values are put into the query. 

The question is how do you optimise if you don't know the values in advance that might result in different execution plans by the query optimiser?

When the query optimizer sees the query (at a 'prepareStatement()' call), it still contains placeholders in some query terms; the optimizer has hence no value available to estimate the correct reduction factor of those terms.

So that is a problem. We can use "typical" values but that is somewhat arbitrary. 

---