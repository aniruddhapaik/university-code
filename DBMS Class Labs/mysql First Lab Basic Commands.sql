-- MySQL
show databases;
use world;
show tables;

select * from city where countrycode = "IND";
select sum(population) as "Total Population" from city where countrycode = "IND";

-- drop database University;
create database University;
show databases;
use university;

show tables;
create table Student(
	SID int,
    student_name varchar(20),
    dob date,
    city varchar(20)
);
desc Student;

alter table Student modify column SID int primary key;
-- alter table student drop primary key;
alter table student rename column city to place;
alter table student modify column SID int auto_increment;
alter table student modify column student_name varchar(30) not null;

alter table student add column date_now date not null;

insert into student (student_name, dob, place, date_now) values
("Varun", "2000-01-01", "New Delhi", current_date());

select * from student;

alter table student rename column date_now to entry_date;
alter table student alter entry_date set default "1970-01-01";
alter table student alter dob set default "1970-01-01";
alter table student alter place set default "Universe";

insert into student (student_name, dob, place, entry_date) values
("Naina", "1000-12-02", "Chennai", current_date()),
("Tom", "2000-10-02", "London", current_date()),
("Bob", "3000-02-20", "Washington", current_date()),
("Kalki", "2898-08-15", "Pondicherry", current_date());

alter table student modify column entry_date datetime;
update student set entry_date = current_timestamp() where SID = 1;
set sql_safe_updates = 0;
update student set entry_date = current_timestamp();

truncate table student;
alter table student auto_increment=1;
select * from student;

create table Department (
	DID int not null auto_increment,
    dept_name varchar(40) not null,
    floor_location int not null,
    primary key(DID)
);
desc Department;

alter table student add column dept_ID int not null;
alter table student add foreign key (dept_ID) references Department(DID);

insert into department (dept_name, floor_location) values
("Department of Business Administration", 0),
("Department of Computer Science", 1),
("Department of Commerce", 2);
select * from department;

insert into student (student_name, dob, place, entry_date, dept_ID) values
("Varun", "2000-01-01", "New Delhi", current_timestamp(), 1),
("Naina", "1000-12-02", "Chennai", current_timestamp(), 3),
("Tom", "2000-10-02", "London", current_timestamp(), 2),
("Bob", "3000-02-20", "Washington", current_timestamp(), 2),
("Kalki", "2898-08-15", "Pondicherry", current_timestamp(), 1);
select * from student;

select student_name as "Student Name", dept_name as "Department", place as "Home Town" 
	from student inner join department on student.dept_ID = department.DID;