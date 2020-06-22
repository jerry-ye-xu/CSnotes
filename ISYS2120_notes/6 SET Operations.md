In all 3 SET operations, the queries require you to return the result of both in the same format. There cannot be a format change.

### Union

```pgsql
SELECT 1, 'a'
    UNION
SELECT 2, 'c'
    UNION
SELECT 3, 'b'
```

__UNION__ by default removes all duplicates, but __UNION ALL__ keeps all duplicates. 

This __ALL__ modifier is available for the other 2 operators as well. 

### Intersect

```pgsql
SELECT studentId
    FROM Enrolled
WHERE uosCode = 'INFO2120'
    INTERSECT
SELECT studentId
    FROM Enrolled
WHERE uosCode = 'INFO3005'
```

### EXCEPT

__EXCEPT__ this operator removes all tuples from the first result set that also exists in the 2nd result set. 

So you'll need to finish the 1st query and then the 2nd query will generate tuples to remove from the 1st result. 

```pgsql
SELECT studentId
    FROM Enrolled
WHERE uosCode = 'INFO2120'
    AND grade IS NOT NULL
        EXCEPT
SELECT studentId
    FROM Enrolled
WHERE uosCode = 'INFO3005'
```

### ORDER BY 

To ORDER BY your results, you'll need to encapsulate the separate queries in brackets

```pgsql
(
SELECT 'a' AS value
)
    UNION
(
SELECT 'c' AS value
)
    UNION
(
SELECT 'b' AS value
)
    ORDER BY value
```

### CROSS JOIN

The __CROSS JOIN__ allows you to find duplicates of things (as the below example will show.)

This is essentially a __cartesian join__ 