# Important Topics

---

### **1. Data Models and Schema**

#### **Data Models:**

- **Definition:** A data model is a conceptual representation of data structures, relationships, and constraints in a database.
- **Types of Data Models:**
  1. **Hierarchical Data Model:**
     - Data is organized in a tree-like structure.
     - Example: Employee reporting structure.
  2. **Network Data Model:**
     - Data is represented as a graph, with records as nodes and relationships as edges.
     - Example: Many-to-many relationships.
  3. **Relational Data Model:**
     - Data is stored in tables (relations) with rows and columns.
     - Example: SQL databases.
  4. **Entity-Relationship Model (ER Model):**
     - Data is represented through entities (objects) and relationships.
     - Example: ER diagrams.
  5. **Object-Oriented Data Model:**
     - Combines object-oriented programming principles with databases.
     - Example: Classes and objects.

#### **Schema:**

- **Definition:** The structure or blueprint of a database that defines how data is organized.
- **Types:**
  1. **Physical Schema:** Describes the physical storage of data.
  2. **Logical Schema:** Represents the logical structure, such as tables, views, and constraints.
  3. **External Schema:** Defines user-specific views of the data.

---

### **2. Types of Attributes**

Attributes represent the properties of an entity in a database.

1. **Simple Attributes:** Cannot be divided further.
   - Example: Name, Age.
2. **Composite Attributes:** Can be broken into sub-parts.
   - Example: Address (Street, City, ZIP).
3. **Single-Valued Attributes:** Hold a single value for each entity.
   - Example: Date of Birth.
4. **Multi-Valued Attributes:** Hold multiple values for an entity.
   - Example: Phone Numbers.
5. **Derived Attributes:** Computed from other attributes.
   - Example: Age (calculated from Date of Birth).
6. **Key Attributes:** Uniquely identify an entity.
   - Example: Employee ID.

---

### **3. Integrity Constraints**

Rules to ensure data accuracy and consistency in a database.

1. **Domain Constraints:** Restrict the values an attribute can hold.
   - Example: Age must be between 0 and 150.
2. **Entity Integrity:** Ensures no primary key is NULL.
3. **Referential Integrity:** Ensures foreign keys match primary keys in referenced tables.
4. **Key Constraints:** Enforces uniqueness for primary keys.

---

### **4. Data Independence**

**Definition:** The ability to change the schema at one level without affecting the schema at another level.

1. **Physical Data Independence:**
   - Changing the physical storage does not affect the logical schema.
   - Example: Moving data to a new disk.
2. **Logical Data Independence:**
   - Changing the logical schema does not affect external schemas.
   - Example: Adding a new table.

---

### **5. Cardinality Ratios**

Describes the number of instances of one entity related to the number of instances of another entity.

1. **One-to-One (1:1):** One entity is associated with exactly one other entity.
   - Example: Each person has one passport.
2. **One-to-Many (1:N):** One entity is associated with many others.
   - Example: A manager supervises many employees.
3. **Many-to-Many (M:N):** Many entities are associated with many others.
   - Example: Students enroll in many courses.

---

### **6. Degree of Relations**

**Definition:** The number of attributes (columns) in a relation.

1. **Unary Relation:** A single attribute.
   - Example: Self-relationship in an ER diagram.
2. **Binary Relation:** Two attributes.
   - Example: Customer-Account relationship.
3. **Ternary Relation:** Three attributes.
   - Example: Vendor supplying products to customers.

---

### **7. Anomalies**

Issues in a database that lead to redundancy and inconsistency.

1. **Insertion Anomaly:** Difficulty adding data without all fields.
   - Example: Adding a new student without enrolling in a course.
2. **Deletion Anomaly:** Unintended data loss.
   - Example: Deleting a course removes all associated student data.
3. **Update Anomaly:** Inconsistency when updating data.
   - Example: Updating a teacher's name in multiple rows.

---

### **8. Transactions and Its Types**

#### **Transaction:**

A unit of work that is either completely executed or fully rolled back.

#### **Types:**

1. **Read-Only Transactions:** Retrieve data without modifying it.
2. **Read-Write Transactions:** Both retrieve and modify data.
3. **Distributed Transactions:** Span multiple databases.

---

### **9. Locks and Recovery Concepts**

#### **Locks:**

Mechanisms to ensure data consistency by controlling concurrent access.

1. **Types of Locks:**
   - **Shared Lock (S):** Allows multiple reads.
   - **Exclusive Lock (X):** Restricts access to one transaction.
   - **Intent Locks:** to acquire a shared or exclusive lock at a finer granularity level (e.g., a specific row within a table).
   - **Binary Lock:** Simplest form of lock where a resource is either locked or unlocked.
   - **Deadlock Avoidance Locks:** advanced locking strategies to prevent deadlocks.
     - **Deadlock:** Two transactions wait indefinitely for each other's locks.

#### **Recovery Concepts:**

Ensures the database returns to a consistent state after failure.

1. **Types:**
   - **Undo (Rollback):** Reverse uncommitted changes.
   - **Redo:** Reapply committed changes.
   - **Checkpoints:** Savepoints for faster recovery.

---

### **10. Functional Dependencies**

**Definition:** A relationship where one attribute uniquely determines another.

#### Example:

If \( A \rightarrow B \), then \( B \) is functionally dependent on \( A \).

#### Types:

1. **Full Dependency:** All attributes of a key determine a dependent attribute.
2. **Partial Dependency:** A subset of a key determines a dependent attribute.
3. **Transitive Dependency:** Indirect functional dependency.

---

### **11. SQL Operations - DDL and DML**

1. **DDL (Data Definition Language):**

   - Used to define and modify database schema.
   - **Commands:**
     - `CREATE TABLE`
     - `ALTER TABLE`
     - `DROP TABLE`
   - Example:
     ```sql
     CREATE TABLE employees (id INT, name VARCHAR(50));
     ```

2. **DML (Data Manipulation Language):**
   - Used to manipulate data in the database.
   - **Commands:**
     - `INSERT`
     - `UPDATE`
     - `DELETE`
     - `SELECT`
   - Example:
     ```sql
     INSERT INTO employees (id, name) VALUES (1, 'Alice');
     ```

---

### **12. 3-Tier Schema Architecture**

Describes the three levels of abstraction in a database:

1. **External Level:** User views.
2. **Conceptual Level:** Logical design.
3. **Internal Level:** Physical storage.

---

### **13. Relational Algebra**

A procedural query language for relational databases.

#### **Operations:**

1. **Select (σ):** Filters rows.
   - Example: \( \sigma\_{age > 30}(Employees) \)
2. **Project (π):** Selects columns.
   - Example: \( \pi\_{name, salary}(Employees) \)
3. **Union (∪):** Combines tuples from two relations.
4. **Intersection (∩):** Finds common tuples.
5. **Difference (-):** Finds tuples in one relation but not another.
6. **Cartesian Product (×):** Combines all tuples.
7. **Join (⋈):** Combines tuples based on conditions.

---

This breakdown provides a detailed overview of each topic. Let me know if you'd like further examples or clarification!
