### Referential Integrity

You can have:

_NO ACTION:_ Delete/update is rejected

_CASCADE:_ Delete all tuples that refer to deleted tuple

_SET NULL:_ resets foreign key to NULL

_SET DEFAULT:_ Sets foreign key value of referencing tuple to a default value

```pgsql
CREATE TABLE Enrolled(
    sid CHAR(10),
    uos CHAR(8),
    grade CHAR(2),
    PRIMARY KEY (sid, uos)
    FOREIGN KEY (sid) REFERENCES Student 
        ON DELETE CASCADE
        ON UPDATE NO ACTION
);

-- NOTE: These referential integrity constraints refer to modifications on the PARENT TABLE!
```

_NOTE:_ These referential integrity constraints refer to modifications on the _parent table_!

```pgsql
CREATE TABLE Assessment(
    sid INTEGER REFERENCES Student,
    uos VARCHAR(8) REFERENCES UnitOfStudy,
    empid INTEGER REEFERENCES Lecturer,
    mark INTEGER,
    grade VARCHAR(2),
    CONSTRAINT maxMarks CHECK(mark BETWEEN 0 AND 100),
    CONSTRAINT grade CHECK(grade IN ('FA', 'PA', 'CR', 'D', 'HD'))
);
```

These checks can be completed immediately or deferred.

```pgsql
CREATE TABLE UnitOfStudy(
    uos_code VARCHAR(8),
    title VARCHAR(220),
    lecturer INTEGER,
    credit_points INTEGER,
    CONSTRAINT UnitOfStudy_PK PRIMARY KEY (uos_code),
    CONSTRAINT UnitOfStudy_FK FOREIGN KEY (lecturer)
    REFERENCES Lecturer DEFERABBLE INITIALLY DEFERRED
);

-- check at the end of code, but allowed to dynamically change later 
```

or you can have

```pgsql
CREATE TABLE UnitOfStudy(......REFERENCES Lecturer DEFERABBLE INITIALLY IMMEDIATE);-- Immediate checking but allowed to dynamically change later CREATE TABLE UnitOfStudy(......REFERENCES Lecturer NOT DEFERRABLE);
```

### Using Assertions

Assertions can be used to check multiple databases. They are like schema objects (tables/views) and when an assertion is specified, the system tests it for validity, and tests it again on every update that may violate it. 

This introduces a _significant amount of overhead_ and thus should be used with caution.

```pgsql
CREATE TABLE Sailors (
    sid INTEGER
    sname CHAR (10)
    rating INTEGER
    PRIMARY KEY (sid)
    CHECK (rating >=1 AND rating <=10)
--    CHECK ((SELECT count(s.sid) FROM Sailors s
--    + (SELECT count(b.bid) FROM Boats b) < 100)
);
```

Instead of putting it inside the table. We can use an _ASSERTION_

```pgsql
CREATE ASSERTION smallclub CHECK(     (SELECT COUNT(s.sid) FROM Sailors s)  + (SELECT COUNT(b.bid) FROM Boats b) < 100) )
```

```pgsql
CREATE ASSERTION mark_constraint CHECK(
    NOT EXISTS (SELECT sid
    FROM Assessment
    GROUP BY sid,uos_code
    HAVING sum(mark) > 100)
)
```

_Assertions are not supported by any DBMS at the moment..._

### Triggers

A trigger is an SQL statement that executes automatically when a pre-specified condition has been met. The trigger consists of 3 parts:

_ON_ event _IF_ precondition _THEN_ trigger

Triggers can be used to maintain foreign-key and semantic constraints, and is often used with _ON DELETE_ and _ON UPDATE_. Some business rules can be enforced with trigger, whilst assertions can be implemented with 2 triggers.

Exceptions can be modelled as update operations, which simplifies database design.

The _trigger event_ can be INSERT, DELETE, UPDATE and operation can be on specific attributes, e.g.

```pgsql
CREATE TRIGGER overdraft_trigger 
    AFTER UPDATE OF balance
        ON account
```

For triggers, there are different levels of granularity. 

_row\_level:_ the event trigger is when a row changes --> a single statment may trigger multiple events
_statement\_level:_ the event trigger is an SQL statement instead --> a statement that changes multiple rows is an event

For PostgreSQL, the syntax is slightly different as well.

The SQL (1999) Syntax is given below.

```pgsql
-- THIS IS THE OLD SYNTAX

CREATE TRIGGER gradeUpgrade
    AFTER INSERT OR UPDATE ON Assessment
BEGIN
    UPDATE Enrolled E
        SET grade='P'
    WHERE grade IS NULL
        AND (SELECT SUM(mark)
                FROM Assessment A
                    WHERE A.sid = E.sid AND
                          A.uos = E.uosCode) >= 50;
END;
```

In PostgreSQL you need to 

1) Define a trigger function

2) Before you can declare the actual trigger that uses it

Belong is an example of a _BEFORE_ trigger.

```pgsql
-- 1)

CREATE FUNCTION AbortEnrolment() RETURNS trigger AS $$
    BEGIN
        RAISE EXCEPTION ‘unit IS FULL’; -- aborts transaction
    END
$$ LANGUAGE pgplsql;

-- 2)
CREATE TRIGGER Max_EnrollCheck
    BEFORE INSERT ON Transcript
        FOR EACH ROW
            WHEN ((SELECT COUNT (T.studId)
                FROM Transcript T
                    WHERE T.uosCode = NEW.uosCode AND
                          T.semester = NEW.semester) >= (
                            SELECT U.maxEnroll
                                FROM UnitOfStudy U
                                    WHERE U.uosCode = NEW.uosCode )
                                    )
EXECUTE PROCEDURE AbortEnrolment();
```

Below is an example of an _AFTER_ trigger.

```pgsql
CREATE TABLE Log ( … );

CREATE FUNCTION SalaryLogger() RETURNS trigger AS $$
    BEGIN
        INSERT INTO Log
            VALUES (CURRENT_DATE, SELECT AVG(Salary)
                FROM Employee );
        RETURN NEW;
    END
$$ LANGUAGE plpgsql;

CREATE TRIGGER RecordNewAverage
    AFTER UPDATE OF Salary ON Employee
    FOR EACH STATEMENT
EXECUTE SalaryLogger();

-- Keeps track of salary averages in the log
```

_BEFORE_ triggers: Checking integrity constaints

_AFTER_ triggers: Integrity maintenance and update propagation