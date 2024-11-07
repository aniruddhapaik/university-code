CREATE TABLE autocars(
  cid INT PRIMARY KEY, 
  name VARCHAR(30), 
  mileagekmpl INT, 
  maxpetrolcapl INT, 
  maxspeedkmph INT, 
  cost INT);

INSERT INTO autocars VALUES
  (1, 'Ferrari', 50, 10, 250, 300000),
  (2, 'Maruti Alto', 70, 5, 150, 5000),
  (3, 'Tata Nano', 75, 5, 125, 4000),
  (4, 'Tata Innova', 60, 10, 170, 12000),
  (5, 'Toyota Fortuner', 60, 12, 200, 25000);

INSERT INTO autocars (cid, name, mileagekmpl, maxpetrolcapl, maxspeedkmph, cost) VALUES
  (6, 'Hyundai i10', 65, 6, 140, 6000),
  (7, 'Honda Civic', 55, 10, 220, 28000),
  (8, 'Ford Mustang', 45, 12, 240, 50000),
  (9, 'BMW X5', 50, 15, 210, 70000),
  (10, 'Audi Q7', 48, 16, 220, 75000),
  (11, 'Mahindra Thar', 55, 11, 160, 22000),
  (12, 'Jeep Compass', 52, 13, 180, 30000),
  (13, 'Nissan Altima', 60, 10, 190, 25000),
  (14, 'Tesla Model S', 85, 0, 250, 80000),
  (15, 'Mercedes G-Wagon', 40, 15, 210, 90000);

INSERT INTO autocars (cid, name, mileagekmpl, maxpetrolcapl, maxspeedkmph, cost) VALUES
  (16, 'Mazda CX-5', 58, 10, 180, 28000),
  (17, 'Chevrolet Spark', 68, 5, 135, 7000),
  (18, 'Volkswagen Golf', 55, 9, 210, 27000),
  (19, 'Porsche 911', 40, 11, 300, 100000),
  (20, 'Hyundai Tucson', 50, 12, 190, 32000);

SELECT mileagekmpl AS "Mileage", 
  count(*) AS "Number of Cars that Have the Same Mileage", 
  sum(cost) AS "Sum of Car Cost with the Same Mileage" 
  FROM autocars GROUP BY mileagekmpl;

SELECT LEFT(name, 1) AS initial, COUNT(*) AS "Car Count"
  FROM autocars
  GROUP BY initial
  ORDER BY initial;

SELECT LEFT(name, 1) AS initial, COUNT(*) AS car_count
  FROM autocars
  GROUP BY initial
  HAVING COUNT(*) > 1
  ORDER BY initial;

SELECT mileagekmpl AS "Mileage (km/L)", 
  COUNT(*) AS "Number of Cars with The Same Mileage" 
  FROM autocars 
  WHERE cost < 100000 
  GROUP BY mileagekmpl 
  HAVING mileagekmpl > 50;

SELECT course_name 
FROM course 
WHERE course_id IN (
  SELECT course_id 
  FROM course_schedule 
  WHERE classroom_id = (
    SELECT classroom_id 
    FROM classroom 
    WHERE building_name = 'Science Hall'
    )
  );

SELECT SUM(credits) 
  FROM Course
  WHERE department_id = (
    SELECT department_id 
    FROM Department 
    WHERE department_name = 'Physics'
  );

SELECT first_name, last_name 
  FROM Student 
  WHERE date_of_birth < ANY (
    SELECT date_of_birth 
    FROM Teacher 
    WHERE department_id = (
      SELECT department_id 
      FROM Department 
      WHERE department_name = 'Mathematics'
    )
  );

SELECT first_name, last_name 
  FROM Teacher 
  WHERE salary > ALL (
    SELECT salary 
    FROM Teacher 
    WHERE department_id = (
      SELECT department_id 
      FROM Department 
      WHERE department_name = 'Mathematics'
    )
  );

SELECT s.first_name, s.last_name, c.course_name
  FROM Student s
  INNER JOIN Enrollment e ON s.student_id = e.student_id
  INNER JOIN Course c ON e.course_id = c.course_id;

SELECT c.course_name, t.first_name, t.last_name
  FROM Course c
  LEFT JOIN Course_Schedule cs ON c.course_id = cs.course_id
  LEFT JOIN Teacher t ON cs.teacher_id = t.teacher_id;

SELECT t.first_name, t.last_name, c.course_name
  FROM Course c
  RIGHT JOIN Course_Schedule cs ON c.course_id = cs.course_id
  RIGHT JOIN Teacher t ON cs.teacher_id = t.teacher_id;

SELECT s.first_name, s.last_name, l.title
  FROM Student s
  FULL OUTER JOIN Library_Borrowing lb ON s.student_id = lb.student_id
  FULL OUTER JOIN Library l ON lb.book_id = l.book_id;

SELECT s1.first_name AS "Student 1 First Name", s1.last_name AS "Student 1 Last Name",
       s2.first_name AS "Student 2 First Name", s2.last_name AS "Student 2 First Name",
       d.department_name AS "Department"
  FROM student s1
  INNER JOIN student s2 ON s1.department_id = s2.department_id AND s1.student_id != s2.student_id
  INNER JOIN Department d ON s1.department_id = d.department_id;

SELECT c.course_name, t.first_name, t.last_name
  FROM Course c
  LEFT JOIN Course_Schedule cs ON c.course_id = cs.course_id
  LEFT JOIN Teacher t ON cs.teacher_id = t.teacher_id;

SELECT t.first_name, t.last_name, c.course_name
  FROM Course c
  RIGHT JOIN Course_Schedule cs ON c.course_id = cs.course_id
  RIGHT JOIN Teacher t ON cs.teacher_id = t.teacher_id;

SELECT s.first_name, s.last_name, l.title
  FROM Student s
  FULL OUTER JOIN Library_Borrowing lb ON s.student_id = lb.student_id
  FULL OUTER JOIN Library l ON lb.library_id = l.library_id;

SELECT DISTINCT * FROM (
  SELECT s.first_name, s.last_name, s.student_id, s.department_id 
  FROM student s 
  INNER JOIN student ON s.student_id = s.department_id
  );

SELECT s.first_name, s.last_name, d.department_name
  FROM Student s
  INNER JOIN Department d ON s.department_id = d.department_id;

SELECT s.first_name, s.last_name, s.date_of_birth
  FROM Student s
  WHERE s.date_of_birth < ANY (SELECT date_of_birth FROM Teacher);

CREATE VIEW student_department_view AS (
SELECT s.first_name, s.last_name, d.department_name
  FROM Student s
  INNER JOIN Department d ON s.department_id = d.department_id
);