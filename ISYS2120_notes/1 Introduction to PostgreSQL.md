### Simple Introduction

SQL is straightforward at first, but you can do some very complicated things here. We cover PostgreSQL but the overarching things carry over to most SQL languages, albeit each language having their slightly unique perks.

We mostly deal with the querying side of the language.

Let’s start with the most basic query.

```sql
-- We create a table

CREATE TABLE Student (
  studentId     INTEGER,
  name          VARCHAR(20) NOT NULL,
  address       VARCHAR(50),
  age           INTEGER,
  level         CHAR(20) DEFAULT Undergraduate
  PRIMARY KEY (studentId)
);
```

We have the following file, which we copy into the table we just created.

307088592,John Smith,Newtown,19

305422153,Sally Waters,Coogee,22

305678453,Pauline Winters,Bondi,20

316424328,Matthew Long,Camperdown,19

309145324,Victoria Tan,Maroubra,23

309187546,Niang Jin Phan,Kingsford,18

```pgsql
COPY Student (studentId, name, address, age) FROM 'students.csv' CSV;
```

```sql
SELECT * FROM Student; -- we select all the columns

SELECT name, address FROM Student; -- select the 2 columns.

SELECT Student.name FROM Student; -- specify the table if 
```

### Querying with conditions

Sometimes we need to specify the student that we want, or have multiple conditions to filter. Let’s add in another table

```pgsql
CREATE TABLE Enrolled (
  studentId        INTEGER,
  uosCode       CHAR(8),
  semester      CHAR(2),
  year          INTEGER,
  grade         VARCHAR(2),
  PRIMARY KEY (studentId,uosCode,Semester,Year),
  FOREIGN KEY (studentId) REFERENCES Student(studentId),
  FOREIGN KEY (uosCode) REFERENCES UnitOfStudy(uosCode)
);

COPY Enrolled (studentId, uosCode, semester, year, grade) FROM 'enrolments.csv' CSV;
```

316424328,INFO2120,S1,2010,D

305678453,INFO2120,S1,2010,HD

316424328,INFO3005,S1,2005,CR

305422153,INFO3404,S2,2008,P

316424328,COMP5338,S1,2006,D

309145324,INFO2120,S1,2010,F

309187546,INFO2005,S2,2004,D

```pgsql
CREATE TABLE UnitOfStudy (
  uosCode       CHAR(8),
  deptId        CHAR(3)     NOT NULL,
  uosName       VARCHAR(40) NOT NULL,
  credits       INTEGER     NOT NULL,
  PRIMARY KEY (uosCode)
);

COPY UnitOfStudy (uosCode, deptId, uosName, credits) FROM 'units.csv' CSV;
```

INFO1003,SIT,Introduction to IT,6

INFO2120,SIT,Database Systems I,6

INFO3404,SIT,Database Systems II,6

COMP5046,SIT,Statistical Natural Language Processing,6

COMP5138,SIT,Database Management Systems,6

COMP5338,SIT,Advanced Data Models,6

INFO2005,SIT,Database Management Introductory,3

INFO3005,SIT,Organisational Database Systems,3

MATH1002,MAT,Linear Algebra,3

COMP5703,SIT,Information Technology Project,12

```sql
SELECT name
    FROM Student
WHERE studentId = 305422153;

SELECT name 
    FROM Student
WHERE 
        studentId = 305422153 
    OR 
        studentId = 309187546;
    
SELECT studentId, grade, uosCode 
    FROM Enrolled WHERE 
        uosCode = 'INFO2120' 
    AND  
        grade = 'HD';
```

### More Conditional Queries

```pgsql
SELECT *
    FROM Student
WHERE age < 25;

SELECT *
    FROM Student
WHERE age BETWEEN 20 and 25;

SELECT *
    FROM Student
WHERE age IN (20,21,22)

SELECT *
    FROM Student
WHERE age >= 20 AND age <= 25

-- You can also specify the BETWEEN function for string values as well. 
SELECT *
    FROM Enrolled
WHERE grade BETWEEN 'CR' and 'D';

-- You can also use brackets to make your conditional queries more complex

SELECT *
    FROM Student
WHERE (age = 19 AND address = 'Newtown')
   OR (age = 20 AND address = 'Bondi');
```

