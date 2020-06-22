Subqueries can be super fun, but there are 2 types 

1. __Co-related Query__

where the subquery is executed for each tuple of the outer query. 

This means that its search condition refers to at least one attribute of the outer query

2. __Non Co-related Query__

where the subquery is executed only once and then its result used for all tuples of the outer query.

```sql
-- co-related query

SELECT film_id, title
    FROM Film
        WHERE rental_rate = (SELECT MIN(rental_rate) 
                                FROM film
                                    WHERE release_year = 2006)
            AND release_year = 2006
                ORDER BY title;
                
-- non co-related query

SELECT studentId, name
    FROM Student
WHERE studentId IN (SELECT E.studentId
                       FROM Enrolled E
                      WHERE E.uosCode = 'INFO2120')
```

Subqueries can be executed anywhere in the query. It is not just restricted within the WHERE operation.

```sql
SELECT name
  FROM (SELECT studentId, name, grade
          FROM Student
               JOIN Enrolled USING (studentId)) AS E
 WHERE grade = 'HD'
 
 -- so what does this actually do? Well, the subquery finds a student who is enrolled and returns their name
 
 SELECT studentId, name, grade
          FROM Student
               JOIN Enrolled USING (studentId)
    WHERE grade = 'HD'

-- You essentially get the same thing without the subquery, but that's not the point I guess. 

-- Alright, what does this do?

SELECT studentId, name
  FROM Student
       JOIN Enrolled USING (studentId)
 WHERE uosCode  = 'INFO2120'
       AND year = 2010
       AND semester = 'S1'
       AND grade = (SELECT MAX(grade)
                      FROM Enrolled
                     WHERE uosCode  = 'INFO2120'
                           AND year = 2010
                           AND semester = 'S1')
```

### A more complicated example

```sql
SELECT film_id, title, actor_id, first_name, last_name
    FROM ((SELECT film_id, title FROM
            Film INNER JOIN Film_Actor USING (film_id) 
                INNER JOIN Actor USING (actor_id)
            WHERE first_name = 'PENELOPE' AND last_name = 'GUINESS') AS Film_pg
        INNER JOIN Film_Actor USING (film_id)) 
        INNER JOIN Actor USING (actor_id)
```

It is often the case where __EXISTS__ can be paired up with a subquery 