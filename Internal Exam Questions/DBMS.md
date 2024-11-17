## CA2

### I. Answer All the questions. 10X2=20Marks

1. **What is data independence?**\
   Data independence is a property of database systems that allows for changes to the database schema without affecting the application programs that access the data. It's a crucial aspect of database management systems (DBMS) and is divided into two types:
   1. **Logical Data Independence**: This allows changes to the logical schema, like adding or removing tables or fields, without affecting the external schema or application programs. For example, adding a new attribute to a table should not require changing the application programs that use that table.
   2. **Physical Data Independence**: This allows changes to the physical schema, such as altering how data is stored (e.g., changing from a heap file to a B-tree index), without affecting the logical schema or application programs. It ensures that applications do not need to be rewritten to accommodate changes in the storage structure.
      Data independence is achieved through abstraction and encapsulation in a DBMS, which separates the data structure at different levels of abstraction. This separation provides flexibility and efficiency in managing and evolving the database over time.
2. **What is database schema?**\
   A database schema is the structure that defines the organization of data within a database. Think of it as the blueprint for how data is arranged, stored, and accessed. It includes all the tables, columns, relationships, views, indexes, and other elements that make up the database.

   Here are the key components of a database schema:

   1. **Tables**: These are the primary units where data is stored. Each table consists of rows (records) and columns (fields).
   2. **Columns**: These define the attributes or fields of the table, specifying the type of data that can be stored in each column (e.g., integer, text, date).
   3. **Relationships**: These define how tables are related to one another, often through primary and foreign keys.
   4. **Views**: These are virtual tables created by querying data from one or more tables.
   5. **Indexes**: These are used to speed up the retrieval of data by providing quick access paths to rows in a table.
   6. **Constraints**: These rules enforce data integrity and consistency, such as primary key, foreign key, unique, and check constraints.

   In essence, the database schema is like the skeleton that holds the database together, ensuring data is organized efficiently and can be accessed in meaningful ways.

3. **What is functional dependency and state an example for trivial dependency?**\
   Functional dependency is a concept in relational databases that describes the relationship between two attributes (or sets of attributes) within a table. Specifically, a functional dependency indicates that the value of one attribute (or a combination of attributes) determines the value of another attribute.

   #### Key Concepts

   - **Determinant**: The attribute (or set of attributes) on the left side of the functional dependency.
   - **Dependent**: The attribute on the right side of the functional dependency.

   The notation for functional dependency is usually represented as \( A &rarr; B \), where attribute A (the determinant) functionally determines attribute B (the dependent).

   #### Example

   Consider a table of student records:

   - **StudentID**: A unique identifier for each student.
   - **StudentName**: The name of the student.
   - **DOB**: The date of birth of the student.

   In this table, the StudentID uniquely determines the StudentName and DOB. This can be represented as:
   **\[ StudentID &rarr; StudentName, DOB \]**

   #### Trivial Functional Dependency

   A trivial functional dependency occurs when the dependent is a subset of the determinant. This means that the dependency doesn't provide any new information and is always true by definition.

   #### Example of Trivial Dependency

   In a table with attributes \( A \) and \( B \), the following is a trivial dependency:
   \[ A, B &rarr; A \]
   This is trivial because A is a subset of \( A, B \), and knowing \( A, B \) obviously includes knowing \( A \).

   Functional dependencies, especially non-trivial ones, play a crucial role in database normalization, ensuring data integrity and eliminating redundancy.

4. **Define ACID properties**\
   The ACID properties are a set of principles that ensure reliable processing of database transactions. They stand for:

   1. **Atomicity**: This ensures that a transaction is treated as a single, indivisible unit of work. Either all the operations within the transaction are completed successfully, or none of them are. This guarantees that the database remains in a consistent state even in the event of a system failure. For example, if a transaction involves transferring money from one bank account to another, both the debit and credit operations must succeed or fail together.

   2. **Consistency**: This property ensures that a transaction takes the database from one valid state to another, maintaining all predefined rules and constraints. After a transaction is completed, the database must be in a consistent state. For instance, if a database constraint requires that an account balance cannot be negative, a transaction that violates this rule will not be allowed to complete.

   3. **Isolation**: Isolation ensures that the operations of one transaction are not visible to other transactions until the transaction is completed. This means that the concurrent execution of transactions leads to the same state as if the transactions were executed sequentially.

   4. **Durability**: Durability guarantees that once a transaction is committed, its changes are permanent and will not be lost, even in the event of a system crash. This means that the database will retain the transaction's effects permanently. For example, after a successful money transfer transaction, the updated balances will remain even if the database crashes immediately after.

   Together, these properties ensure that transactions are processed reliably and that the integrity of the database is maintained. They are fundamental to the operation of modern database management systems.

