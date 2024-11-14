# Relational Algebra - Operations

Relational Algebra is a procedural query language for relational databases, and its operations enable users to retrieve and manipulate data in a structured way. Here are the fundamental operations in relational algebra, explained in detail with examples.

---

### 1. **Select Operation (σ)**

The **Select** operation (σ) is used to select rows (tuples) that satisfy a specific condition. It’s a unary operation because it operates on a single relation (table).

**Syntax:**  
\[
\sigma\_{\text{condition}}(\text{Relation})
\]

**Example:**
Suppose we have a **Student** table:

| Student_ID | Name  | Age | Major   |
| ---------- | ----- | --- | ------- |
| 1          | Alice | 20  | Math    |
| 2          | Bob   | 21  | Science |
| 3          | Carol | 22  | History |
| 4          | Dave  | 23  | Science |

To select all students majoring in "Science", we use:
\[
\sigma\_{\text{Major} = \text{"Science"}}(\text{Student})
\]

**Result:**

| Student_ID | Name | Age | Major   |
| ---------- | ---- | --- | ------- |
| 2          | Bob  | 21  | Science |
| 4          | Dave | 23  | Science |

---

### 2. **Project Operation (π)**

The **Project** operation (π) is used to select specific columns (attributes) from a relation. It’s also a unary operation. Unlike **Select**, which filters rows, **Project** filters columns.

**Syntax:**  
\[
\pi\_{\text{column(s)}}(\text{Relation})
\]

**Example:**
Using the **Student** table from above, if we want to get a list of student names and their majors, we use:
\[
\pi\_{\text{Name, Major}}(\text{Student})
\]

**Result:**

| Name  | Major   |
| ----- | ------- |
| Alice | Math    |
| Bob   | Science |
| Carol | History |
| Dave  | Science |

---

### 3. **Union Operation (∪)**

The **Union** operation (∪) combines the tuples from two relations into a single relation, removing any duplicates. For **Union** to work, both relations must have the same set of attributes.

**Syntax:**  
\[
\text{Relation1} \cup \text{Relation2}
\]

**Example:**
Suppose we have two tables, **Science_Students** and **Math_Students**, with students studying in different majors:

**Science_Students:**

| Student_ID | Name |
| ---------- | ---- |
| 2          | Bob  |
| 4          | Dave |

**Math_Students:**

| Student_ID | Name  |
| ---------- | ----- |
| 1          | Alice |
| 5          | Emily |

To get a combined list of students in both majors, we use:
\[
\text{Science_Students} \cup \text{Math_Students}
\]

**Result:**

| Student_ID | Name  |
| ---------- | ----- |
| 2          | Bob   |
| 4          | Dave  |
| 1          | Alice |
| 5          | Emily |

---

### 4. **Set Difference (−)**

The **Set Difference** operation (−) returns the tuples that are present in one relation but not in another. Both relations must have the same set of attributes.

**Syntax:**  
\[
\text{Relation1} - \text{Relation2}
\]

**Example:**
Using the **Science_Students** and **Math_Students** tables from above, if we want to find students in **Math_Students** who are _not_ in **Science_Students**, we use:
\[
\text{Math_Students} - \text{Science_Students}
\]

**Result:**

| Student_ID | Name  |
| ---------- | ----- |
| 1          | Alice |
| 5          | Emily |

---

### 5. **Cartesian Product (×)**

The **Cartesian Product** operation (×) combines every tuple in one relation with every tuple in another, producing a relation with every possible combination of tuples. This is useful as an intermediate step in join operations.

**Syntax:**  
\[
\text{Relation1} \times \text{Relation2}
\]

**Example:**
Suppose we have two tables, **Courses** and **Professors**:

**Courses:**

| Course_ID | Course_Name |
| --------- | ----------- |
| 101       | Math        |
| 102       | Science     |

**Professors:**

| Prof_ID | Prof_Name |
| ------- | --------- |
| 1       | Dr. Smith |
| 2       | Dr. Brown |

To get all possible combinations of courses and professors, we use:
\[
\text{Courses} \times \text{Professors}
\]

**Result:**

| Course_ID | Course_Name | Prof_ID | Prof_Name |
| --------- | ----------- | ------- | --------- |
| 101       | Math        | 1       | Dr. Smith |
| 101       | Math        | 2       | Dr. Brown |
| 102       | Science     | 1       | Dr. Smith |
| 102       | Science     | 2       | Dr. Brown |

---

### 6. **Rename Operation (ρ)**

The **Rename** operation (ρ) is used to rename the attributes of a relation or even the relation itself. This is useful in cases where you need to distinguish between different instances of the same relation in queries or when you need to provide more descriptive names.

**Syntax:**  
\[
\rho\_{\text{NewRelationName(OldAttribute1 \rightarrow NewAttribute1, OldAttribute2 \rightarrow NewAttribute2, ...)}}(\text{Relation})
\]

**Example:**
Using the **Courses** table, suppose we want to rename `Course_ID` to `ID` and `Course_Name` to `Name`, and give the table the name **Subject**:

**Original Courses Table:**

| Course_ID | Course_Name |
| --------- | ----------- |
| 101       | Math        |
| 102       | Science     |

To rename, we use:
\[
\rho\_{\text{Subject(Course_ID \rightarrow ID, Course_Name \rightarrow Name)}}(\text{Courses})
\]

**Result:**

| ID  | Name    |
| --- | ------- |
| 101 | Math    |
| 102 | Science |

---

### Summary Table of Relational Algebra Operations

| Operation             | Symbol | Description                                                                    |
| --------------------- | ------ | ------------------------------------------------------------------------------ |
| **Select**            | σ      | Filters rows based on a condition                                              |
| **Project**           | π      | Selects specific columns from a relation                                       |
| **Union**             | ∪      | Combines rows from two relations, removing duplicates                          |
| **Set Difference**    | −      | Returns rows present in one relation but not in the other                      |
| **Cartesian Product** | ×      | Combines each row of one relation with every row of another                    |
| **Rename**            | ρ      | Renames attributes or relations in a query for clarity or to prevent ambiguity |

Each of these operations forms the building blocks of more complex queries and is crucial for managing and querying relational databases.
