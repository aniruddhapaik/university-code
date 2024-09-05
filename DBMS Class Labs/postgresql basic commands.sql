\l -- list of databases
\d -- list of tables
\dt -- list of tables

create database University;

alter database University owner to aniruddha;

\c University -- \connect to database University

create table student (
    sid SERIAL PRIMARY KEY NOT NULL,
    name VARCHAR(30) NOT NULL,
    state VARCHAR(20)
);
-- or
create table student (
    sid INT GENERATED ALWAYS AS IDENTITY PRIMARY KEY NOT NULL,
    name VARCHAR(30) NOT NULL,
    state VARCHAR(20)
);

ALTER TABLE student
ADD COLUMN sid SERIAL PRIMARY KEY;

alter table student drop constraint student_pkey;

drop table student;

-- creating new set of tables based on ER diagram
-- creating in a particular order since most tables have dependencies
-- Tables that are referenced as foreign keys must be created before the tables that reference them.
CREATE TABLE Department (
    department_id SERIAL PRIMARY KEY,
    department_name VARCHAR(100) UNIQUE,
    location VARCHAR(100),
    phone_number VARCHAR(15),
    head_of_department INT
    -- FOREIGN KEY (head_of_department) REFERENCES Teacher(teacher_id) 
    -- Commented to avoid circular dependency, add after Teacher creation
);

CREATE TABLE Classroom (
    classroom_id SERIAL PRIMARY KEY,
    building_name VARCHAR(100),
    room_number VARCHAR(10),
    capacity INT
);

CREATE TABLE Degree (
    degree_id SERIAL PRIMARY KEY,
    degree_name VARCHAR(100),
    degree_level VARCHAR(50),
    department_id INT REFERENCES Department(department_id),
    required_credits INT
);

CREATE TABLE Library (
    library_id SERIAL PRIMARY KEY,
    title VARCHAR(255),
    author VARCHAR(100),
    isbn VARCHAR(20) UNIQUE,
    publication_year INT,
    copies_available INT,
    location VARCHAR(50)
);

CREATE TABLE Teacher (
    teacher_id SERIAL PRIMARY KEY,
    first_name VARCHAR(50),
    last_name VARCHAR(50),
    date_of_birth DATE,
    gender CHAR(1),
    email VARCHAR(100) UNIQUE,
    phone_number VARCHAR(15),
    address VARCHAR(255),
    hire_date DATE,
    department_id INT REFERENCES Department(department_id),
    salary NUMERIC(10, 2)
);

-- Add Foreign Key for head_of_department in Department Table (After Teacher Table Creation)
ALTER TABLE Department
ADD CONSTRAINT head_of_department_fkey
FOREIGN KEY (head_of_department) REFERENCES Teacher(teacher_id);

CREATE TABLE Student (
    student_id SERIAL PRIMARY KEY,
    first_name VARCHAR(50),
    last_name VARCHAR(50),
    date_of_birth DATE,
    gender CHAR(1),
    email VARCHAR(100) UNIQUE,
    phone_number VARCHAR(15),
    address VARCHAR(255),
    enrollment_date DATE,
    department_id INT REFERENCES Department(department_id)
);

CREATE TABLE Course (
    course_id SERIAL PRIMARY KEY,
    course_name VARCHAR(100),
    course_description TEXT,
    credits INT,
    department_id INT REFERENCES Department(department_id)
);

CREATE TABLE Student_Degree (
    student_degree_id SERIAL PRIMARY KEY,
    student_id INT REFERENCES Student(student_id),
    degree_id INT REFERENCES Degree(degree_id),
    start_date DATE,
    expected_graduation_date DATE
);

CREATE TABLE Enrollment (
    enrollment_id SERIAL PRIMARY KEY,
    student_id INT REFERENCES Student(student_id),
    course_id INT REFERENCES Course(course_id),
    enrollment_date DATE,
    grade CHAR(2)
);

CREATE TABLE Course_Schedule (
    schedule_id SERIAL PRIMARY KEY,
    course_id INT REFERENCES Course(course_id),
    teacher_id INT REFERENCES Teacher(teacher_id),
    classroom_id INT REFERENCES Classroom(classroom_id),
    day_of_week VARCHAR(10),
    start_time TIME,
    end_time TIME,
    semester VARCHAR(20)
);