5. **What is an Anomaly and list its types?**\
   In the context of a Database Management System (DBMS), an anomaly refers to an inconsistency or error that can occur when data is inserted, updated, or deleted in a database. These anomalies arise due to redundant data and can compromise data integrity.

   #### Types of Anomalies

   1. **Insertion Anomaly**:

   - This occurs when certain attributes cannot be inserted into the database without the presence of other attributes. For example, if you have a table where both `EmployeeID` and `Department` fields must be filled, you can't add a new employee without assigning them to a department. This can be problematic if the employee's department has not been decided yet.

   1. **Update Anomaly**:

   - This happens when the same piece of data exists in multiple places and only some of these instances are updated. This leads to inconsistency in the database. For example, if an employee's address is stored in multiple tables and you update the address in one table but not in the others, the database will have conflicting information.

   1. **Deletion Anomaly**:

   - This occurs when the deletion of data results in the unintended loss of additional data. For instance, if you delete a record of an employee who is also a supervisor, you might also lose important information about the department that the supervisor was managing.

   #### Example

   Consider a simple table storing student enrollments in courses:

   | StudentID | StudentName | CourseID | CourseName |
   | --------- | ----------- | -------- | ---------- |
   | 1         | Alice       | C101     | Math       |
   | 2         | Bob         | C101     | Math       |
   | 3         | Charlie     | C102     | Physics    |

   - **Insertion Anomaly**: If you want to add a new course but no students are currently enrolled, you can't insert a course without a `StudentID` and `StudentName`.
   - **Update Anomaly**: If the course name "Math" changes to "Advanced Math" in one row but not the others, it creates inconsistency.
   - **Deletion Anomaly**: If Charlie is the only student enrolled in Physics and you delete his record, you also lose the information about the course Physics itself.

   Normalization techniques are applied in database design to reduce or eliminate these anomalies by organizing the data into related tables.

6. **What is Attribute Closure?**\
   Attribute closure is a concept used in the context of relational database theory, particularly in functional dependency and normalization processes. It helps in determining all the attributes that can be functionally determined by a given set of attributes. In other words, the attribute closure of a set of attributes \( X \), denoted as \( X<sup>+</sup> \), is the set of all attributes that can be functionally determined by \( X \) under a given set of functional dependencies.

   #### Steps to Find Attribute Closure

   1. **Start with the given set of attributes**: Initialize the closure with the attributes in the set \( X \).
   2. **Apply functional dependencies**: For each functional dependency \( A &rarr; B \), if \( A \) is a subset of the closure, then add \( B \) to the closure.
   3. **Repeat until no new attributes can be added**: Continue applying the functional dependencies until no more attributes can be added to the closure.

   #### Example

   Consider a relation with attributes \( A, B, C, D \) and the following functional dependencies:

   4. \( A &rarr; B \)
   5. \( B &rarr; C \)
   6. \( C &rarr; D \)

   To find the attribute closure of \( A \), \( A<sup>+</sup> \):

   7. Start with \( A \): \( A<sup>+</sup> = \{A\} \)
   8. Apply \( A &rarr; B \): \( A<sup>+</sup> = \{A, B\} \)
   9. Apply \( B &rarr; C \): \( A<sup>+</sup> = \{A, B, C\} \)
   10. Apply \( C &rarr; D \): \( A<sup>+</sup> = \{A, B, C, D\} \)

   So, the attribute closure of \( A \) is \( \{A, B, C, D\} \).

   Attribute closure is an essential tool in database design, as it helps in determining the keys of a relation and in the process of normalization. It ensures that the database design is efficient and free of redundancies.

7. **What is Transaction Processing System?**\
   A Transaction Processing System (TPS) in the context of a Database Management System (DBMS) is designed to manage and support the execution of transactions in an efficient, reliable, and secure manner. These systems handle a large volume of routine transactions and are critical for the daily operations of businesses.

   #### Key Features of TPS in DBMS:

   1. **Transaction Management**: Ensures that all transactions adhere to the ACID properties (Atomicity, Consistency, Isolation, Durability), guaranteeing that data integrity is maintained even in the case of system failures.
   2. **Concurrency Control**: Manages simultaneous transaction execution to prevent conflicts and ensure consistency, often through mechanisms like locking, timestamps, and optimistic concurrency control.
   3. **Recovery Management**: Provides mechanisms to recover from failures, ensuring that all transactions are either fully completed and committed or fully rolled back to maintain a consistent database state.
   4. **Real-Time Processing**: Transactions are processed immediately upon arrival, providing instant feedback and updates to the database, which is crucial for applications like online banking or reservation systems.
   5. **Security and Authorization**: Ensures that only authorized users can perform specific transactions, safeguarding data against unauthorized access and modifications.

   #### Examples of TPS in DBMS:

   - **Banking Systems**: Processes transactions such as withdrawals, deposits, transfers, and loan payments.
   - **Point of Sale (POS) Systems**: Manages sales transactions, inventory updates, and customer data in retail environments.
   - **Reservation Systems**: Handles bookings and reservations for airlines, hotels, and car rentals.
   - **Payroll Systems**: Processes salary calculations, tax withholdings, and benefit distributions.

   Transaction Processing Systems ensure that transactions are processed accurately and efficiently, supporting the smooth operation of business processes. They are fundamental to maintaining the reliability and performance of database-driven applications.