### Aggregate Functions

```sql
SELECT AVG(age) FROM Student;

SELECT COUNT(uosCode) FROM UnitOfStudy

SELECT MAX(age) FROM Student;

SELECT MIN(age) FROM Student;

SELECT SUM(credits) FROM UnitOfStydy;

-- This is an interesting aggregate function I didn't know about:

SELECT ARRAY(uosName) FROM UnitOfStudy
```

### Other Functions

```sql
SELECT GREATEST(6, 42, 7), LEAST(7, 6, 42);
```

```sql
SELECT film_id, title, rental_rate, replacement_cost, GREATEST(rental_rate * 19, replacement_cost ) as late_fee
    FROM (Film INNER JOIN Film_Actor USING (film_id)) 
        INNER JOIN Actor USING (actor_id)
    WHERE first_name = 'JOE' AND last_name = 'SWANK'
```

### ORDER BY

```pgsql
SELECT *
    FROM Student
ORDER BY studentId DESC;

SELECT *
    FROM Student
WHERE age > 20
    ORDER BY studentId ASC, address ASC;
```

### DISTINCT and ALL

```pgsql
SELECT DISTINCT address
    FROM Student;

-- With ALL, you can specify to keep all values.
SELECT ALL address
    FROM Student
WHERE age BETWEEN 18 and 25;

-- And you can use aggregate functions on these as well

SELECT COUNT(DISTINCT original_language_id)
    FROM Film;
```

### GROUP BY

You can use \_\_GROUP BY\_\_ to group co-related data sets together and then compute some statistic (e.g. AVG) for the group.

```pgsql
SELECT uosCode, COUNT(studentId) AS enrolments
    FROM Enrolled
WHERE year >= 2006
    GROUP BY uosCode
```

```pgsql
SELECT uosCode, year_uni, COUNT(studentId) 
    FROM Enrolled
WHERE year >= 2006
    GROUP BY uosCode, year_uni;

-- Note: You cannot use GROUP BY without using both uosCode and year_uni, because there is no guarantee that there will only be one year for all the rows within the same group. 

-- You need to ensure that all attribute names which are listed behind SELECT are also listed behind GROUP BY
```

#### Supporting GROUP BY with HAVING

```pgsql
SELECT nationality, COUNT(actor_id)
    FROM (Actor LEFT JOIN Country ON (Actor.nationality = Country.short_code))
    GROUP BY nationality
        HAVING COUNT(actor_id) >= 2
    ORDER BY COUNT(actor_id) DESC, nationality
```

As you can see from the above, __HAVING__ is like a conditional filter on the __GROUP BY__

### LIMIT 

```pgsql
SELECT sid, name, grade
    FROM Student
        JOIN Transcript USING (sid)
WHERE uos_code = 'MATH1001'
ORDER BY grade DESC
LIMIT 3
```

You can simply __LIMIT__ your output simply with the LIMIT operator. 



Just building the data for Films.

```pgsql
START TRANSACTION;

SET CONSTRAINTS ALL DEFERRED;

CREATE TABLE Actor (
    actor_id     SMALLINT              PRIMARY KEY,
    first_name   CHARACTER VARYING(45) NOT NULL,
    last_name    CHARACTER VARYING(45) NOT NULL,
    nationality  CHAR(2)
);

CREATE TABLE Film (
    film_id              SMALLINT                   PRIMARY KEY,
    title                CHARACTER VARYING(255)     NOT NULL,
    description          CHARACTER VARYING(255),
    release_year         SMALLINT,
    language_id          SMALLINT,
    original_language_id SMALLINT,
    rental_duration      SMALLINT     DEFAULT 3     NOT NULL,
    rental_rate          NUMERIC(4,2) DEFAULT 4.99  NOT NULL,
    length               SMALLINT,
    replacement_cost     NUMERIC(5,2) DEFAULT 19.99 NOT NULL,
    rating               CHARACTER VARYING(6)       DEFAULT 'G',
    special_features     CHARACTER VARYING(255)
);

CREATE TABLE Film_Actor (
    actor_id    SMALLINT  NOT NULL REFERENCES Actor(actor_id) DEFERRABLE,
    film_id     SMALLINT  NOT NULL REFERENCES Film(film_id)   DEFERRABLE,
    PRIMARY KEY (actor_id, film_id)
);

COPY Actor         FROM 'actors.csv'          CSV;
COPY Film          FROM 'films.csv'           CSV;
COPY Film_Actor    FROM 'film_actors.csv'     CSV;

COMMIT;
```

