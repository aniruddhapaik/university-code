alter table student alter column name set not null, alter column dob set not null, alter column gender set not null;

insert into department (department_name) values
('Computer Science'),
('M.Com'),
('MBA'),
('English'),
('French'),
('Physics'),
('Chemistry'),
('Mathematics'),
('Biology'),
('German');

insert into course (course_name, course_credits, department_id) values
('MSc CS', 72, 1),
('M.Com General', 70, 2),
('MBA IM', 70, 3),
('English Professional', 50, 4),
('MCA', 72, 1),
('Physics Intensive', 65, 6),
('MBA General', 70, 3),
('Mathematics Intensive', 65, 8),
('M.Tech CSE', 60, 1),
('German Professional', 50, 10);

insert into student (name, dob, gender, department_id) values
('Ani', '2000-01-01', 'M', 1),
('Aka', '2000-02-01', 'F', 10),
('Raja', '2000-03-01', 'M', 3),
('Kruti', '2000-04-01', 'F', 4),
('Bhashu', '2000-05-01', 'M', 3),
('Dyu', '2000-06-01', 'M', 1),
('Shivani', '2000-07-01', 'F', 4),
('Uttu', '2000-08-01', 'F', 2),
('Jeya', '2000-09-01', 'M', 8),
('Ankita', '2000-10-01', 'F', 6);

insert into course_registered (course_code, student_id) values
(1, 5),
(2, 10),
(3, 7),
(4, 4),
(5, 3),
(6, 1),
(7, 4),
(8, 2),
(9, 8),
(10, 6);

alter table course_registered add column reg_date date, alter column reg_date set default current_date;
update course_registered set reg_date = current_date;
alter table course_registered alter column reg_date set not null;

select d.department_name, sum(c.course_credits) AS "Total Credits"
from course c left outer join department d 
on c.department_id = d.department_id 
group by d.department_id order by sum(c.course_credits) desc;

select d.department_name, count(c.department_id) 
from course c left outer join department d 
on c.department_id = d.department_id
group by d.department_id
order by count(c.department_id) desc
limit 1 offset 1;

select d.*, s.* from department d natural join student s;

ALTER TABLE course_registered 
ADD CONSTRAINT course_reg_pkey 
PRIMARY KEY (course_code, student_id);

CREATE TABLE course_registered (
    course_code VARCHAR(50),
    student_id INT,
    registration_date DATE,
    -- other columns as needed
    PRIMARY KEY (course_code, student_id)
);

SELECT d.*
FROM doctor d
JOIN patient c ON d.doctor_id = c.doctor_id
GROUP BY d.doctor_id, d.specialization, d.qualification, d.first_name, d.middle_name, d.last_name
HAVING COUNT(c.patient_id) > 3;

SELECT d.*, c.case_id, c.case_details
FROM Doctor d
LEFT OUTER JOIN CASE c ON d.Doctor_id = c.Doctor_id;
