__Key questions__

- What are some characteristics of 
a) ram
b) hard drives
c) CPUs
- What implications does this have on DBMS design?
- Briefly describe the components of a hard drive. Drawing a picture might help.
- What is the "access gap"?
- How do we try to overcome the "access gap" problem?
- What are some examples of "raw data"? What kind of structure do they have? What are some issues with this type of storage?
- What are some examples of database files?
- Briefly describe the row format in PostgreSQL?
---
- What are the pros and cons of different file organisations?
a) heap
b) sorted
c) indexes
- What are the time complexity
a) scan
b) read
c) query
d) write
- What is a "wide column store"?
- What are some pros and cons of column storage?
- Briefly describe the components of a buffer manager.
---
- Define a dirty page.
- Describe buffer utilisation. What is the formula and what is considered "good efficiency"?
- Describe the 4 replacement policies. What one is most commonly used?
- What is clock? How does it work?
- What is pre-fetching?
- Why don't we just use the OS's buffer management?
---

__Bonus__

- Why are multiple buffer pools useful?
- How does the DBMS know when to do pre-fetching?
- What is data sharing?
- Why does PostgreSQL use OS caching whereas other enterprise database software use their own implementation of caching?
- What is sequential flooding?
- Describe LRU-K.
- Describe Localisation.
- What are priority hints?
- What is background writing and why is it useful?

Note: CMU Databases L5