271,ACADEMY DINOSAUR,A Epic Drama of a Feminist And a Mad Scientist who must Battle a Teacher in The Canadian Rockies,2006,1,,6,0.99,86,20.99,PG,"Deleted Scenes,Behind the Scenes"

272,ACE GOLDFINGER,A Astounding Epistle of a Database Administrator And a Explorer who must Find a Car in Ancient China,2006,1,,3,4.99,48,12.99,G,"Trailers,Deleted Scenes"

273,ADAPTATION HOLES,A Astounding Reflection of a Lumberjack And a Car who must Sink a Lumberjack in A Baloon Factory,2006,1,,7,2.99,50,18.99,NC-17,"Trailers,Deleted Scenes"

274,AFFAIR PREJUDICE,A Fanciful Documentary of a Frisbee And a Lumberjack who must Chase a Monkey in A Shark Tank,2006,1,,5,2.99,117,26.99,G,"Commentaries,Behind the Scenes"

275,AFRICAN EGG,A Fast-Paced Documentary of a Pastry Chef And a Dentist who must Pursue a Forensic Psychologist in The Gulf of Mexico,2006,1,2,6,2.99,130,22.99,G,Deleted Scenes

276,AGENT TRUMAN,A Intrepid Panorama of a Robot And a Boy who must Escape a Sumo Wrestler in Ancient China,1998,1,5,3,2.99,169,17.99,PG,Deleted Scenes

277,AIRPLANE SIERRA,A Touching Saga of a Hunter And a Butler who must Discover a Butler in A Jet Boat,2006,1,4,6,4.99,62,28.99,PG-13,"Trailers,Deleted Scenes"

278,AIRPORT POLLOCK,A Epic Tale of a Moose And a Girl who must Confront a Monkey in Ancient India,2006,1,1,6,4.99,54,15.99,R,Trailers

279,ALABAMA DEVIL,A Thoughtful Panorama of a Database Administrator And a Mad Scientist who must Outgun a Mad Scientist in A Jet Boat,2006,1,5,3,2.99,114,21.99,PG-280,"Trailers,Deleted Scenes"

281,ALADDIN CALENDAR,A Action-Packed Tale of a Man And a Lumberjack who must Reach a Feminist in Ancient China,2006,1,2,6,4.99,63,24.99,NC-17,"Trailers,Deleted Scenes"

282,ALAMO VIDEOTAPE,A Boring Epistle of a Butler And a Cat who must Fight a Pastry Chef in A MySQL Convention,2006,1,3,6,0.99,126,16.99,G,"Commentaries,Behind the Scenes"

283,ALASKA PHANTOM,A Fanciful Saga of a Hunter And a Pastry Chef who must Vanquish a Boy in Australia,2006,1,5,6,0.99,136,22.99,PG,"Commentaries,Deleted Scenes"

284,ALI FOREVER,A Action-Packed Drama of a Dentist And a Crocodile who must Battle a Feminist in The Canadian Rockies,2006,1,,4,4.99,150,21.99,PG,"Deleted Scenes,Behind the Scenes"

285,ALICE FANTASIA,A Emotional Drama of a A Shark And a Database Administrator who must Vanquish a Pioneer in Soviet Georgia,2006,1,,6,0.99,94,23.99,NC-286,"Trailers,Deleted Scenes,Behind the Scenes"

287,ALIEN CENTER,A Brilliant Drama of a Cat And a Mad Scientist who must Battle a Feminist in A MySQL Convention,2006,1,1,3,2.99,46,10.99,NC-288,"Trailers,Commentaries,Behind the Scenes"

289,ALLEY EVOLUTION,A Fast-Paced Drama of a Robot And a Composer who must Battle a Astronaut in New Orleans,2006,1,1,6,2.99,180,23.99,NC-17,"Trailers,Commentaries"

290,ALONE TRIP,A Fast-Paced Character Study of a Composer And a Dog who must Outgun a Boat in An Abandoned Fun House,2006,1,,3,0.99,82,14.99,R,"Trailers,Behind the Scenes"

