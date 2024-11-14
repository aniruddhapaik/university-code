# Normalization in Database Design

Normalization is a database design process that organizes data to minimize redundancy and avoid undesirable anomalies during data operations. It involves dividing a database into multiple related tables and establishing relationships among them. There are several “normal forms,” each with specific requirements. Here’s a detailed breakdown of the most commonly used forms with examples:

### 1NF (First Normal Form)

A table is in **1NF** if:

1. All columns contain atomic (indivisible) values.
2. There are no repeating groups or arrays.
3. Each column contains values of a single type.

**Example:**
Consider a table storing a list of students and the courses they’re enrolled in:

| Student_ID | Name  | Courses          |
| ---------- | ----- | ---------------- |
| 1          | Alice | Math, Science    |
| 2          | Bob   | English, History |

This table is **not in 1NF** because the `Courses` column contains multiple values for some rows (e.g., "Math, Science"). To convert this to 1NF, we need to separate these values into individual rows:

| Student_ID | Name  | Course  |
| ---------- | ----- | ------- |
| 1          | Alice | Math    |
| 1          | Alice | Science |
| 2          | Bob   | English |
| 2          | Bob   | History |

Now, each column contains atomic values, and there are no repeating groups, so the table is in **1NF**.

### 2NF (Second Normal Form)

A table is in **2NF** if:

1. It is in 1NF.
2. All non-key attributes are fully functionally dependent on the entire primary key (i.e., there is no partial dependency).

Partial dependency means a non-key attribute depends only on part of a composite primary key, not the whole.

**Example:**
Consider a table that records students, courses, and the instructor for each course:

| Student_ID | Course  | Instructor |
| ---------- | ------- | ---------- |
| 1          | Math    | Mr. Brown  |
| 1          | Science | Ms. Smith  |
| 2          | English | Ms. Davis  |
| 2          | History | Mr. White  |

The primary key is a composite of `Student_ID` and `Course`, as each student may enroll in multiple courses. Here, `Instructor` depends only on the `Course`, not the `Student_ID`. This violates **2NF** because `Instructor` is partially dependent on the composite primary key.

To bring this table into **2NF**, we separate `Instructor` into a different table:

1. **Student-Course Table:**

   | Student_ID | Course  |
   | ---------- | ------- |
   | 1          | Math    |
   | 1          | Science |
   | 2          | English |
   | 2          | History |

2. **Course-Instructor Table:**

   | Course  | Instructor |
   | ------- | ---------- |
   | Math    | Mr. Brown  |
   | Science | Ms. Smith  |
   | English | Ms. Davis  |
   | History | Mr. White  |

Now, both tables satisfy **2NF** because all non-key attributes fully depend on the primary key.

### 3NF (Third Normal Form)

A table is in **3NF** if:

1. It is in 2NF.
2. There are no transitive dependencies, meaning non-key attributes are only dependent on the primary key, not on other non-key attributes.

**Example:**
Consider a table where student information includes the `Department` and `Department_Location`:

| Student_ID | Name  | Department | Department_Location |
| ---------- | ----- | ---------- | ------------------- |
| 1          | Alice | Math       | Building A          |
| 2          | Bob   | Science    | Building B          |

Here, `Department_Location` is transitively dependent on `Department` (a non-key attribute) rather than directly on `Student_ID`. This violates **3NF**.

To bring this table into **3NF**, we separate the department information:

1. **Student Table:**

   | Student_ID | Name  | Department |
   | ---------- | ----- | ---------- |
   | 1          | Alice | Math       |
   | 2          | Bob   | Science    |

2. **Department Table:**

   | Department | Department_Location |
   | ---------- | ------------------- |
   | Math       | Building A          |
   | Science    | Building B          |

Now, the `Department_Location` attribute depends only on the primary key of the `Department` table, ensuring the database is in **3NF**.

### BCNF (Boyce-Codd Normal Form)

A table is in **BCNF** if:

1. It is in 3NF.
2. For every dependency \( X \rightarrow Y \), \( X \) should be a super key (i.e., no partial dependencies even in unique keys).

**Example:**
Consider a university table where a professor can teach multiple courses, but each course is taught by only one professor:

| Professor | Course  | Department |
| --------- | ------- | ---------- |
| Dr. Smith | Math    | Science    |
| Dr. Brown | History | Arts       |

The primary key here is a composite of `Professor` and `Course`. However, `Department` depends only on `Professor`, not on the full key. To satisfy **BCNF**, we separate `Department` information as follows:

1. **Professor-Course Table:**

   | Professor | Course  |
   | --------- | ------- |
   | Dr. Smith | Math    |
   | Dr. Brown | History |

2. **Professor-Department Table:**

   | Professor | Department |
   | --------- | ---------- |
   | Dr. Smith | Science    |
   | Dr. Brown | Arts       |

Now, the tables satisfy **BCNF** because each dependency involves a super key.

### 4NF (Fourth Normal Form)

A table is in **4NF** if:

1. It is in BCNF.
2. It has no multi-valued dependencies, which means there are no non-trivial dependencies where a single attribute can have multiple independent values for another single attribute.

**Example:**
Suppose a student can have multiple phone numbers and enroll in multiple courses:

| Student_ID | Phone_Number | Course  |
| ---------- | ------------ | ------- |
| 1          | 555-1234     | Math    |
| 1          | 555-5678     | Science |
| 2          | 555-8765     | English |
| 2          | 555-4321     | History |

Here, `Phone_Number` and `Course` are independent multi-valued facts about `Student_ID`, which violates **4NF**. To bring this table into **4NF**, split it into two separate tables:

1. **Student-Phone Table:**

   | Student_ID | Phone_Number |
   | ---------- | ------------ |
   | 1          | 555-1234     |
   | 1          | 555-5678     |
   | 2          | 555-8765     |
   | 2          | 555-4321     |

2. **Student-Course Table:**

   | Student_ID | Course  |
   | ---------- | ------- |
   | 1          | Math    |
   | 1          | Science |
   | 2          | English |
   | 2          | History |

Each table now contains only one fact about the `Student_ID`, satisfying **4NF**.

### 5NF (Fifth Normal Form)

A table is in **5NF** if:

1. It is in 4NF.
2. It has no join dependencies, meaning the table cannot be decomposed further without losing information.

**Example:**
Suppose a project involves multiple consultants, each consultant has multiple skills, and each project requires specific skills:

| Project   | Consultant | Skill  |
| --------- | ---------- | ------ |
| Project A | Alice      | Java   |
| Project A | Alice      | SQL    |
| Project A | Bob        | Java   |
| Project B | Alice      | Python |
| Project B | Bob        | SQL    |

Here, the relationships are interdependent among three entities (`Project`, `Consultant`, and `Skill`). To satisfy **5NF**, separate them into three tables where each pairwise relationship is stored:

1. **Project-Consultant Table:**

   | Project   | Consultant |
   | --------- | ---------- |
   | Project A | Alice      |
   | Project A | Bob        |
   | Project B | Alice      |
   | Project B | Bob        |

2. **Consultant-Skill Table:**

   | Consultant | Skill  |
   | ---------- | ------ |
   | Alice      | Java   |
   | Alice      | SQL    |
   | Alice      | Python |
   | Bob        | Java   |
   | Bob        | SQL    |

3. **Project-Skill Table:**

   | Project   | Skill  |
   | --------- | ------ |
   | Project A | Java   |
   | Project A | SQL    |
   | Project B | Python |
   | Project B | SQL    |

These tables in **5NF** preserve all information without redundancy or loss.
