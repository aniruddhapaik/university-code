Server [localhost]:
Database [postgres]: constraints
Port [5432]:
Username [postgres]: aniruddha
Password for user aniruddha:

psql (17.0)
WARNING: Console code page (437) differs from Windows code page (1252)
         8-bit characters might not work correctly. See psql reference
         page "Notes for Windows users" for details.
Type "help" for help.

constraints=# create database exam;
CREATE DATABASE
constraints=# \c exam
You are now connected to database "exam" as user "aniruddha".
exam=# create table tenant (
exam(# tenant_id int primary key,
exam(# name varchar(50),
exam(# contact_info varchar(50)
exam(# );
CREATE TABLE
exam=# create table apartment (
exam(# apartment_id int primary key,
exam(# location varchar(50),
exam(# rent int
exam(# );
CREATE TABLE
exam=# create table lease (
exam(# lease_id int primary key,
exam(# tenant_id int references tenant(tenant_id),
exam(# apartment_id int references apartment(apartment_id),
exam(# start_date date
exam(# end_date date
exam(# );
ERROR:  syntax error at or near "end_date"
LINE 6: end_date date
        ^
exam=# create table lease (
exam(# lease_id int primary key,
exam(# tenant_id int references tenant(tenant_id),
exam(# apartment_id int references apartment(apartment_id),
exam(# start_date date,
exam(# end_date date
exam(# );
CREATE TABLE
exam=# create table payment (
exam(# payment_id int primary key,
exam(# lease_id int references lease(lease_id),
exam(# payment_amount int,
exam(# payment_date date
exam(# );
CREATE TABLE
exam=# lter table lease add column security_deposit decimal(10,2);
ERROR:  syntax error at or near "lter"
LINE 1: lter table lease add column security_deposit decimal(10,2);
        ^
exam=# alter table lease add column security_deposit decimal(10,2);
ALTER TABLE
exam=# alter table apartment alter column rent set data type decimal(10,2);
ALTER TABLE
exam=# alter table payment alter column payment_amount set data type decimal(10,2);
ALTER TABLE
exam=# \d tenant
                         Table "public.tenant"
    Column    |         Type          | Collation | Nullable | Default
--------------+-----------------------+-----------+----------+---------
 tenant_id    | integer               |           | not null |
 name         | character varying(50) |           |          |
 contact_info | character varying(50) |           |          |
Indexes:
    "tenant_pkey" PRIMARY KEY, btree (tenant_id)
Referenced by:
    TABLE "lease" CONSTRAINT "lease_tenant_id_fkey" FOREIGN KEY (tenant_id) REFERENCES tenant(tenant_id)


exam=# \d apartment
                       Table "public.apartment"
    Column    |         Type          | Collation | Nullable | Default
--------------+-----------------------+-----------+----------+---------
 apartment_id | integer               |           | not null |
 location     | character varying(50) |           |          |
 rent         | numeric(10,2)         |           |          |
Indexes:
    "apartment_pkey" PRIMARY KEY, btree (apartment_id)
Referenced by:
    TABLE "lease" CONSTRAINT "lease_apartment_id_fkey" FOREIGN KEY (apartment_id) REFERENCES apartment(apartment_id)


exam=# \d lease
                       Table "public.lease"
      Column      |     Type      | Collation | Nullable | Default
------------------+---------------+-----------+----------+---------
 lease_id         | integer       |           | not null |
 tenant_id        | integer       |           |          |
 apartment_id     | integer       |           |          |
 start_date       | date          |           |          |
 end_date         | date          |           |          |
 security_deposit | numeric(10,2) |           |          |
Indexes:
    "lease_pkey" PRIMARY KEY, btree (lease_id)
Foreign-key constraints:
    "lease_apartment_id_fkey" FOREIGN KEY (apartment_id) REFERENCES apartment(apartment_id)
    "lease_tenant_id_fkey" FOREIGN KEY (tenant_id) REFERENCES tenant(tenant_id)
Referenced by:
    TABLE "payment" CONSTRAINT "payment_lease_id_fkey" FOREIGN KEY (lease_id) REFERENCES lease(lease_id)


exam=# \d payment
                     Table "public.payment"
     Column     |     Type      | Collation | Nullable | Default
----------------+---------------+-----------+----------+---------
 payment_id     | integer       |           | not null |
 lease_id       | integer       |           |          |
 payment_amount | numeric(10,2) |           |          |
 payment_date   | date          |           |          |
Indexes:
    "payment_pkey" PRIMARY KEY, btree (payment_id)
Foreign-key constraints:
    "payment_lease_id_fkey" FOREIGN KEY (lease_id) REFERENCES lease(lease_id)


exam=# insert into tenant (tenant_id, name, contact_info) values
exam-# (1, 'Ani', '1234567890'),
exam-# (2, 'Raja', '0987654321'),
exam-# (3, 'Sarthak', '1234509876'),
exam-# (4, 'Bhashu', '0987612345'),
exam-# (5, 'Bibek', '5432167890');
INSERT 0 5
exam=# insert into apartment (tenant_id, location, rent) values
exam-# (1, 'Rainbow Nagar', 20000.00),
exam-# (2, 'Kuruchikuppam', 15000.00),
exam-# (3, 'Anna Salai', 30000.00),
exam-# (4, 'Kharagpur', 45000.00),
exam-# (5, 'Rajinder Nagar', 10000.00);
ERROR:  column "tenant_id" of relation "apartment" does not exist
LINE 1: insert into apartment (tenant_id, location, rent) values
                               ^
exam=# insert into apartment (apartment_id, location, rent) values
exam-# (1, 'Rainbow Nagar', 20000.00),
exam-# (2, 'Kuruchikuppam', 15000.00),
exam-# (3, 'Anna Salai', 30000.00),
exam-# (4, 'Kharagpur', 45000.00),
exam-# (5, 'Rajinder Nagar', 10000.00);
INSERT 0 5
exam=# select * from apartment;
 apartment_id |    location    |   rent
--------------+----------------+----------
            1 | Rainbow Nagar  | 20000.00
            2 | Kuruchikuppam  | 15000.00
            3 | Anna Salai     | 30000.00
            4 | Kharagpur      | 45000.00
            5 | Rajinder Nagar | 10000.00
(5 rows)


exam=# insert into lease (lease_id, tenant_id, apartment_id, start_date, end_date, security_deposit) values
exam-# (1, 2, 3, '2024-01-01', '2026-12-31', 15000.00),
exam-# (2, 1, 2, '2024-01-01', '2028-12-31', 7500.00),
exam-# (3, 4, 1, '2020-05-01', '2030-05-01', 10000.00),
exam-# (4, 5, 4, '2022-10-01', '2028-10-01', 22500.00),
exam-# (5, 3, 5, '2021-07-01', '2032-07-01', 5000.00);
INSERT 0 5
exam=#  insert into payment (payment_id, lease_id, payment_amount, payment_date) values
exam-# (1, 3, 1000.00, '2020-05-01'),
exam-# (2, 1, 7000.00, '2020-05-01'),
exam-# (3, 2, 5000.00, '2020-05-01'),
exam-# (4, 5, 1500.00, '2020-05-01'),
exam-# (5, 4, 1800.00, '2020-05-01');
INSERT 0 5
exam=# truncate table payment;
TRUNCATE TABLE
exam=# insert into payment (payment_id, lease_id, payment_amount, payment_date) values
exam-# (1, 3, 20000.00, '2020-05-01'),
exam-# (2, 1, 30000.00, '2024-01-01'),
exam-# (3, 2, 15000.00, '2022-01-01'),
exam-# (4, 5, 10000.00, '2021-07-01'),
exam-# (5, 4, 45000.00, '2022-10-01'),
exam-# (6, 3, 20000.00, '2020-06-01'),
exam-# (7, 1, 30000.00, '2024-02-01'),
exam-# (8, 2, 15000.00, '2022-02-01'),
exam-# (9, 5, 10000.00, '2021-08-01'),
exam-# (10, 4, 45000.00, '2022-11-01'),
exam-# (11, 3, 20000.00, '2020-07-01'),
exam-# (12, 1, 30000.00, '2024-03-01'),
exam-# (13, 2, 15000.00, '2022-03-01'),
exam-# (14, 5, 10000.00, '2021-09-01'),
exam-# (15, 4, 45000.00, '2022-12-01');
INSERT 0 15
exam=# select * from payment;
 payment_id | lease_id | payment_amount | payment_date
------------+----------+----------------+--------------
          1 |        3 |       20000.00 | 2020-05-01
          2 |        1 |       30000.00 | 2024-01-01
          3 |        2 |       15000.00 | 2022-01-01
          4 |        5 |       10000.00 | 2021-07-01
          5 |        4 |       45000.00 | 2022-10-01
          6 |        3 |       20000.00 | 2020-06-01
          7 |        1 |       30000.00 | 2024-02-01
          8 |        2 |       15000.00 | 2022-02-01
          9 |        5 |       10000.00 | 2021-08-01
         10 |        4 |       45000.00 | 2022-11-01
         11 |        3 |       20000.00 | 2020-07-01
         12 |        1 |       30000.00 | 2024-03-01
         13 |        2 |       15000.00 | 2022-03-01
         14 |        5 |       10000.00 | 2021-09-01
         15 |        4 |       45000.00 | 2022-12-01
(15 rows)


exam=# select a.apartment_id, sum(p.payment_amount) from apartment a
exam-# left outer join lease l on a.apartment_id = l.apartment_id
exam-# left outer join payment p on l.lease_id = p.lease_id
exam-# group by a.apartment_id;
 apartment_id |    sum
--------------+-----------
            4 | 135000.00
            2 |  45000.00
            3 |  90000.00
            5 |  30000.00
            1 |  60000.00
(5 rows)


exam=# select a.apartment_id, a.location, sum(p.payment_amount) as "Total rent collected by apartment" from apartment a
exam-# left outer join lease l on a.apartment_id = l.apartment_id
exam-# left outer join payment p on l.lease_id = p.lease_id
exam-# group by a.apartment_id;
 apartment_id |    location    | Total rent collected by apartment
--------------+----------------+-----------------------------------
            4 | Kharagpur      |                         135000.00
            2 | Kuruchikuppam  |                          45000.00
            3 | Anna Salai     |                          90000.00
            5 | Rajinder Nagar |                          30000.00
            1 | Rainbow Nagar  |                          60000.00
(5 rows)


exam=# select t.*, a.*, l.end_date - l.start_date as "Lease Duration"
exam-# from tenant t
exam-# left outer join lease l on t.tenant_id = l.tenant_id
exam-# left outer join apartment a on l.apartment_id = a.apartment_id;
 tenant_id |  name   | contact_info | apartment_id |    location    |   rent   | Lease Duration
-----------+---------+--------------+--------------+----------------+----------+----------------
         2 | Raja    | 0987654321   |            3 | Anna Salai     | 30000.00 |           1095
         1 | Ani     | 1234567890   |            2 | Kuruchikuppam  | 15000.00 |           1826
         4 | Bhashu  | 0987612345   |            1 | Rainbow Nagar  | 20000.00 |           3652
         5 | Bibek   | 5432167890   |            4 | Kharagpur      | 45000.00 |           2192
         3 | Sarthak | 1234509876   |            5 | Rajinder Nagar | 10000.00 |           4018
(5 rows)


exam=# select t.*, a.*, DATE(l.end_date - l.start_date) as "Lease Duration"
exam-# from tenant t
exam-# left outer join lease l on t.tenant_id = l.tenant_id
exam-# left outer join apartment a on l.apartment_id = a.apartment_id;
ERROR:  function date(integer) does not exist
LINE 1: select t.*, a.*, DATE(l.end_date - l.start_date) as "Lease D...
                         ^
HINT:  No function matches the given name and argument types. You might need to add explicit type casts.
exam=# select t.*, a.*, to_date(l.end_date - l.start_date) as "Lease Duration"
exam-# from tenant t
exam-# left outer join lease l on t.tenant_id = l.tenant_id
exam-# left outer join apartment a on l.apartment_id = a.apartment_id;
ERROR:  function to_date(integer) does not exist
LINE 1: select t.*, a.*, to_date(l.end_date - l.start_date) as "Leas...
                         ^
HINT:  No function matches the given name and argument types. You might need to add explicit type casts.
exam=#
exam=# select t.*, a.*, to_date(l.end_date - l.start_date, 'DD') as "Lease Duration"
exam-# from tenant t
exam-# left outer join lease l on t.tenant_id = l.tenant_id
exam-# left outer join apartment a on l.apartment_id = a.apartment_id;
ERROR:  function to_date(integer, unknown) does not exist
LINE 1: select t.*, a.*, to_date(l.end_date - l.start_date, 'DD') as...
                         ^
HINT:  No function matches the given name and argument types. You might need to add explicit type casts.
exam=# \select t.*, a.*, age(l.end_date, l.start_date) as "Lease Duration"
invalid command \select
Try \? for help.
exam=# from tenant t
exam-# left outer join lease l on t.tenant_id = l.tenant_id
exam-# left outer join apartment a on l.apartment_id = a.apartment_id;
ERROR:  syntax error at or near "from"
LINE 1: from tenant t
        ^
exam=# select t.*, a.*, age(l.end_date, l.start_date)
exam-# from tenant t
exam-# left outer join lease l on t.tenant_id = l.tenant_id
exam-# left outer join apartment a on l.apartment_id = a.apartment_id;
 tenant_id |  name   | contact_info | apartment_id |    location    |   rent   |           age
-----------+---------+--------------+--------------+----------------+----------+-------------------------
         2 | Raja    | 0987654321   |            3 | Anna Salai     | 30000.00 | 2 years 11 mons 30 days
         1 | Ani     | 1234567890   |            2 | Kuruchikuppam  | 15000.00 | 4 years 11 mons 30 days
         4 | Bhashu  | 0987612345   |            1 | Rainbow Nagar  | 20000.00 | 10 years
         5 | Bibek   | 5432167890   |            4 | Kharagpur      | 45000.00 | 6 years
         3 | Sarthak | 1234509876   |            5 | Rajinder Nagar | 10000.00 | 11 years
(5 rows)


exam=# select t.*, a.*, age(l.end_date, l.start_date) as 'Lease Duration'
exam-# from tenant t
exam-# left outer join lease l on t.tenant_id = l.tenant_id
exam-# left outer join apartment a on l.apartment_id = a.apartment_id;
ERROR:  syntax error at or near "'Lease Duration'"
LINE 1: select t.*, a.*, age(l.end_date, l.start_date) as 'Lease Dur...'
                                                          ^
exam=# select t.*, a.*, age(l.end_date, l.start_date) as Lease_Duration
exam-# from tenant t
exam-# left outer join lease l on t.tenant_id = l.tenant_id
exam-# left outer join apartment a on l.apartment_id = a.apartment_id;
 tenant_id |  name   | contact_info | apartment_id |    location    |   rent   |     lease_duration
-----------+---------+--------------+--------------+----------------+----------+-------------------------
         2 | Raja    | 0987654321   |            3 | Anna Salai     | 30000.00 | 2 years 11 mons 30 days
         1 | Ani     | 1234567890   |            2 | Kuruchikuppam  | 15000.00 | 4 years 11 mons 30 days
         4 | Bhashu  | 0987612345   |            1 | Rainbow Nagar  | 20000.00 | 10 years
         5 | Bibek   | 5432167890   |            4 | Kharagpur      | 45000.00 | 6 years
         3 | Sarthak | 1234509876   |            5 | Rajinder Nagar | 10000.00 | 11 years
(5 rows)


exam=# select t.*, a.apartment_id, a.location, p.payment_amount, p.payment_date
exam-# from payment p
exam-# left outer join lease l on p.lease_id = l.lease_id
exam-# left outer join apartment a on l.apartment_id = a.apartment_id
exam-# left out join tenant t on l.tenant_id = t.tenant_id;
ERROR:  syntax error at or near "out"
LINE 5: left out join tenant t on l.tenant_id = t.tenant_id;
             ^
exam=#
exam=# select t.*, a.apartment_id, a.location, p.payment_amount, p.payment_date
exam-# from payment p
exam-# left outer join lease l on p.lease_id = l.lease_id
exam-# left outer join apartment a on l.apartment_id = a.apartment_id
exam-# left outer join tenant t on l.tenant_id = t.tenant_id;
 tenant_id |  name   | contact_info | apartment_id |    location    | payment_amount | payment_date
-----------+---------+--------------+--------------+----------------+----------------+--------------
         4 | Bhashu  | 0987612345   |            1 | Rainbow Nagar  |       20000.00 | 2020-05-01
         2 | Raja    | 0987654321   |            3 | Anna Salai     |       30000.00 | 2024-01-01
         1 | Ani     | 1234567890   |            2 | Kuruchikuppam  |       15000.00 | 2022-01-01
         3 | Sarthak | 1234509876   |            5 | Rajinder Nagar |       10000.00 | 2021-07-01
         5 | Bibek   | 5432167890   |            4 | Kharagpur      |       45000.00 | 2022-10-01
         4 | Bhashu  | 0987612345   |            1 | Rainbow Nagar  |       20000.00 | 2020-06-01
         2 | Raja    | 0987654321   |            3 | Anna Salai     |       30000.00 | 2024-02-01
         1 | Ani     | 1234567890   |            2 | Kuruchikuppam  |       15000.00 | 2022-02-01
         3 | Sarthak | 1234509876   |            5 | Rajinder Nagar |       10000.00 | 2021-08-01
         5 | Bibek   | 5432167890   |            4 | Kharagpur      |       45000.00 | 2022-11-01
         4 | Bhashu  | 0987612345   |            1 | Rainbow Nagar  |       20000.00 | 2020-07-01
         2 | Raja    | 0987654321   |            3 | Anna Salai     |       30000.00 | 2024-03-01
         1 | Ani     | 1234567890   |            2 | Kuruchikuppam  |       15000.00 | 2022-03-01
         3 | Sarthak | 1234509876   |            5 | Rajinder Nagar |       10000.00 | 2021-09-01
         5 | Bibek   | 5432167890   |            4 | Kharagpur      |       45000.00 | 2022-12-01
(15 rows)


exam=# select t.*, a.apartment_id, a.location, p.payment_amount, p.payment_date
exam-# from payment p
exam-# left outer join lease l on p.lease_id = l.lease_id
exam-# left outer join apartment a on l.apartment_id = a.apartment_id
exam-# left outer join tenant t on l.tenant_id = t.tenant_id
exam-# order by t.tenant_id;
 tenant_id |  name   | contact_info | apartment_id |    location    | payment_amount | payment_date
-----------+---------+--------------+--------------+----------------+----------------+--------------
         1 | Ani     | 1234567890   |            2 | Kuruchikuppam  |       15000.00 | 2022-02-01
         1 | Ani     | 1234567890   |            2 | Kuruchikuppam  |       15000.00 | 2022-03-01
         1 | Ani     | 1234567890   |            2 | Kuruchikuppam  |       15000.00 | 2022-01-01
         2 | Raja    | 0987654321   |            3 | Anna Salai     |       30000.00 | 2024-02-01
         2 | Raja    | 0987654321   |            3 | Anna Salai     |       30000.00 | 2024-03-01
         2 | Raja    | 0987654321   |            3 | Anna Salai     |       30000.00 | 2024-01-01
         3 | Sarthak | 1234509876   |            5 | Rajinder Nagar |       10000.00 | 2021-08-01
         3 | Sarthak | 1234509876   |            5 | Rajinder Nagar |       10000.00 | 2021-07-01
         3 | Sarthak | 1234509876   |            5 | Rajinder Nagar |       10000.00 | 2021-09-01
         4 | Bhashu  | 0987612345   |            1 | Rainbow Nagar  |       20000.00 | 2020-05-01
         4 | Bhashu  | 0987612345   |            1 | Rainbow Nagar  |       20000.00 | 2020-06-01
         4 | Bhashu  | 0987612345   |            1 | Rainbow Nagar  |       20000.00 | 2020-07-01
         5 | Bibek   | 5432167890   |            4 | Kharagpur      |       45000.00 | 2022-11-01
         5 | Bibek   | 5432167890   |            4 | Kharagpur      |       45000.00 | 2022-10-01
         5 | Bibek   | 5432167890   |            4 | Kharagpur      |       45000.00 | 2022-12-01
(15 rows)


exam=# select t.*, a.apartment_id, a.location, p.payment_amount, p.payment_date
exam-# from payment p
exam-# left outer join lease l on p.lease_id = l.lease_id
exam-# left outer join apartment a on l.apartment_id = a.apartment_id
exam-# left outer join tenant t on l.tenant_id = t.tenant_id
exam-# order by t.tenant_id, p.payment_date asc;
 tenant_id |  name   | contact_info | apartment_id |    location    | payment_amount | payment_date
-----------+---------+--------------+--------------+----------------+----------------+--------------
         1 | Ani     | 1234567890   |            2 | Kuruchikuppam  |       15000.00 | 2022-01-01
         1 | Ani     | 1234567890   |            2 | Kuruchikuppam  |       15000.00 | 2022-02-01
         1 | Ani     | 1234567890   |            2 | Kuruchikuppam  |       15000.00 | 2022-03-01
         2 | Raja    | 0987654321   |            3 | Anna Salai     |       30000.00 | 2024-01-01
         2 | Raja    | 0987654321   |            3 | Anna Salai     |       30000.00 | 2024-02-01
         2 | Raja    | 0987654321   |            3 | Anna Salai     |       30000.00 | 2024-03-01
         3 | Sarthak | 1234509876   |            5 | Rajinder Nagar |       10000.00 | 2021-07-01
         3 | Sarthak | 1234509876   |            5 | Rajinder Nagar |       10000.00 | 2021-08-01
         3 | Sarthak | 1234509876   |            5 | Rajinder Nagar |       10000.00 | 2021-09-01
         4 | Bhashu  | 0987612345   |            1 | Rainbow Nagar  |       20000.00 | 2020-05-01
         4 | Bhashu  | 0987612345   |            1 | Rainbow Nagar  |       20000.00 | 2020-06-01
         4 | Bhashu  | 0987612345   |            1 | Rainbow Nagar  |       20000.00 | 2020-07-01
         5 | Bibek   | 5432167890   |            4 | Kharagpur      |       45000.00 | 2022-10-01
         5 | Bibek   | 5432167890   |            4 | Kharagpur      |       45000.00 | 2022-11-01
         5 | Bibek   | 5432167890   |            4 | Kharagpur      |       45000.00 | 2022-12-01
(15 rows)


exam=# select t.*, a.*, l.end_date - l.start_date as Lease_Duration
exam-# from tenant t
exam-# left outer join lease l on t.tenant_id = l.tenant_id
exam-# left outer join apartment a on l.apartment_id = a.apartment_id;
 tenant_id |  name   | contact_info | apartment_id |    location    |   rent   | lease_duration
-----------+---------+--------------+--------------+----------------+----------+----------------
         2 | Raja    | 0987654321   |            3 | Anna Salai     | 30000.00 |           1095
         1 | Ani     | 1234567890   |            2 | Kuruchikuppam  | 15000.00 |           1826
         4 | Bhashu  | 0987612345   |            1 | Rainbow Nagar  | 20000.00 |           3652
         5 | Bibek   | 5432167890   |            4 | Kharagpur      | 45000.00 |           2192
         3 | Sarthak | 1234509876   |            5 | Rajinder Nagar | 10000.00 |           4018
(5 rows)


exam=# select t.*, a.*, l.end_date - l.start_date as Lease_Duration_in_days
exam-# from tenant t
exam-# left outer join lease l on t.tenant_id = l.tenant_id
exam-# left outer join apartment a on l.apartment_id = a.apartment_id;
 tenant_id |  name   | contact_info | apartment_id |    location    |   rent   | lease_duration_in_days
-----------+---------+--------------+--------------+----------------+----------+------------------------
         2 | Raja    | 0987654321   |            3 | Anna Salai     | 30000.00 |                   1095
         1 | Ani     | 1234567890   |            2 | Kuruchikuppam  | 15000.00 |                   1826
         4 | Bhashu  | 0987612345   |            1 | Rainbow Nagar  | 20000.00 |                   3652
         5 | Bibek   | 5432167890   |            4 | Kharagpur      | 45000.00 |                   2192
         3 | Sarthak | 1234509876   |            5 | Rajinder Nagar | 10000.00 |                   4018
(5 rows)


exam=# create view as (
exam(# select t.*, a.apartment_id, a.location, p.payment_amount, p.payment_date
exam(# from payment p
exam(# left outer join lease l on p.lease_id = l.lease_id
exam(# left outer join apartment a on l.apartment_id = a.apartment_id
exam(# left outer join tenant t on l.tenant_id = t.tenant_id
exam(# order by t.tenant_id, p.payment_date asc);
ERROR:  syntax error at or near "as"
LINE 1: create view as (
                    ^
exam=# create view Tenant_details_Payment_history as (
exam(# select t.*, a.apartment_id, a.location, p.payment_amount, p.payment_date
exam(# from payment p
exam(# left outer join lease l on p.lease_id = l.lease_id
exam(# left outer join apartment a on l.apartment_id = a.apartment_id
exam(# left outer join tenant t on l.tenant_id = t.tenant_id
exam(# order by t.tenant_id, p.payment_date asc);
CREATE VIEW
exam=# select t.tenant_name, l.end_date - NOW() as "Lease Time Remaining"
exam-# from tenant t
exam-# right outer join lease l on t.tenant_id = l.tenant_id;
ERROR:  column t.tenant_name does not exist
LINE 1: select t.tenant_name, l.end_date - NOW() as "Lease Time Rema..."
               ^
exam=# select t.name, l.end_date - NOW() as "Lease Time Remaining"
exam-# from tenant t
exam-# right outer join lease l on t.tenant_id = l.tenant_id;
  name   |   Lease Time Remaining
---------+---------------------------
 Raja    | 777 days 07:30:12.788136
 Ani     | 1508 days 07:30:12.788136
 Bhashu  | 1994 days 07:30:12.788136
 Bibek   | 1417 days 07:30:12.788136
 Sarthak | 2786 days 07:30:12.788136
(5 rows)


exam=# select t.tenant_id, t.name, l.end_date - NOW() as "Lease Time Remaining"
exam-# from tenant t
exam-# right outer join lease l on t.tenant_id = l.tenant_id;
 tenant_id |  name   |   Lease Time Remaining
-----------+---------+---------------------------
         2 | Raja    | 777 days 07:29:23.969981
         1 | Ani     | 1508 days 07:29:23.969981
         4 | Bhashu  | 1994 days 07:29:23.969981
         5 | Bibek   | 1417 days 07:29:23.969981
         3 | Sarthak | 2786 days 07:29:23.969981
(5 rows)


exam=# select * from Tenant_details_Payment_history;
 tenant_id |  name   | contact_info | apartment_id |    location    | payment_amount | payment_date
-----------+---------+--------------+--------------+----------------+----------------+--------------
         1 | Ani     | 1234567890   |            2 | Kuruchikuppam  |       15000.00 | 2022-01-01
         1 | Ani     | 1234567890   |            2 | Kuruchikuppam  |       15000.00 | 2022-02-01
         1 | Ani     | 1234567890   |            2 | Kuruchikuppam  |       15000.00 | 2022-03-01
         2 | Raja    | 0987654321   |            3 | Anna Salai     |       30000.00 | 2024-01-01
         2 | Raja    | 0987654321   |            3 | Anna Salai     |       30000.00 | 2024-02-01
         2 | Raja    | 0987654321   |            3 | Anna Salai     |       30000.00 | 2024-03-01
         3 | Sarthak | 1234509876   |            5 | Rajinder Nagar |       10000.00 | 2021-07-01
         3 | Sarthak | 1234509876   |            5 | Rajinder Nagar |       10000.00 | 2021-08-01
         3 | Sarthak | 1234509876   |            5 | Rajinder Nagar |       10000.00 | 2021-09-01
         4 | Bhashu  | 0987612345   |            1 | Rainbow Nagar  |       20000.00 | 2020-05-01
         4 | Bhashu  | 0987612345   |            1 | Rainbow Nagar  |       20000.00 | 2020-06-01
         4 | Bhashu  | 0987612345   |            1 | Rainbow Nagar  |       20000.00 | 2020-07-01
         5 | Bibek   | 5432167890   |            4 | Kharagpur      |       45000.00 | 2022-10-01
         5 | Bibek   | 5432167890   |            4 | Kharagpur      |       45000.00 | 2022-11-01
         5 | Bibek   | 5432167890   |            4 | Kharagpur      |       45000.00 | 2022-12-01
(15 rows)


exam=# select t.tenant_id, t.name, l.end_date - current_date as "Lease Time Remaining"
exam-# from tenant t
exam-# right outer join lease l on t.tenant_id = l.tenant_id;
 tenant_id |  name   | Lease Time Remaining
-----------+---------+----------------------
         2 | Raja    |                  778
         1 | Ani     |                 1509
         4 | Bhashu  |                 1995
         5 | Bibek   |                 1418
         3 | Sarthak |                 2787
(5 rows)


exam=# select t.tenant_id, t.name, l.end_date - current_date as "Lease Time Remaining in Days"
exam-# from tenant t
exam-# right outer join lease l on t.tenant_id = l.tenant_id;
 tenant_id |  name   | Lease Time Remaining in Days
-----------+---------+------------------------------
         2 | Raja    |                          778
         1 | Ani     |                         1509
         4 | Bhashu  |                         1995
         5 | Bibek   |                         1418
         3 | Sarthak |                         2787
(5 rows)


exam=# select t.tenant_id, t.name, l.end_date - current_date as "Lease Time Remaining in Days"
exam-# from tenant t
exam-# LEFT outer join lease l on t.tenant_id = l.tenant_id;
 tenant_id |  name   | Lease Time Remaining in Days
-----------+---------+------------------------------
         2 | Raja    |                          778
         1 | Ani     |                         1509
         4 | Bhashu  |                         1995
         5 | Bibek   |                         1418
         3 | Sarthak |                         2787
(5 rows)


exam=# select t.tenant_id, t.name, sum(p.payment_amount)
exam-# from tenant t
exam-# left outer join lease l on t.tenant_id = l.tenant_id
exam-# left outer join payment p on l.lease_id = p.lease_id
exam-# group by t.tenant_id
exam-# having sum(p.payment_amount) > 2000.00;
 tenant_id |  name   |    sum
-----------+---------+-----------
         5 | Bibek   | 135000.00
         4 | Bhashu  |  60000.00
         2 | Raja    |  90000.00
         1 | Ani     |  45000.00
         3 | Sarthak |  30000.00
(5 rows)


exam=# select t.tenant_id, t.name, sum(p.payment_amount)
exam-# from tenant t
exam-# left outer join lease l on t.tenant_id = l.tenant_id
exam-# left outer join payment p on l.lease_id = p.lease_id
exam-# group by t.tenant_id
exam-# having sum(p.payment_amount) > 2000.00
exam-# order by sum(p.payment_amount) desc;
 tenant_id |  name   |    sum
-----------+---------+-----------
         5 | Bibek   | 135000.00
         2 | Raja    |  90000.00
         4 | Bhashu  |  60000.00
         1 | Ani     |  45000.00
         3 | Sarthak |  30000.00
(5 rows)


exam=# select t.tenant_id, t.name, sum(p.payment_amount) as "Paid more than 2000.00"
exam-# from tenant t
exam-# left outer join lease l on t.tenant_id = l.tenant_id
exam-# left outer join payment p on l.lease_id = p.lease_id
exam-# group by t.tenant_id
exam-# having sum(p.payment_amount) > 2000.00
exam-# order by sum(p.payment_amount) desc;
 tenant_id |  name   | Paid more than 2000.00
-----------+---------+------------------------
         5 | Bibek   |              135000.00
         2 | Raja    |               90000.00
         4 | Bhashu  |               60000.00
         1 | Ani     |               45000.00
         3 | Sarthak |               30000.00
(5 rows)


exam=# select tenant_id, name from tenant where lease_id in
exam-# (select lease_id, sum(payment_amount) from payment group by lease_id having sum(payment_amount) > 2000.00);
ERROR:  column "lease_id" does not exist
LINE 1: select tenant_id, name from tenant where lease_id in
                                                 ^
exam=# select tenant_id, name from tenant where tenant_id in
exam-# (select tenant_id from lease where lease_id in
exam(#   (select lease_id from payment group by lease_id having sum(payment_amount) > 2000.00));
 tenant_id |  name
-----------+---------
         1 | Ani
         2 | Raja
         3 | Sarthak
         4 | Bhashu
         5 | Bibek
(5 rows)


exam=# update table tenant set contact_info = 'example@gmail.com';
ERROR:  syntax error at or near "table"
LINE 1: update table tenant set contact_info = 'example@gmail.com';
               ^
exam=# update tenant set contact_info = 'example@gmail.com';
UPDATE 5
exam=# select tenant_id, name from tenant where contact_info like '%gmail.com';
 tenant_id |  name
-----------+---------
         1 | Ani
         2 | Raja
         3 | Sarthak
         4 | Bhashu
         5 | Bibek
(5 rows)


exam=# select tenant_id, name, contact_info from tenant where contact_info like '%gmail.com';
 tenant_id |  name   |   contact_info
-----------+---------+-------------------
         1 | Ani     | example@gmail.com
         2 | Raja    | example@gmail.com
         3 | Sarthak | example@gmail.com
         4 | Bhashu  | example@gmail.com
         5 | Bibek   | example@gmail.com
(5 rows)


exam=# select location, avg(rent) as "Average Rent" from apartment group by location order by avg(rent) asc;
    location    |      Average Rent
----------------+------------------------
 Rajinder Nagar | 10000.0000000000000000
 Kuruchikuppam  | 15000.0000000000000000
 Rainbow Nagar  |     20000.000000000000
 Anna Salai     |     30000.000000000000
 Kharagpur      |     45000.000000000000
(5 rows)


exam=# update tenant set contact_info = 'ani@gmail.com' where name = 'Ani';
UPDATE 1
exam=# update tenant set contact_info = 'bhashu@gmail.com' where name = 'Bhashu';
UPDATE 1
exam=# update tenant set contact_info = 'raja@hotmail.com' where name = 'Raja';
UPDATE 1
exam=# update tenant set contact_info = 'sarthak@hotmail.com' where name = 'Sarthak';
UPDATE 1
exam=# update tenant set contact_info = 'bibek@gmail.com' where name = 'Bibek';
UPDATE 1
exam=#