291,ALTER VICTORY,A Thoughtful Drama of a Composer And a Feminist who must Meet a Secret Agent in The Canadian Rockies,2006,1,2,6,0.99,57,27.99,PG-13,"Trailers,Behind the Scenes"

292,AMADEUS HOLY,A Emotional Display of a Pioneer And a Technical Writer who must Battle a Man in A Baloon,2006,1,5,6,0.99,113,20.99,PG,"Commentaries,Deleted Scenes,Behind the Scenes"

293,AMELIE HELLFIGHTERS,A Boring Drama of a Woman And a Squirrel who must Conquer a Student in A Baloon,2006,1,6,4,4.99,79,23.99,R,"Commentaries,Deleted Scenes,Behind the Scenes"

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

41,JODIE,DEGENERES,FR

42,TOM,MIRANDA,NZ

43,KIRK,JOVOVICH,RU

44,NICK,STALLONE,US

45,REESE,KILMER,US

46,PARKER,GOLDBERG,HU

47,JULIA,BARRYMORE,UK

48,FRANCES,DAY-LEWIS,UK

49,ANNE,CRONYN,US

50,NATALIE,HOPKINS,US

51,GARY,PHOENIX,US

52,CARMEN,HUNT,UK

53,MENA,TEMPLE,US

54,PENELOPE,PINKETT,UK

55,FAY,KILMER,US

56,DAN,HARRIS,US

57,JUDE,CRUISE,VN

58,CHRISTIAN,AKROYD,US

59,DUSTIN,TAUTOU,FR

60,HENRY,BERRY,UK

61,CHRISTIAN,NEESON,IE

62,JAYNE,NEESON,US

63,CAMERON,WRAY,NZ

64,RAY,JOHANSSON,UK

65,ANGELA,HUDSON,US

66,MARY,TANDY,US

67,JESSICA,BAILEY,UK

68,RIP,WINSLET,UK

69,KENNETH,PALTROW,ZA

70,MICHELLE,MCCONAUGHEY,IE

71,ADAM,GRANT,UK

72,SEAN,WILLIAMS,UK

73,GARY,PENN,US

74,MILLA,KEITEL,DE

75,BURT,POSEY,UK

76,ANGELINA,ASTAIRE,US

77,CARY,MCCONAUGHEY,IE

78,GROUCHO,SINATRA,US

79,MAE,HOFFMAN,US

80,RALPH,CRUZ,US

81,SCARLETT,DAMON,US

82,WOODY,JOLIE,US

83,BEN,WILLIS,US

84,JAMES,PITT,US

85,MINNIE,ZELLWEGER,UK

86,GREG,CHAPLIN,US

87,SPENCER,PECK,US

88,KENNETH,PESCI,IT

89,CHARLIZE,DENCH,US

90,SEAN,GUINESS,IE

91,CHRISTOPHER,BERRY,US

92,KIRSTEN,AKROYD,US

93,ELLEN,PRESLEY,US

94,KENNETH,TORN,UK

95,DARYL,WAHLBERG,ZA

96,GENE,WILLIS,US

97,MEG,HAWKE,AU

98,CHRIS,BRIDGES,US

99,JIM,MOSTEL,AT

100,SPENCER,DEPP,US

101,SUSAN,DAVIS,US

102,WALTER,TORN,US

103,MATTHEW,LEIGH,UK

104,PENELOPE,CRONYN,US

105,SIDNEY,CROWE,AU

106,GROUCHO,DUNST,NL

107,GINA,DEGENERES,FR

108,WARREN,NOLTE,US

109,SYLVESTER,DERN,DK

110,SUSAN,DAVIS,US

111,CAMERON,ZELLWEGER,UK

112,RUSSELL,BACALL,IN

113,MORGAN,HOPKINS,US

114,MORGAN,MCDORMAND,IE

115,HARRISON,BALE,AU

116,DAN,STREEP,US

117,RENEE,TRACY,US

118,CUBA,ALLEN,CA

119,WARREN,JACKMAN,AU

120,PENELOPE,MONROE,US

121,LIZA,BERGMAN,DE

122,SALMA,NOLTE,US

123,JULIANNE,DENCH,US

