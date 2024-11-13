# C. Consider the following relations for an Order Processing Database application in a Company

## Relational Diagram:

### CUSTOMER

- Customer_No
- Customer_Name
- Customer_DoB
- Customer_Address (Multi-valued Attribute)

### CUSTOMER_ORDER

- Invoice_No
- Order_Date
- Quantity
- Customer_No

### ITEM

- Item_ID
- Item_ID
- Item_Name
- Unit_Price

### DISPATCH

- Desp_ID
- Time
- Date
- Item_ID

---

1. Develop DDL queries to implement the above schema with proper data type and enforceprimarykey, foreign key constraints and populate atleast 5 tuples on each relation.
2. Develop a SQL query to rename the ITEM table as PRODUCTS.
3. Develop a SQL query to find customer details who placed more products.
4. Create a Left Outer Join SQL query between Customer and Products.
5. Create a simple View called Dispatch with Customer Name, Address and Invoice_No details.
6. Develop a SQL query to find product details who Item_Names starts with A.
7. Develop a SQL query to find the Total Number of dispatch on today.
