The “NULL” value is a specify value that represents some data that is _not_ known (yet). 

This is useful not only as a placeholder for information that is absent, but also is used when values are deleted. We'll talk about this a little later.

### Querying NULL values 

```pgsql
SELECT studentId
    FROM Enrolled
WHERE grade IS NULL;

-- or you can check the reverse

SELECT studentId
    FROM Enrolled
WHERE grade IS NOT NULL;

-- NOTE: NULL is NOT an empty string
SELECT '' IS NULL;
SELECT 0 IS NULL;

-- The above queries will return false because they are not null values.
```

### NULL is the 3rd logic 

Normally when we think about logic, we're thinking about boolean logic --> true OR false.

However, the NULL is actually a 3rd boolean result. We have to becareful here!!

```pgsql
SELECT 1 = NULL;

SELECT 1 IS NULL;
```

What are the 2 results for the 2 above queries?

Hint: The 3rd logic result is “NULL”

`a``b``a = b``a AND b``a OR b``NOT a``a IS NULL`truetruetruetruetruefalsefalsetruefalsefalsefalsetruefalsefalsefalsetruefalsefalsetruetruefalsefalsefalsetruefalsefalsetruefalsetrue`NULL`unknownunknowntruefalsefalsefalse`NULL`unknownfalseunknowntruefalse`NULL`trueunknownunknowntrueunknowntrue`NULL`falseunknownfalseunknownunknowntrue`NULL``NULL`unknownunknownunknownunknowntrue

### Aggregate functions with NULL

Some detail here you need to pay attention to.

Let’s talk about COUNT

```pgsql
-- COUNT(*) ALWAYS counts all tuples
Select COUNT(*) FROM Student;

-- Anything else, it ignores any NULL
Select COUNT(studentId) FROM Student;

-- just a standard query, don't get tricked!
SELECT COUNT(*)
    FROM Student
WHERE age IS NULL;
```

__Careful!__

```pgsql
SELECT AVG(age) FROM Student;


SELECT SUM(age) / COUNT(*) AS avg FROM Student;

-- These guys do NOT return the same result. This is because COUNT(*) returns tuples with an unknown age as well! This makes the denominator different. 
```

#### Setting a specific output for NULL

Sometimes it might be hard to actually see an empty value in a table. So we can actually set a specific value to output when the query returns a NULL value.

```pgsql
\pset NULL '[NULL]';

-- The output is:
-- Null display is "[NULL]"
```

You can do something similar with the \_\_COALESCE\_\_ function

```pgsql
SELECT studentId, COALESCE(grade, '[UNKNOWN]')
  FROM Enrolled;
```

The output is shown below:

| studentid | coalesce |
|-----------|----------|
| 609187546 | [UNKNOWN] |
| 316424328 | D |
| 305678453 | HD |
| 316424328 | CR |
| 200022153 | P |
| 316424328 | D |
| 404246989 | [UNKNOWN] |
| 309145324 | F |
| 609187546 | D |
| 207088592 | [UNKNOWN] |



