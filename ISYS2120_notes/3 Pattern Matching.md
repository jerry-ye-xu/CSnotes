### Using LIKE

```pgsql
SELECT uosCode, uosName
    FROM UnitOfStudy
WHERE uosName LIKE 'Database%';

-- The NOT LIKE function does the opposite
SELECT uosCode, uosName
    FROM UnitOfStudy
WHERE uosName NOT LIKE '%Database%';
```

The “%” sign is a wildcard for any sequence of zero or more characters. 

You can also use placeholders “\_”, which matches exactly 1 character

### LOWER

```pgsql
SELECT uosCode, uosName
    FROM UnitOfStudy
WHERE LOWER(uosName) LIKE '%systems%';
```

This is good for case-insensitive matching.

### More Advanced Regex Pattern Matching

```pgsql
SELECT uosCode, uosName
    FROM UnitOfStudy
WHERE uosName SIMILAR TO '(Advanced|Data)%';

SELECT uosCode, uosName
    FROM UnitOfStudy
WHERE uosCode SIMILAR TO 'COMP[[:digit:]]{4}';
```

These are pretty advanced, and we can go into more detail later.