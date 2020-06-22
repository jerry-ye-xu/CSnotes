### Basic Math

```pgsql
SELECT 10 + 2;
SELECT 10 - 2;
SELECT 10 * 2;
SELECT 10 / 2;
```

### Math Functions

```pgsql
mod(a, b);

round(n, d);

trunc(n, d);

ceil(n);

floor(n);

abs(n);
```

### Special Values

SQL supports a few special values for floating point data:

__NaN__ - not a number

__infinity__ - larger than any number

__-infinity__ - smaller than any number

__You need to input them as strings in SQL:__

e.g. 'NaN' or 'infinity' 

```pgsql
CREATE TABLE Test ( val FLOAT );
INSERT INTO  Test VALUES (0), ('NaN'), (NULL);

\pset null '[NULL]'
SELECT * FROM Test;
SELECT * FROM Test WHERE val IS NULL;
```

| val |
| --- |
| 0 |
| NaN |
| [NULL] |

| val |
| --- |
| [NULL] |

