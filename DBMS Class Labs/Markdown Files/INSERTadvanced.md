The error here occurs because the `INSERT INTO ... VALUES` syntax expects a list of values, not a `SELECT` statement. To insert data from another table, you need to use the `INSERT INTO ... SELECT` syntax instead of `INSERT INTO ... VALUES`.

Here’s how you should write the query:

```sql
INSERT INTO customer_order (invoice_no, order_date, quantity, customer_no, item_id)
SELECT invoice_no, order_date, quantity, customer_no, item_id
FROM custom_order;
```

### Explanation:

- `INSERT INTO customer_order (column1, column2, ...)`: This specifies the columns you want to insert data into.
- `SELECT column1, column2, ... FROM custom_order`: This selects the data from `custom_order` to be inserted into `customer_order`.

This syntax allows you to copy data from one table (`custom_order`) to another (`customer_order`).

To insert the remaining rows from the `customer_order` table into the `dispatch` table (based on the `invoice_no` values that are not yet in `dispatch`), you can use an `INSERT INTO ... SELECT` query with a `WHERE` clause to filter out the `invoice_no` values that are already in `dispatch`.

Here’s the SQL command that accomplishes this:

```sql
INSERT INTO dispatch (time, date, item_id, invoice_no)
SELECT
    '15:00:00'::TIME AS time,      -- Set a default time (or adjust as needed)
    order_date AS date,            -- Use the order_date as the date for dispatch
    item_id,
    invoice_no
FROM
    customer_order
WHERE
    invoice_no NOT IN (SELECT invoice_no FROM dispatch);
```

### Explanation:

1. **`INSERT INTO dispatch`**: This specifies that we are inserting new rows into the `dispatch` table.
2. **`SELECT ... FROM customer_order`**: We select columns from `customer_order` to be inserted.
   - `time`: Sets a default time (you can adjust this as needed).
   - `date`: Uses `order_date` from `customer_order` as the `date` in `dispatch`.
   - `item_id` and `invoice_no`: Copies these values directly from `customer_order`.
3. **`WHERE invoice_no NOT IN (SELECT invoice_no FROM dispatch)`**: This filters out any rows where `invoice_no` already exists in `dispatch`, ensuring that only new `invoice_no` values are inserted.

This command will add only the rows from `customer_order` that have `invoice_no` values missing in `dispatch`.