CREATE TABLE Attendance (
    attendance_id SERIAL PRIMARY KEY,
    student_id INT REFERENCES Student(student_id),
    course_id INT REFERENCES Course(course_id),
    date_of_attendance DATE,
    status VARCHAR(10)
);

CREATE TABLE Library_Borrowing (
    borrowing_id SERIAL PRIMARY KEY,
    student_id INT REFERENCES Student(student_id),
    library_id INT REFERENCES Library(library_id),
    borrow_date DATE,
    return_date DATE,
    status VARCHAR(10)
);

CREATE TABLE Exam (
    exam_id SERIAL PRIMARY KEY,
    course_id INT REFERENCES Course(course_id),
    exam_date DATE,
    exam_type VARCHAR(20),
    location VARCHAR(100)
);
-- Done with DDL commands - creation and altering of tables

-- Now onto inserting test values into the tables, using DML commands
-- For inserting data, it's crucial to follow the order 
--   that respects the foreign key dependencies to avoid constraint violations.

INSERT INTO Classroom (building_name, room_number, capacity) VALUES
    ('Science Hall', '101', 30),
    ('Engineering Building', '201', 50),
    ('Arts Center', '301', 25),
    ('Business School', '401', 40),
    ('Library Annex', '501', 20);

INSERT INTO Library (title, author, isbn, publication_year, copies_available, location) VALUES
    ('Introduction to Algorithms', 'Thomas H. Cormen', '9780262033848', 2009, 3, 'A1'),
    ('Database Systems', 'Elmasri & Navathe', '9780132145375', 2010, 5, 'B2'),
    ('Artificial Intelligence', 'Stuart Russell', '9780136042594', 2010, 2, 'C3'),
    ('Operating System Concepts', 'Silberschatz', '9781118063330', 2012, 4, 'D4'),
    ('Computer Networks', 'Andrew S. Tanenbaum', '9780132126953', 2011, 3, 'E5');

-- initially inserting without the head_of_department column values.
INSERT INTO Department (department_name, location, phone_number) VALUES
    ('Computer Science', 'Building A', '123-456-7890'),
    ('Mathematics', 'Building B', '123-456-7891'),
    ('Physics', 'Building C', '123-456-7892'),
    ('Chemistry', 'Building D', '123-456-7893'),
    ('Biology', 'Building E', '123-456-7894');

INSERT INTO Teacher (first_name, last_name, date_of_birth, gender, email, phone_number, address, hire_date, department_id, salary) VALUES
    ('John', 'Doe', '1975-06-15', 'M', 'john.doe@example.com', '555-1234', '123 Main St', '2000-08-01', 1, 55000),
    ('Jane', 'Smith', '1980-09-25', 'F', 'jane.smith@example.com', '555-5678', '456 Oak St', '2005-07-15', 2, 60000),
    ('Robert', 'Brown', '1965-12-30', 'M', 'robert.brown@example.com', '555-9876', '789 Pine St', '1998-01-10', 3, 75000),
    ('Emily', 'Johnson', '1983-03-12', 'F', 'emily.johnson@example.com', '555-5432', '321 Maple St', '2010-09-05', 4, 62000),
    ('Michael', 'Williams', '1970-01-20', 'M', 'michael.williams@example.com', '555-3456', '654 Elm St', '2003-03-20', 5, 58000);

-- After the Teacher table has been populated, update the Department table to set the head_of_department 
--   values using the appropriate teacher_id from the Teacher table.

UPDATE Department 
SET head_of_department = (SELECT teacher_id FROM Teacher WHERE email = 'john.doe@example.com')
WHERE department_name = 'Computer Science';

UPDATE Department 
SET head_of_department = (SELECT teacher_id FROM Teacher WHERE email = 'jane.smith@example.com')
WHERE department_name = 'Mathematics';

UPDATE Department 
SET head_of_department = (SELECT teacher_id FROM Teacher WHERE email = 'robert.brown@example.com')
WHERE department_name = 'Physics';

UPDATE Department 
SET head_of_department = (SELECT teacher_id FROM Teacher WHERE email = 'emily.johnson@example.com')
WHERE department_name = 'Chemistry';

UPDATE Department 
SET head_of_department = (SELECT teacher_id FROM Teacher WHERE email = 'michael.williams@example.com')
WHERE department_name = 'Biology';

