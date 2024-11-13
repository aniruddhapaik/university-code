# CSCA 416: DBMS LAB Viva Voce Answers

### 1. In normalization, the process of eliminating redundancy and organizing data into smaller tables is known as **\_\_\_\_**.

- In normalization, the process of eliminating redundancy and organizing data into smaller, well-structured tables is known as **decomposition**.  
- This process involves dividing a database into multiple tables to ensure that each table contains data related to a single concept or entity. This is done to avoid duplication, maintain data integrity, and optimize data storage. Decomposition is often guided by normalization forms (e.g., First Normal Form, Second Normal Form, etc.), with the goal of achieving a normalized database structure that reduces anomalies in data insertion, update, and deletion.

### 2. The concept of separating the logical schema from the physical schema is known as **\_\_\_\_**.

- The concept of separating the logical schema from the physical schema is known as **data independence**.
- Data independence allows changes to be made to the physical storage of data without affecting the logical structure of the database (and vice versa). This separation ensures that applications can interact with data at a higher logical level without needing to know details about how the data is physically stored or managed on disk. There are two types of data independence:

1. **Logical data independence** – the ability to change the logical schema without altering the external schema or application programs.
2. **Physical data independence** – the ability to change the physical schema without impacting the logical schema.

- This concept is a foundational principle in database design, helping ensure flexibility and stability in database systems.

### 3. A **\_\_\_\_** is an attribute or a set of attributes that uniquely identifies a record in a relation.

- A **primary key** is an attribute or a set of attributes that uniquely identifies a record in a relation.

- In a database table (or relation), the primary key ensures that each record (row) can be uniquely identified. This means that no two rows in the table can have the same value for the primary key, and the primary key cannot contain NULL values. Primary keys are essential for maintaining entity integrity within a relational database.

### 4. A **\_\_\_\_** constraint ensures that no two rows in a table have the same values for the set of specified attributes.

- A **unique constraint** ensures that no two rows in a table have the same values for the set of specified attributes.

- This constraint enforces uniqueness for the specified columns, allowing duplicate values only if at least one value in the specified set is different. Unlike a primary key constraint, a unique constraint allows NULL values, but each non-NULL combination of values must still be unique. Unique constraints are commonly used to enforce data integrity by preventing duplicate entries in columns where unique values are required (e.g., email addresses or usernames).

### 5. What is the formula to find the block address in the Disk **\_\_\_\_**?

- `Block address = Sector Address + Track Address`

- The formula to find the **block address** in a disk typically depends on the **cylinder**, **head**, and **sector** values, which are the components of the CHS (Cylinder-Head-Sector) addressing system. A common formula to compute the block address in CHS format is as follows:

  `Block Address = (Cylinder × Heads per Cylinder + Head) × Sectors per Track + (Sector − 1)`

  Where:

  - **Cylinder** is the cylinder number.
  - **Head** is the head number within that cylinder (also referred to as the platter or surface).
  - **Sector** is the specific sector number within the track (sector values typically start from 1).
  - **Heads per Cylinder** refers to the number of heads (or surfaces) per cylinder.
  - **Sectors per Track** is the number of sectors in each track.

  This formula is used to compute the linear address (block number) for a sector on a disk when given its CHS location. In modern systems, however, logical block addressing (LBA) is more commonly used, which assigns a unique linear address to each block on the disk, bypassing the need for CHS details.

### 6. A **\_\_\_\_** is a collection of related data organized in a way that allows easy access, retrieval, and management.

- A **database** is a collection of related data organized in a way that allows easy access, retrieval, and management.
  Databases are designed to store information systematically, enabling users and applications to efficiently interact with the data. They can be managed through Database Management Systems (DBMS), which provide tools for data storage, querying, updating, and administration.

### 7. **\_\_\_\_** is a concurrency control mechanism used to ensure that multiple transactions can be executed safely in parallel.

- **Locking** is a concurrency control mechanism used to ensure that multiple transactions can be executed safely in parallel.

- Locking prevents conflicts by controlling access to data, allowing only one transaction to access specific data at a time or defining specific conditions for shared access. There are different types of locks, such as:

  - **Shared locks** (read locks): Allow multiple transactions to read a data item but not modify it.
  - **Exclusive locks** (write locks): Prevent any other transaction from accessing the data until the lock is released.

  Other concurrency control mechanisms include **timestamp ordering**, **multiversion concurrency control (MVCC)**, and **optimistic concurrency control**. These mechanisms ensure database consistency, isolation, and durability in a multi-transaction environment, preventing issues like lost updates, dirty reads, and uncommitted data visibility.

### 8. **\_\_\_\_** is a sequence of operations performed as a single logical unit of work in a database management system.

- A **transaction** is a sequence of operations performed as a single logical unit of work in a database management system.

- In database management, a transaction is treated as an atomic process, meaning it either fully completes or fully fails—there is no partial completion. Transactions must satisfy the ACID properties (Atomicity, Consistency, Isolation, and Durability) to ensure data integrity. This means:

  - **Atomicity**: All operations within a transaction are completed; if any operation fails, the entire transaction is rolled back.
  - **Consistency**: The database remains in a valid state before and after the transaction.
  - **Isolation**: Transactions do not interfere with each other, even when running concurrently.
  - **Durability**: Once a transaction is committed, its changes are permanently recorded in the database.

  Transactions are fundamental to ensuring reliable and predictable database behavior in multi-user and distributed environments.

### 9. The relationship between two tables where each record in the first table can relate to many records in the second table, but each record in the second table relates to only one record in the first table is called a **\_\_\_\_** relationship.

- The relationship between two tables where each record in the first table can relate to many records in the second table, but each record in the second table relates to only one record in the first table is called a **one-to-many** relationship.

- In a **one-to-many** relationship, the primary key from the first table (the "one" side) is typically referenced as a foreign key in the second table (the "many" side). This relationship is common in databases and is used to model scenarios where a single entity (such as a customer) can be associated with multiple related entities (such as orders), but each order belongs to only one customer.

### 10. In a database system, enforcing **\_\_\_\_** ensures that no conflicting operations are performed on shared data concurrently.

- In a database system, enforcing **concurrency control** ensures that no conflicting operations are performed on shared data concurrently.

- Concurrency control mechanisms manage the simultaneous execution of transactions in a way that preserves data consistency and isolation. Techniques such as locking, timestamp ordering, and multiversion concurrency control (MVCC) are used to prevent conflicts like lost updates, dirty reads, and other anomalies. This is essential for maintaining the ACID properties in databases, especially in multi-user environments where multiple transactions may access or modify the same data simultaneously.
