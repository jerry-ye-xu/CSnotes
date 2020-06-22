__Key questions__

- Describe the role and structure of query processing.
- Describe the key ideas in relational algebra. What symbols are used to represent these ideas?
- Write a relational algebra expression for the following SQL query:
```{mysql}
SELECT S.name, U.uosname
  FROM Student S, Enrolled E, UosOffering U
    WHERE S.sid = E.sid 
      AND U.uoscode = E.uoscode
      AND U.semester = E.semester
      AND U.year = E.year
      AND E.mark BETWEEN 85 AND 100
```
- What is the difference between expression tree vs. query execution plan?
- What is the difference between logical operations vs. RA operators vs. physical operations?
- Define "access path".
- Define "reduction factor".
- How is query costs measured? What is the tradeoff between the optimal query and executing the query in practice?
- What are the two ways records are passed between operations? Which kind of queries would invoke which?
---
- Describe external merge sorting in detail. Use diagrams, and work through a small example
- What is the complexity for external merge sort?
- When would using B+ trees for sorting be a good idea?