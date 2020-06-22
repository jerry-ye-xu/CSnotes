Data typeDescriptionExample value`DATE`A date`'2011-04-03'``TIME`A time`'19:14:06.977434+11'``TIMESTAMP`A date and time`'2011-04-03 19:14:33.974799+11'`

PostgreSQL provides access to a number of date and time constants. Some of them are shown below:

__CURRENT_DATE__
The date component of the current system time.

__CURRENT_TIME__
The time component of the current system time.

__CURRENT_TIMESTAMP__
The full current system time.
`NOW()`A function alias for __CURRENT_TIME__

ComponentMeaning`DAY`Retrieve the day of a `DATE` or `TIMESTAMP` value.`MONTH`Retrieve the month of a `DATE` or `TIMESTAMP` value.`YEAR`Retrieve the year of a `DATE` or `TIMESTAMP` value.`HOUR`Retrieve the hour of a `TIME` or `TIMESTAMP` value.`MINUTE`Retrieve the minute field of a `TIME` or `TIMESTAMP`value.`SECOND`Retrieve the second of a `TIME` or `TIMESTAMP` value.

You can also extract the __Day of Year__

```pgsql
SELECT EXTRACT(DOY FROM DATE '2016-04-22');
```

| day of year |
| ----------- | 
| 113 |

```pgsql
SELECT COUNT(film_id) as count
    FROM Film
        WHERE release_year > (EXTRACT(YEAR FROM CURRENT_DATE) - 10) AND release_year <= (EXTRACT(YEAR FROM CURRENT_DATE))
```

### Timezones

ComponentMeaning`TIMEZONE`Retrieve the timezone offset from UTC in seconds of a `TIMESTAMP` value.`TIMEZONE_HOUR`Retrieve the hour component of the timezone offset from UTC of a `TIMESTAMP` value`TIMEZONE_MINUTE`Retrieve the minute component of the timezone offset from UTC of a `TIMESTAMP`value.



### Complicated Example

```pgsql
SELECT to_char(EXTRACT(TIMEZONE_HOUR FROM CURRENT_TIMESTAMP), 'UT"C"SG00') || ':' || to_char(EXTRACT(TIMEZONE_MINUTE FROM CURRENT_TIMESTAMP), 'FM00') as tz_offset;

-- The "C" is to ignore special effects from that C
```