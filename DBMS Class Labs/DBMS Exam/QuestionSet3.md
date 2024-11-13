# Set 3: Apartment Rental System

## Relational Diagram:

### Tenant

- Tenant_ID (PK)
- Name
- Contact_Info

### Apartment

- Apartment_ID (PK)
- Location
- Rent

### Lease

- Lease_ID (PK)
- Tenant_ID (FK)
- Apartment_ID (FK)
- Start_Date
- End_Date

### Payment

- Payment_ID (PK)
- Lease_ID (FK)
- Payment_Amount
- Payment_Date

---

1. Implement the Relational Model using SQL DDL commands
2. Alter/Modify the structure of the table: Write an SQL query to alter the structure of the Lease table ADD Security_Deposit DECIMAL(10,2).
3. Aggregate Function: Write an SQL query to Find the total rent collected for each apartment.
4. Join: Write an SQL query to List all tenants along with their apartment details and lease duration.
5. View: Write an SQL query to Create a view to display tenant details with their apartment and payment history.
6. Derived Attribute: Write an SQL query to Calculate the remaining lease duration for each tenant.
7. Nested query: Write an SQL query to Find tenants who have paid more than $2000 in total rent.
8. LIKE Operation: Write an SQL query to find tenants whose contact information ends with 'gmail.com'.
9. GROUP BY and ORDER BY: Write an SQL query to group apartments by location and display the average rent for each location, ordered by average rent in ascending order.