INSERT INTO Degree (degree_name, degree_level, department_id, required_credits) VALUES
    ('Bachelor of Computer Science', 'Bachelor', 1, 120),
    ('Master of Computer Science', 'Master', 1, 60),
    ('Bachelor of Mathematics', 'Bachelor', 2, 120),
    ('Master of Mathematics', 'Master', 2, 60),
    ('Bachelor of Physics', 'Bachelor', 3, 120);

INSERT INTO Student (first_name, last_name, date_of_birth, gender, email, phone_number, address, enrollment_date, department_id) VALUES
    ('Alice', 'Johnson', '2000-01-10', 'F', 'alice.johnson@example.com', '555-0123', '111 River Rd', '2018-09-01', 1),
    ('Bob', 'Smith', '1999-05-21', 'M', 'bob.smith@example.com', '555-0456', '222 Lake St', '2017-09-01', 2),
    ('Charlie', 'Brown', '2001-03-15', 'M', 'charlie.brown@example.com', '555-0789', '333 Hill St', '2019-09-01', 3),
    ('Diana', 'Clark', '1998-11-22', 'F', 'diana.clark@example.com', '555-0987', '444 Valley St', '2016-09-01', 4),
    ('Eve', 'Davis', '2000-07-07', 'F', 'eve.davis@example.com', '555-0654', '555 Ocean Ave', '2018-09-01', 5);

INSERT INTO Course (course_name, course_description, credits, department_id) VALUES
    ('Data Structures', 'Introduction to Data Structures', 4, 1),
    ('Algorithms', 'Design and Analysis of Algorithms', 4, 1),
    ('Linear Algebra', 'Matrix Theory and Linear Algebra', 3, 2),
    ('Quantum Mechanics', 'Fundamentals of Quantum Mechanics', 4, 3),
    ('Organic Chemistry', 'Introduction to Organic Chemistry', 4, 4);

INSERT INTO Student_Degree (student_id, degree_id, start_date, expected_graduation_date) VALUES
    (1, 1, '2018-09-01', '2022-05-01'),
    (2, 3, '2017-09-01', '2021-05-01'),
    (3, 5, '2019-09-01', '2023-05-01'),
    (4, 1, '2016-09-01', '2020-05-01'),
    (5, 1, '2018-09-01', '2022-05-01');

INSERT INTO Enrollment (student_id, course_id, enrollment_date, grade) VALUES
    (1, 1, '2018-09-05', 'A'),
    (2, 3, '2017-09-05', 'B'),
    (3, 4, '2019-09-05', 'C'),
    (4, 5, '2016-09-05', 'B'),
    (5, 2, '2018-09-05', 'A');

INSERT INTO Course_Schedule (course_id, teacher_id, classroom_id, day_of_week, start_time, end_time, semester) VALUES
    (1, 1, 1, 'Monday', '09:00', '10:30', 'Fall 2024'),
    (2, 1, 2, 'Wednesday', '11:00', '12:30', 'Fall 2024'),
    (3, 2, 3, 'Tuesday', '13:00', '14:30', 'Fall 2024'),
    (4, 3, 4, 'Thursday', '15:00', '16:30', 'Fall 2024'),
    (5, 4, 5, 'Friday', '08:00', '09:30', 'Fall 2024');

INSERT INTO Attendance (student_id, course_id, date, status) VALUES
    (1, 1, '2024-09-01', 'Present'),
    (2, 3, '2024-09-02', 'Absent'),
    (3, 4, '2024-09-03', 'Present'),
    (4, 5, '2024-09-04', 'Present'),
    (5, 2, '2024-09-05', 'Absent');

INSERT INTO Library_Borrowing (student_id, library_id, borrow_date, return_date, status) VALUES
    (1, 1, '2024-08-01', '2024-08-15', 'Returned'),
    (2, 2, '2024-08-10', '2024-08-25', 'Overdue'),
    (3, 3, '2024-08-15', '2024-08-30', 'Returned'),
    (4, 4, '2024-08-20', '2024-09-05', 'Pending'),
    (5, 5, '2024-08-25', '2024-09-10', 'Returned');

INSERT INTO Exam (course_id, exam_date, exam_type, location) VALUES
    (1, '2024-12-15', 'Final', 'Building A, Room 101'),
    (2, '2024-12-16', 'Midterm', 'Building B, Room 201'),
    (3, '2024-12-17', 'Final', 'Building C, Room 301'),
    (4, '2024-12-18', 'Midterm', 'Building D, Room 401'),
    (5, '2024-12-19', 'Final', 'Building E, Room 501');
