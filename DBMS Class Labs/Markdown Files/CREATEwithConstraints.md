```
CREATE TABLE customer_order (
    invoice_no SERIAL PRIMARY KEY,
    order_date DATE NOT NULL,
    quantity INT NOT NULL,
    customer_no INT,
    item_id INT,

    -- Naming the foreign key constraints
    CONSTRAINT fk_customer_no FOREIGN KEY (customer_no) REFERENCES customer(customer_no),
    CONSTRAINT fk_item_id FOREIGN KEY (item_id) REFERENCES product(item_id)
);
```

```
CREATE TABLE customer_order (
    invoice_no SERIAL PRIMARY KEY,
    order_date DATE NOT NULL,
    quantity INT NOT NULL,
    customer_no INT REFERENCES customer(customer_no),
    item_id INT,
    FOREIGN KEY (item_id) REFERENCES product(item_id)
);
```
