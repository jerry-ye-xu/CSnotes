### Authorisation 

In DBMS systems, instead of authenticating with a username and password, DBA will obtain _grant_ and _revoke_ privileges to end-users depending on their role in the organisation.

The DBMS is then responsible for tracking which level of access a user is allowed at any given time, and subsequently restricting their activities to the database. 

The corresponding PostgreSQL are as follows:

```pgsql
-- basic skeleton

GRANT select 
    ON table
        TO x, y, z;

REVOKE select
    ON table
        TO x, y, z;
```

If you revoke a privilege from a user, then all privileges that that user passed on to another user will be revoked as well.

This list of privileges are:

[SELECT, INSERT, DELETE, UPDATE, REFERENCES]

Only the Owner of the table can

[CREATE, DROP, ALTER]

Let’s look at some more examples

```pgsql
GRANT insert, select 
    ON Student TO Jerry;

GRANT delete 
    On Student to John WITH GRANT OPTION;

-- if a user has GRANT OPTION, then they are allowed to pass their privilege onto others (with or without passing on the GRANT OPTION).

GRANT update(title)
    ON UnitofStudy TO Jeremy;

GRANT select 
    ON FemaleStudents
        To Puppy, Kitty;
```

### Incorporating VIEWS for Security

Sometimes we want to abstract away certain layers.

Hence we want to create a “VIEW” for end-users that hides details in the underlying relation(s).

VIEWs are stored as a definition, rather than a set of tuples. This means that no storage space is wasted and that the data will refresh itself each time it is run.

```pgsql
CREATE VIEW FemaleStudents2018 (sid, grade)
    AS SELECT S.sid, E.grade
        FROM Student S, Enrolled E  
            WHERE S.sid=E.sid AND
                  S.gender = 'F' AND
                  E.semester = '2018sem1'
```

You can of course, update the _VIEW_ and the underlying base tables will be updated to reflect the changes.

If you don't specify all the values in the tuple set for a particular table when updating the view, then the table will automatically populate the appropriate column with a NULL. It will also use the DEFAULT value if you set one. 

However, the new tuple introduced will be not visible in the _VIEW_. One way you can solve this is to allow the insertion (provided that _WITH CHECK OPTION_ has not been appended to the _CREATE VIEW_ statement. The _CHECK OPTION_ can be allowed to a _VIEW_ to prevent inserts to rows where the WHERE clause in the select\_statement is not true. It also prevents updates that would cause the select\_statement to not be true. You can also set _LOCAL_ and _CASCADED_ _CHECK OPTIONS_ in order to determine the extent of testing of the INSERT.

### Authorisation Mode REFERENCES

The _REFERENCES_ privilege allows the user to create FOREIGN KEYS across tables. However, the user needs privileges on both the REFERENCE and REFERENCED tables. This can be important because if you are allowed to create FKs, then to some extent you will have knowledge of information about the other tables that you are referencing. With users having REFERENCE privilege, you can check for the existance of values in another column.  

```pgsql
GRANT references
    ON Student to Jerry;
```

### Role Based Authorisation

Sometimes, you can create a role and specify a group of users, and then grant the role itself specific privileges.

```pgsql
CREATE ROLE manager;

GRANT select, insert ON students TO manager;

GRANT manager TO Jerry;
```