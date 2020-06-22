### WINDOW

The so-called __window_ functions allow computation for aggregation over a set of values relative to the current row. 

You can also __rank()__ the query output for the window. 

Consider the 2 examples below

```pgsql
SELECT sid, name, rank() OVER (ORDER BY mark DESC)
  FROM Student
       NATURAL JOIN Enrolled
 WHERE uos_code = 'INFO1903'
 LIMIT 3
```

The above computes the top 3.

The below, computes the top 5 most common films in each category

```pgsql
SELECT rank() OVER (ORDER BY COUNT(film_id) DESC) as rank,
        name as category, 
         COUNT(film_id) as films
    FROM (Film INNER JOIN Film_Category USING (film_id))
            INNER JOIN Category USING (category_id)
    GROUP BY category
    ORDER BY rank ASC, category ASC 
    
    LIMIT 5
```

### CASE 

Remember to check the format very carefully.

CASE WHEN `condition` THEN `output`
    ....
    ....
    ....
    ....
ELSE

END as `name of column`

```pgsql
SELECT film_id, title, release_year, rating, 
CASE WHEN rating = 'G' THEN 'General Audiences. All Ages Admitted.'
    WHEN rating = 'PG' THEN 'Parental Guidance Suggested. Some Material May Not Be Suitable For Children.'
    WHEN rating = 'PG-13' THEN 'Parents Strongly Cautioned. Some Material May Be Inappropriate For Children Under 13.'
    WHEN rating = 'R' THEN 'Restricted. Children Under 17 Require Accompanying Parent or Adult Guardian.'
    WHEN rating = 'NC-17' THEN 'No One 17 and Under Admitted.'
    ELSE ''
    END as rating_def
    FROM Film 
        WHERE release_year >= 2002 and release_year <= 2006
```



