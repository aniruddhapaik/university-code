Here are 20 questions focused on querying the "University" database, covering a variety of SQL keywords, clauses, and conditions:

### **Basic Queries**

1. **Select:**  
   Retrieve the first name, last name, and email of all students enrolled in the "Computer Science" department.

   ```sql
   SELECT first_name, last_name, email 
   FROM Student 
   WHERE department_id = (SELECT department_id FROM Department WHERE department_name = 'Computer Science');
   ```

2. **Where Clause with Conditions:**  
   Find all courses with more than 3 credits offered by the "Mathematics" department.

   ```sql
   SELECT course_name, credits 
   FROM Course 
   WHERE credits > 3 AND department_id = (SELECT department_id FROM Department WHERE department_name = 'Mathematics');
   ```

3. **Order By:**  
   List all teachers' names and emails, ordered by their hire date (most recent first).

   ```sql
   SELECT first_name, last_name, email 
   FROM Teacher 
   ORDER BY hire_date DESC;
   ```

### **Aggregate Functions and Grouping**

4. **Count and Group By:**  
   Find how many students are enrolled in each department.

   ```sql
   SELECT department_id, COUNT(*) AS total_students 
   FROM Student 
   GROUP BY department_id;
   ```

5. **AVG Function:**  
   Calculate the average salary of teachers in the "Biology" department.

   ```sql
   SELECT AVG(salary) 
   FROM Teacher 
   WHERE department_id = (SELECT department_id FROM Department WHERE department_name = 'Biology');
   ```

6. **SUM Function:**  
   Find the total number of credits for courses offered by the "Physics" department.

   ```sql
   SELECT SUM(credits) 
   FROM Course 
   WHERE department_id = (SELECT department_id FROM Department WHERE department_name = 'Physics');
   ```

### **Join Queries**

7. **Inner Join:**  
   List all students and the degrees they are pursuing.

   ```sql
   SELECT s.first_name, s.last_name, d.degree_name 
   FROM Student s
   INNER JOIN Student_Degree sd ON s.student_id = sd.student_id
   INNER JOIN Degree d ON sd.degree_id = d.degree_id;
   ```

8. **Left Join:**  
   List all courses and their assigned teachers (if a course has no teacher assigned, still list it).

   ```sql
   SELECT c.course_name, t.first_name, t.last_name 
   FROM Course c
   LEFT JOIN Course_Schedule cs ON c.course_id = cs.course_id
   LEFT JOIN Teacher t ON cs.teacher_id = t.teacher_id;
   ```

9. **Join with Filtering:**  
   Retrieve all students who borrowed books from the library but haven’t returned them yet.

   ```sql
   SELECT s.first_name, s.last_name 
   FROM Student s
   INNER JOIN Library_Borrowing lb ON s.student_id = lb.student_id
   WHERE lb.status = 'Pending';
   ```

10. **Join with Aggregate:**  
    Find the total number of students enrolled in each course.

   ```sql
   SELECT c.course_name, COUNT(e.student_id) AS total_enrolled
   FROM Course c
   INNER JOIN Enrollment e ON c.course_id = e.course_id
   GROUP BY c.course_name;
   ```

### **Subqueries**

11. **Subquery in Where Clause:**  
   Find all courses that are being taught in "Science Hall".

   ```sql
   SELECT course_name 
   FROM Course
   WHERE course_id IN (SELECT course_id FROM Course_Schedule WHERE classroom_id = (SELECT classroom_id FROM Classroom WHERE building_name = 'Science Hall'));
   ```

12. **Subquery in Select Clause:**  
   List the names of all students and their respective department names.

   ```sql
   SELECT first_name, last_name, (SELECT department_name FROM Department WHERE department_id = s.department_id) AS department
   FROM Student s;
   ```

13. **Correlated Subquery:**  
   Find students who are enrolled in more courses than any other student.

   ```sql
   SELECT first_name, last_name 
   FROM Student s
   WHERE (SELECT COUNT(*) FROM Enrollment e WHERE e.student_id = s.student_id) >
         (SELECT MAX(total_courses) FROM (SELECT COUNT(*) AS total_courses FROM Enrollment GROUP BY student_id) AS course_counts);
   ```

### **Advanced Clauses and Conditions**

14. **Distinct:**  
   Retrieve the distinct list of departments that offer courses with more than 3 credits.

   ```sql
   SELECT DISTINCT department_id 
   FROM Course 
   WHERE credits > 3;
   ```

15. **HAVING Clause:**  
   Find departments that have more than 3 teachers.

   ```sql
   SELECT department_id, COUNT(*) AS total_teachers 
   FROM Teacher 
   GROUP BY department_id 
   HAVING COUNT(*) > 3;
   ```

16. **LIKE with Wildcards:**  
   Find all books in the library with titles containing the word "Computer".

   ```sql
   SELECT title 
   FROM Library 
   WHERE title LIKE '%Computer%';
   ```

17. **BETWEEN Clause:**  
   Find all exams scheduled between '2024-12-15' and '2024-12-18'.

   ```sql
   SELECT course_id, exam_date 
   FROM Exam 
   WHERE exam_date BETWEEN '2024-12-15' AND '2024-12-18';
   ```

18. **IN Clause:**  
   Find the names of all students who are enrolled in the "Data Structures" or "Algorithms" courses.

   ```sql
   SELECT s.first_name, s.last_name 
   FROM Student s
   WHERE s.student_id IN (SELECT e.student_id 
                          FROM Enrollment e 
                          WHERE e.course_id IN (SELECT course_id FROM Course WHERE course_name IN ('Data Structures', 'Algorithms')));
   ```

19. **Case Statement:**  
   Display students' names along with their grade category (A: 'Excellent', B: 'Good', C: 'Average', otherwise 'Needs Improvement').

   ```sql
   SELECT s.first_name, s.last_name, 
          CASE 
              WHEN e.grade = 'A' THEN 'Excellent'
              WHEN e.grade = 'B' THEN 'Good'
              WHEN e.grade = 'C' THEN 'Average'
              ELSE 'Needs Improvement'
          END AS grade_category
   FROM Enrollment e
   INNER JOIN Student s ON e.student_id = s.student_id;
   ```

20. **Exists Clause:**  
   List all departments that have at least one student enrolled.

   ```sql
   SELECT department_name 
   FROM Department d
   WHERE EXISTS (SELECT 1 FROM Student s WHERE s.department_id = d.department_id);
   ```

These questions cover a wide range of SQL concepts, such as `JOIN`, `GROUP BY`, `HAVING`, subqueries, aggregate functions, and more, helping you master querying your "University" database.
