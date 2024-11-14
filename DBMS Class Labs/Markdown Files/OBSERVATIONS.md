# Observations

### Is: `alter table add column newcolumn int, alter column newcolumn set not null;` a valid PostreSQL query?

The query as written is not valid in PostgreSQL. PostgreSQL does not allow you to alter a column and set constraints like `NOT NULL` in a single `ALTER TABLE` command if multiple operations are combined with commas. Instead, you need to separate each `ALTER` operation into its own `ALTER TABLE` statement.

Here's the correct way to do it:

```sql
ALTER TABLE your_table_name
ADD COLUMN newcolumn INT;

ALTER TABLE your_table_name
ALTER COLUMN newcolumn SET NOT NULL;
```

Each `ALTER` operation is performed in a separate command. This is necessary because PostgreSQL requires each `ALTER TABLE` subcommand to be executed independently when setting constraints like `NOT NULL`.

---

### What about: `alter table add column newcolumn date, alter column newcolumn set default to current_date;`

The query as written is also not valid in PostgreSQL. Specifically, there are two issues:

1. **Combining Operations with a Comma**: As before, PostgreSQL does not support combining multiple `ALTER` operations with a comma.
2. **Syntax for Setting a Default Value**: The syntax for setting a default value is `SET DEFAULT`, without the `TO`.

Here's the correct way to execute this in PostgreSQL:

```sql
ALTER TABLE your_table_name
ADD COLUMN newcolumn DATE;

ALTER TABLE your_table_name
ALTER COLUMN newcolumn SET DEFAULT CURRENT_DATE;
```

This will add a new `DATE` column called `newcolumn` and set its default value to the current date.

---

### what about: `alter table rename col to cols, alter column col2 set not null;`

The query as written is not valid in PostgreSQL because:

1. **Combining Operations with a Comma**: PostgreSQL does not support combining multiple `ALTER TABLE` operations in a single statement using commas.
2. **Reference to `col2` in the Second Statement**: After renaming `col` to `cols`, there is no indication of `col2` in the syntax provided, but assuming `col2` is another existing column, it should be referenced in a separate statement.

The correct way to perform these operations is with two separate `ALTER TABLE` commands:

```sql
ALTER TABLE your_table_name
RENAME COLUMN col TO cols;

ALTER TABLE your_table_name
ALTER COLUMN col2 SET NOT NULL;
```

This will rename the column `col` to `cols` and set the `NOT NULL` constraint on `col2`. Each operation is executed independently in PostgreSQL.