124,SCARLETT,BENING,IT

125,ALBERT,NOLTE,US

126,FRANCES,TOMEI,IN

127,KEVIN,BACON,US

128,CATE,MCQUEEN,IE

129,DARYL,CRAWFORD,UK

130,GRETA,KEITEL,DE

131,JANE,JACKMAN,AU

132,ADAM,HOPPER,US

133,RICHARD,PENN,CA

134,GENE,HOPKINS,US

135,RITA,REYNOLDS,US

136,ED,MANSFIELD,CA

137,MORGAN,WILLIAMS,UK

138,LUCILLE,DEE,CZ

139,EWAN,GOODING,HU

140,WHOOPI,HURT,US

141,CATE,HARRIS,UK

142,JADA,RYDER,CA

143,RIVER,DEAN,US

144,ANGELA,WITHERSPOON,UK

145,KIM,ALLEN,CA

146,ALBERT,JOHANSSON,UK

147,FAY,WINSLET,UK

148,EMILY,DEE,FR

149,RUSSELL,TEMPLE,UK

150,JAYNE,NOLTE,US

151,GEOFFREY,HESTON,US

152,BEN,HARRIS,UK

153,MINNIE,KILMER,US

154,MERYL,GIBSON,AU

155,IAN,TANDY,IE

156,FAY,WOOD,CA

157,GRETA,MALDEN,GR

158,VIVIEN,BASINGER,US

159,LAURA,BRODY,US

160,CHRIS,DEPP,AU

161,HARVEY,HOPE,CA

162,OPRAH,KILMER,US

163,CHRISTOPHER,WEST,ZA

164,HUMPHREY,WILLIS,US

165,AL,GARLAND,EG

166,NICK,DEGENERES,FR

167,LAURENCE,BULLOCK,US

168,WILL,WILSON,JP

169,KENNETH,HOFFMAN,US

170,MENA,HOPPER,IN

171,OLYMPIA,PFEIFFER,DE

172,GROUCHO,WILLIAMS,ES

173,ALAN,DREYFUSS,NL

174,MICHAEL,BENING,IN

175,WILLIAM,HACKMAN,US

176,JON,CHASE,US

177,GENE,MCKELLEN,IE

178,LISA,MONROE,US

179,ED,GUINESS,IE

180,JEFF,SILVERSTONE,UK

181,MATTHEW,CARREY,KR

182,DEBBIE,AKROYD,US

183,RUSSELL,CLOSE,US

184,HUMPHREY,GARLAND,BR

185,MICHAEL,BOLGER,AT

186,JULIA,ZELLWEGER,PL

187,RENEE,BALL,ZA

188,ROCK,DUKAKIS,GR

189,CUBA,BIRCH,CN

190,AUDREY,BAILEY,BR

191,GREGORY,GOODING,DE

192,JOHN,SUVARI,IN

193,BURT,TEMPLE,US

194,MERYL,ALLEN,AU

195,JAYNE,SILVERSTONE,UK

196,BELA,WALKEN,EG

197,REESE,WEST,US

198,MARY,KEITEL,AT

199,JULIA,FAWCETT,UK

200,THORA,TEMPLE,US

1,1

2,3

5,19

10,1

10,9

12,16

19,2

19,3

20,1

21,6

22,9

23,6

24,3

26,9

27,19

28,14

29,10

30,1

35,10

36,15

37,10

37,12

37,19

40,1

40,11

41,4

43,19

45,18

51,5

52,20

53,1

53,9

55,8

57,16

59,5

62,6

64,3

64,10

68,9

69,15

75,12

77,13

81,4

81,11

84,19

85,2

85,14

88,4

90,2

90,11

91,13

94,13

96,8

99,7

102,20

103,5

104,19

105,12

105,15

108,1

108,6

108,9

109,12

110,8

114,13

117,10

117,15

123,3

130,9

133,7

136,20

137,6

137,14

138,8

139,20

142,10

142,18

144,18

146,12

146,16

147,4

155,20

157,10

159,20

160,2

162,1

162,4

162,7

162,18

164,15

169,6

170,7

170,15

174,11

175,9

176,13

177,12

180,12

181,5

185,7

187,17

188,1

188,10

188,14

191,16

192,16

194,9

197,6

200,5