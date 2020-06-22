### JOIN Basics

Joining is one of the more tricky parts of basic SQL syntax, because sometimes in order to get what you need it can be a little counterintuitive.

To start with, let's look at a more basic example, where we use a condition in the WHERE clause to join two tables together.

```pgsql
SELECT Student.studentId, Student.name
    FROM Student, Enrolled
 WHERE Student.studentId = Enrolled.studentId
    AND Enrolled.uosCode = 'INFO2120';
```

This is called the __equi join__ because you're joining on an equality. 

Be wary! If you do not specify all tables that need to be joined appropriately, then you'll end up outputting a __cartesian join__ which maps each product in each table to every product in every other table. So you'll end up with a massive table which is most likely not the desired result.

Note: Sometimes you can make your life easier by renaming your tables or columns

```pgsql
SELECT Student.studentID as id
    FROM Student S, Enrolled E -- Note the renaming here. 
 WHERE Student.studentId = Enrolled.studentId
```

You can also have 3 way joins called explicitly:

```pgsql
SELECT S.studentId, name
    FROM Student S, Enrolled E, UnitOfStudy U
 WHERE S.studentId = E.studentId
        AND U.uosCode = E.uosCode 
        AND U.uosName = 'Database Systems I'
```

### NATURAL JOINs are dangerous!

Definitely avoid these unless necessary. This is because when you make a mistake, you end up with a cartesian join, so it is better to write queries that are more explicit. 

What NATURAL JOIN basically does is join tables where their common attributes are equal. So if one table has 2 common attributes (e.g. SID, Faculty) then any common values that coincide will be joined and outputted by the query. 

The common attributes also have to have the same name as well. So if there is a typo somewhere, then you can easily make some bad queries. 

However, we’ll give some examples to illustrate its usage.

```pgsql
SELECT *
    FROM Student NATURAL JOIN Enrolled
WHERE uosCode = 'INFO2120';

SELECT studentId, name
    FROM (Student NATURAL JOIN Enrolled E)
                  NATURAL JOIN UnitOfStudy
WHERE uosName = 'Database Systems I';
```

\_\_NATURAL\_JOIN\_\_ shows the join attributes only once in the result, whereas an equi-join will show all results regardless.

### INNER JOIN

__INNER JOIN__ is the standard join in SQL.

It basically allows you to either specify the JOIN condition either using ON or USING.

ON - allows you to join using a condition e.g. id = uni_email

USING - allows you to join when attribute names are the same.

Let's have a look at its usage. 

Pay special attention to the 2nd example. 

```pgsql
SELECT year, name
    FROM AcademicStaff
        JOIN Lecture ON (id = lecturer)
 WHERE uosCode = 'COMP5138';

-- Note: This is a VERY good way to filter!
SELECT U2.uoscode, U2.credits
    FROM UnitOfStudy U1 JOIN UnitOfStudy U2
        ON (U2.credits < U1.credits)
    WHERE U1.uosCode = 'INFO2120';

SELECT U2.uoscode, U2.credits
    FROM UnitOfStudy U1 JOIN UnitOfStudy U2
        ON (U1.uosCode = 'INFO2120'
            AND U2.credits < U1.credits);
-- Note: The multiple conditions functionality is rarely used. 

SELECT Actor.first_name, Actor.last_name
    FROM (Film INNER JOIN Film_Actor USING (film_id)) NATURAL JOIN Actor
        WHERE Film.title = 'AMERICAN CIRCUS'
        ORDER BY Actor.last_name ASC
        
        
```

### OUTER JOINs

__OUTER JOIN__ is when you combine tables together even if there are no common values in the specified attributes/condition. Most of the time you'll be using USING. 

__LEFT OUTER JOIN__ vs. __RIGHT OUTER JOIN__

Basically a LEFT OUTER JOIN keeps values in the left relation that have no "join partner" from the right table. RIGHT OUTER JOIN does the opposite, and __FULL OUTER JOIN__ all the values.

In the case of no matches, NULLs are used to fill the values up.

```pgsql
SELECT studentId, name, uosCode
    FROM Student
        LEFT OUTER JOIN Enrolled USING (studentId)
    ORDER BY studentId, uosCode;

SELECT uosCode, year, classroomId, seats
    FROM Lecture
        FULL OUTER JOIN Classroom USING (classroomId)
    ORDER BY uosCode;
```

### More Complicated Example

So if you need to join multiple examples:

```pgsql
SELECT Film.title, COALESCE(Actor.first_name, 'N/A') as actor_firstname, COALESCE(Actor.last_name, 'N/A') as actor_lastname
    FROM (Film LEFT OUTER JOIN Film_Actor USING (film_id)) LEFT OUTER JOIN Actor USING (Actor_id)
    WHERE Film.release_year = 2004;
```