8. **Define an Entity and explain prime and non-prime attributes.**\
   In the context of a database, an **entity** is an object or thing that can be distinctly identified. It represents a real-world concept or object that has a unique existence and is typically described by its properties or attributes. Entities can be anything from a person, place, event, or even a concept.

   #### Examples of Entities

   - **Person**: Employee, Customer, Student
   - **Place**: Office, Store, City
   - **Event**: Meeting, Sale, Transaction
   - **Concept**: Course, Product, Service

   #### Attributes

   Attributes are the properties or characteristics of an entity that provide more information about it. For example, an "Employee" entity might have attributes like EmployeeID, Name, Position, and Salary.

   #### Prime and Non-prime Attributes

   1. **Prime Attributes**:

   - These are the attributes that are part of a candidate key or primary key of an entity. A candidate key is a minimal set of attributes that can uniquely identify each instance of an entity. The primary key is a special candidate key chosen by the database designer to uniquely identify the entity.
   - **Example**: In an Employee entity, if `EmployeeID` is the primary key, then `EmployeeID` is a prime attribute.

   2. **Non-prime Attributes**:

   - These are the attributes that are not part of any candidate key. They provide additional information about the entity but are not used to uniquely identify it.
   - **Example**: In the same Employee entity, attributes like `Name`, `Position`, and `Salary` are non-prime attributes as they are not part of the primary key.

   #### Example Entity: Employee

   | Attribute      | Type    | Description                 |
   | -------------- | ------- | --------------------------- |
   | **EmployeeID** | Integer | Unique identifier (Prime)   |
   | Name           | String  | Employee's name (Non-prime) |
   | Position       | String  | Job title (Non-prime)       |
   | Salary         | Decimal | Monthly salary (Non-prime)  |

   Understanding the distinction between prime and non-prime attributes is crucial for database design and normalization, ensuring that the database is efficient and free from redundancy.

9. **Explain the types Transactions Locks.**\
   Transaction locks in DBMS are mechanisms used to manage concurrency by controlling how multiple transactions access the database simultaneously. They ensure consistency and isolation by preventing conflicts, such as data corruption or deadlocks. The main types of locks used in DBMS are:

   #### **1. Shared Lock (S)**

   - **Purpose**: Allows multiple transactions to read a data item simultaneously but prevents any of them from writing to it.
   - **Usage**:
     - A transaction places a shared lock on a resource (like a table or a row) when it needs to **read** the data.
     - Other transactions can also place shared locks on the same resource for reading.
   - **Example**:
     - If transaction T1 reads a record with a shared lock, T2 can also read it. However, T2 cannot write until T1 releases the shared lock.
   - **Application**: Read-only operations like `SELECT`.

   #### **2. Exclusive Lock (X)**

   - **Purpose**: Allows a transaction to both read and write a data item, but prevents all other transactions from accessing it (neither read nor write).
   - **Usage**:
     - A transaction places an exclusive lock on a resource when it intends to **modify** (write) the data.
     - No other transaction can acquire any lock (shared or exclusive) on that resource until the exclusive lock is released.
   - **Example**:
     - If transaction T1 updates a record with an exclusive lock, T2 cannot read or write that record until T1 releases the lock.
   - **Application**: Write operations like `UPDATE` or `DELETE`.

   #### **3. Intent Locks**

   - **Purpose**: Indicate the intention of a transaction to acquire a shared or exclusive lock at a finer granularity level (e.g., a specific row within a table).
   - **Types**:
     - **Intent Shared (IS)**: Indicates intent to acquire a shared lock on a lower-level resource.
     - **Intent Exclusive (IX)**: Indicates intent to acquire an exclusive lock on a lower-level resource.
     - **Shared with Intent Exclusive (SIX)**: Indicates a shared lock on a resource with the intention to acquire exclusive locks at lower levels.
   - **Usage**:
     - Intent locks are used in hierarchical locking (e.g., table → row) to prevent conflicts between transactions operating at different levels of granularity.
   - **Example**:
     - If T1 wants to read a table (shared lock) but write to some rows (exclusive locks), it places an `SIX` lock on the table.

   #### **4. Read and Write Locks**

   - **Read Lock**:
     - Equivalent to a **shared lock**.
     - Multiple transactions can read but cannot modify the data.
   - **Write Lock**:
     - Equivalent to an **exclusive lock**.
     - Only one transaction can modify the data while preventing others from accessing it.

   #### **5. Binary Locks**

   - **Purpose**: Simplest form of lock where a resource is either locked or unlocked.
   - **States**:
     - **Locked**: No other transaction can access the resource.
     - **Unlocked**: The resource is free to be accessed by any transaction.
   - **Usage**:
     - Binary locks are rarely used in modern DBMS as they lack flexibility (e.g., distinguishing between read and write operations).

   #### **6. Record-Level Locks**

   - **Purpose**: Locks individual records (rows) in a table.
   - **Usage**:
     - Ideal for fine-grained locking where transactions are expected to work on specific rows.
   - **Example**:
     - T1 locks row 1 for writing, while T2 locks row 2 for reading.

   #### **7. Table-Level Locks**

   - **Purpose**: Locks an entire table to restrict access to all its rows.
   - **Usage**:
     - Used when a transaction needs to perform operations on a large portion of the table.
   - **Example**:
     - T1 locks a table to update multiple rows, preventing T2 from reading or writing until the lock is released.

   #### **8. Deadlock Avoidance Locks**

   - Some DBMS use advanced locking strategies to prevent deadlocks, such as:
     - **Timeout-Based Locks**: A transaction is forced to wait for a set time before failing.
     - **Wait-Die or Wound-Wait Schemes**: Priority-based methods to decide which transaction should proceed in case of conflict.

   #### Importance of Locks

   Locks ensure the **isolation** and **consistency** properties of transactions, which are part of the ACID properties. By using appropriate locks, DBMS can balance **concurrency** (performance) and **conflict resolution** (data integrity).

