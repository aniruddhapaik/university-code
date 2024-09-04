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
ADD CONSTRAINT fk_head_of_department
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
    date DATE,
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
-- Done with DDL commands - creation of tables, and altering

-- Now onto inserting test values into the tables, using DML commands
