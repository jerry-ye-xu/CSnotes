### User-Defined Domains

PostgreSQL allows for user-defined domains, which are data types with constraints such as NOT NULL, CHECK etc.

```pgsql
CREATE DOMAIN Dollars numeric(12, 2);

CREATE DOMAIN contact_name AS
    VARCHAR NOT NULL CHECK(value !~ '\s');

-- contact_name cannot be null and cannot contain spaces.
```

### ALTER TABLE 

```pgsql
ALTER TABLE Student ALTER COLUMN WAM SET NOT NULL;
```

If existing data violates this constraint, then the constraint is _NOT_ added!!

Other examples include

```pgsql
ADD CONSTRAINT constraint_name new_constraint
DROP CONSTRAINT constraint_name
RENAME CONSTRAINT old_name TO new_name
ALTER COLUMN attribute_name domain_constraint
```

Question: What is the "constraint_name" part?

```pgsql
ALTER TABLE Student
    ADD CONSTRAINT minimum_age
        CHECK (age > 12);
```