10. **What is Starvation condition in transactions.**\
    **Starvation** is a condition in transaction management where a transaction is perpetually unable to acquire the resources it needs to proceed because of a continuous denial of access. This situation occurs due to unfair scheduling or resource allocation mechanisms, leading to the transaction being indefinitely delayed or "starved."

    #### Causes of Starvation in Transactions:

    1. **Priority-Based Scheduling**:

    - Transactions with lower priority may be indefinitely delayed if higher-priority transactions keep acquiring the needed resources.

    2. **Locks Held for Extended Periods**:

    - If a transaction holds locks on resources for too long, other waiting transactions may be unable to proceed.

    3. **Unfair Lock Granting Policies**:

    - If the system always grants locks to newer transactions, older transactions may never get a chance to execute.

    4. **Resource Contention**:

    - High demand for a limited set of resources can cause some transactions to be perpetually blocked if certain transactions are repeatedly given preference.

    5. **Deadlock Resolution Mechanisms**:

    - Certain deadlock prevention strategies, such as preempting transactions, may cause some transactions to be repeatedly rolled back or delayed, resulting in starvation.

    #### Example of Starvation:

    - Suppose multiple transactions (T1, T2, T3) are competing for a lock on a shared resource.
    - If the lock scheduling policy always favors newer transactions, T1 (the oldest transaction) may never acquire the lock, as new transactions keep arriving and being prioritized.

    #### Prevention of Starvation:

    1. **Fair Scheduling**:

    - Use **First-Come, First-Served (FCFS)** or **FIFO (First In, First Out)** policies to ensure transactions are handled in the order they arrive.

    2. **Priority Aging**:

    - Gradually increase the priority of a transaction that has been waiting for a long time. This ensures that older transactions eventually get a chance to execute.

    3. **Timeout Mechanisms**:

    - Set time limits for transactions to acquire locks. If a transaction exceeds the limit, the system can interrupt and reschedule it.

    4. **Fair Locking Protocols**:

    - Implement locking mechanisms that balance access to resources among all transactions.

    5. **Deadlock Avoidance with Fairness**:

    - Ensure that any deadlock resolution technique used does not disproportionately impact specific transactions.

    #### Importance of Addressing Starvation:

    Starvation can reduce the throughput and fairness of a transaction processing system, leading to inefficiency and dissatisfaction for users or applications dependent on the DBMS. Proper strategies are crucial for ensuring both performance and fairness in transaction processing.

### II. Answer ANY FOUR questions. 4X5=20Marks

11. Explain in detail about Relational Algebra operations with an example.
12. Explain the terms and functionalities of Specializations and Generalizations.
13. Differentiate strict two phase locking protocol and rigorous two phase locking protocol.
14. Explain about types of Locks in Transactions.
15. Explain in detail about 3-Tier Schema Architecture with neat diagram.

### III. Answer ANYONE question. 2x10=20Marks

16. Given are lation R(P, Q, R, S, T) and Functional Dependency set FD={PQ→R, S→T},\
     determine whether the given R is in 2NF? If not convert it into 2NF.\
    **(OR)**
17. (i)What are the Transaction states explain with a state diagram?\
    (ii)What are Aggregate Functions and explain each function with simple example syntax.
