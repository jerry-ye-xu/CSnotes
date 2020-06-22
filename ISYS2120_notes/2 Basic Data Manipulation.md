Let’s quickly talk about updating, deleting values in databases.

### Basic Data Types

We quickly look at the datatypes 

__SMALLINT__ — 2 byte numeric integer value
__INTEGER__ — 4 byte numeric integer value
__FLOAT__ — 8 byte floating point value
__CHAR(n)__ — fixed-length string of n characters
__VARCHAR(n)__ — variable-length string of 0 to n characters

__DATE__ - a date object
__TIME__ - a time object
__TIMESTAMP__ - a datetime object 

__SERIAL__ - treated as an integer, PostgreSQL will automatically create a new value for each new insert. 

### Data Manipulation Basics

```pgsql
INSERT INTO Actor VALUES(4711, 'Arnold', 'Schwarzenegger', 'AT');

SELECT * FROM Country;
UPDATE Country 
   SET name= 'Confoederatio Helvetica'
 WHERE short_code = 'CH';
SELECT * FROM Country;

-- NOTE: Update returns the number of rows being affected. 

-- NOTE: If you do not include the WHERE clause, ALL the rows in the table are updated!

DELETE FROM 
    Language 
WHERE name = 'German';
```

### The CREATE VIEW function

```pgsql
CREATE VIEW CurrentStudents AS
    SELECT studentId, uosCode, semester
FROM Enrolled
   WHERE year = 2016;
  
-- NOTE: Pay special attention to the "AS" in the query above. 

-- Creates a view and performs SELECT over it.
-- You can query the created "VIEW" as if it were a normal table. 
SELECT *
    FROM CurrentStudents;

-- to remove a view, just drop it.
DROP VIEW CurrentStudents;
```

```pgsql
-- SERIAL 

CREATE TABLE Test ( 
    id  SERIAL,
    val CHAR
);
INSERT INTO Test(val) VALUES ('a'), ('b');
SELECT * FROM Test;
```

Although a view is queried like a table, there is nothing stored in it. The contents are dynamically retrieved from the underlying tables each time it is referenced in a query.

__AS__ can also be used to rename columns. That is super useful.

### Building the Table

```pgsql
START TRANSACTION;

SET CONSTRAINTS ALL DEFERRED;

CREATE TABLE Country (
    country_id  SMALLINT              PRIMARY KEY,
    short_code  CHAR(2)               UNIQUE NOT NULL,
    name        CHARACTER VARYING(25) NOT NULL
);

CREATE TABLE Actor (
    actor_id     SMALLINT              PRIMARY KEY,
    first_name   CHARACTER VARYING(45) NOT NULL,
    last_name    CHARACTER VARYING(45) NOT NULL,
    nationality  CHAR(2)               REFERENCES Country(short_code) DEFERRABLE
);

COPY Country FROM 'countries.csv' CSV;
COPY Actor   FROM 'actors.csv'    CSV;

COMMIT;
```

1,PENELOPE,GUINESS,IE

2,NICK,WAHLBERG,SE

3,ED,CHASE,US

4,JENNIFER,DAVIS,CA

5,JOHNNY,LOLLOBRIGIDA,IT

6,BETTE,NICHOLSON,US

7,GRACE,MOSTEL,US

8,MATTHEW,JOHANSSON,UK

9,JOE,SWANK,US

10,CHRISTIAN,GABLE,AU

11,ZERO,CAGE,US

12,KARL,BERRY,UK

13,UMA,WOOD,UK

14,VIVIEN,BERGEN,DE

15,CUBA,OLIVIER,MX

16,FRED,COSTNER,US

17,HELEN,VOIGHT,NZ

18,DAN,TORN,ZA

19,BOB,FAWCETT,UK

20,LUCILLE,TRACY,DK

21,KIRSTEN,PALTROW,PL

22,ELVIS,MARX,AT

23,SANDRA,KILMER,IE

24,CAMERON,STREEP,UK

25,KEVIN,BLOOM,AU

26,RIP,CRAWFORD,UK

27,JULIA,MCQUEEN,IE

28,WOODY,HOFFMAN,CH

29,ALEC,WAYNE,US

30,SANDRA,PECK,US

31,SISSY,SOBIESKI,RU

32,TIM,HACKMAN,US

33,MILLA,PECK,US

34,AUDREY,OLIVIER,UK

35,JUDY,DEAN,TR

36,BURT,DUKAKIS,GR

37,VAL,BOLGER,DK

38,TOM,MCKELLEN,IE

39,GOLDIE,BRODY,AU

40,JOHNNY,CAGE,US

1,AU,Australia

2,AT,Austria

3,BR,Brazil

4,CA,Canada

5,CN,China

6,CZ,Czech Republic

7,DK,Denmark

8,EG,Egypt

9,FR,France

10,DE,Germany

11,GR,Greece

12,HU,Hungary

13,IN,India

14,IE,Ireland

15,IT,Italy

16,JP,Japan

17,KR,"Korea, Republic of"

18,MX,Mexico

19,NL,Netherlands

20,NZ,New Zealand

21,PL,Poland

22,RU,Russia

23,ZA,South Africa

24,ES,Spain

25,SE,Sweden

26,CH,Switzerland

27,TR,Turkey

28,VN,Vietnam

29,UK,United Kingdom

30,US,United States