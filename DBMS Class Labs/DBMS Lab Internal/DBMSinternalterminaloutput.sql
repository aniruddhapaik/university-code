Server [localhost]:
Database [postgres]: labtest
Port [5432]:
Username [postgres]: aniruddha
Password for user aniruddha:

psql (17.0)
WARNING: Console code page (437) differs from Windows code page (1252)
         8-bit characters might not work correctly. See psql reference
         page "Notes for Windows users" for details.
Type "help" for help.

labtest=# \l
                                                                List of databases
    Name     |   Owner   | Encoding | Locale Provider |      Collate       |       Ctype        | Locale | ICU Rules |     Access privileges
-------------+-----------+----------+-----------------+--------------------+--------------------+--------+-----------+----------------------------
 constraints | aniruddha | UTF8     | libc            | English_India.1252 | English_India.1252 |        |           |
 labtest     | aniruddha | UTF8     | libc            | English_India.1252 | English_India.1252 |        |           |
 postgres    | postgres  | UTF8     | libc            | English_India.1252 | English_India.1252 |        |           |
 template0   | postgres  | UTF8     | libc            | English_India.1252 | English_India.1252 |        |           | =c/postgres               +
             |           |          |                 |                    |                    |        |           | postgres=CTc/postgres
 template1   | postgres  | UTF8     | libc            | English_India.1252 | English_India.1252 |        |           | =c/postgres               +
             |           |          |                 |                    |                    |        |           | postgres=CTc/postgres
 university  | aniruddha | UTF8     | libc            | English_India.1252 | English_India.1252 |        |           | =Tc/aniruddha             +
             |           |          |                 |                    |                    |        |           | aniruddha=C*T*c*/aniruddha+
             |           |          |                 |                    |                    |        |           | postgres=C*T*c*/aniruddha
(6 rows)


labtest=# \dt
Did not find any relations.
labtest=# \d
Did not find any relations.
labtest=# create table customer (
labtest(# customer_no int primary key,
labtest(# customer_name varchar(40),
labtest(# customer_dob date,
labtest(# customer_address text);
CREATE TABLE
labtest=# create table customer_order(
labtest(# invoice_no INT PRIMARY KEY,
labtest(# order_date date,
labtest(# quantity int not null,
labtest(# customer_no int references customer(customer_no),
labtest(# item_id int);
CREATE TABLE
labtest=# create table item(
labtest(# item_id int primary key,
labtest(# item_name varchar(40),
labtest(# unit_price int);
CREATE TABLE
labtest=# alter table customer_order add constraint item_fkey forein key (item_id) references item (item_id);
ERROR:  syntax error at or near "forein"
LINE 1: ...ter table customer_order add constraint item_fkey forein key...
                                                             ^
labtest=# alter table customer_order add constraint item_fkey foreign key (item_id) references item (item_id);
ALTER TABLE
labtest=# create table dispatch (
labtest(# desp_id int primary key,
labtest(# time timestamp,
labtest(# date date,
labtest(# item_id references item(item_id);
labtest(# )
labtest-# ;
ERROR:  syntax error at or near "references"
LINE 5: item_id references item(item_id);
                ^
labtest=#
labtest=# create table dispatch (
labtest(# desp_id int PRIMARY key,
labtest(# time timestamp,
labtest(# date date,
labtest(# item_id references item(item_id)
labtest(# );
ERROR:  syntax error at or near "references"
LINE 5: item_id references item(item_id)
                ^
labtest=# create table dispatch (
labtest(# desp_id int PRIMARY key,
labtest(# time timestamp,
labtest(# date date,
labtest(# item_id int references item(item_id)
labtest(# );
CREATE TABLE
labtest=# \dt
              List of relations
 Schema |      Name      | Type  |   Owner
--------+----------------+-------+-----------
 public | customer       | table | aniruddha
 public | customer_order | table | aniruddha
 public | dispatch       | table | aniruddha
 public | item           | table | aniruddha
(4 rows)


labtest=# \dl
      Large objects
 ID | Owner | Description
----+-------+-------------
(0 rows)


labtest=# \d
              List of relations
 Schema |      Name      | Type  |   Owner
--------+----------------+-------+-----------
 public | customer       | table | aniruddha
 public | customer_order | table | aniruddha
 public | dispatch       | table | aniruddha
 public | item           | table | aniruddha
(4 rows)


labtest=# \d item
                         Table "public.item"
   Column   |         Type          | Collation | Nullable | Default
------------+-----------------------+-----------+----------+---------
 item_id    | integer               |           | not null |
 item_name  | character varying(40) |           |          |
 unit_price | integer               |           |          |
Indexes:
    "item_pkey" PRIMARY KEY, btree (item_id)
Referenced by:
    TABLE "dispatch" CONSTRAINT "dispatch_item_id_fkey" FOREIGN KEY (item_id) REFERENCES item(item_id)
    TABLE "customer_order" CONSTRAINT "item_fkey" FOREIGN KEY (item_id) REFERENCES item(item_id)


labtest=# alter table item rename product;
ERROR:  syntax error at or near ";"
LINE 1: alter table item rename product;
                                       ^
labtest=# rename item to product;
ERROR:  syntax error at or near "rename"
LINE 1: rename item to product;
        ^
labtest=# alter table item rename item to product;
ERROR:  column "item" does not exist
labtest=# alter table item rename to product;
ALTER TABLE
labtest=# insert into customer values
labtest-# (1, 'Bob', '2000-01-05', 'timbactoo'),
labtest-# (2, 'Tom', '2001-02-06', 'timbactoo'),
labtest-# (3, 'Ani', '2002-03-07', 'timbactoo'),
labtest-# (4, 'Bashu', '2003-04-08', 'timbactoo'),
labtest-# (5, 'Raja', '2004-05-09', 'timbactoo');
INSERT 0 5
labtest=# insert into item values
labtest-# (1, 'Car', 300000),
labtest-# (2, 'Truck', 50000),
labtest-# (3, 'Bike', 4000),
labtest-# (4, 'Jet', 500000),
labtest-# (5, 'Yacht', 800000);
ERROR:  relation "item" does not exist
LINE 1: insert into item values
                    ^
labtest=# insert into product values
labtest-# (1, 'Car', 300000),
labtest-# (2, 'Truck', 50000),
labtest-# (3, 'Bike', 4000),
labtest-# (4, 'Jet', 500000),
labtest-# (5, 'Yacht', 800000);
INSERT 0 5
labtest=# \d customer_order
             Table "public.customer_order"
   Column    |  Type   | Collation | Nullable | Default
-------------+---------+-----------+----------+---------
 invoice_no  | integer |           | not null |
 order_date  | date    |           |          |
 quantity    | integer |           | not null |
 customer_no | integer |           |          |
 item_id     | integer |           |          |
Indexes:
    "customer_order_pkey" PRIMARY KEY, btree (invoice_no)
Foreign-key constraints:
    "customer_order_customer_no_fkey" FOREIGN KEY (customer_no) REFERENCES customer(customer_no)
    "item_fkey" FOREIGN KEY (item_id) REFERENCES product(item_id)


labtest=# insert into customer_order values
labtest-# (1, '2024-01-05', 10, 3, 4),
labtest-# (2, '2024-02-06', 5, 1, 3),
labtest-# (3, '2024-03-07', 4, 2, 5),
labtest-# (4, '2024-04-08', 12, 4, 2),
labtest-# (5, '2024-05-09', 15, 5, 1);
INSERT 0 5
labtest=# select * from dispatch;
 desp_id |           time            |    date    | item_id
---------+---------------------------+------------+---------
       1 | 2024-11-07 15:52:21.30146 | 2025-01-05 |       3
(1 row)


labtest=# create table dispatch (
labtest(# desp_id int PRIMARY key,
labtest(# time timestamp,
labtest(# date date,
labtest(# item_id int references item(item_id)
labtest(# );
ERROR:  relation "item" does not exist
labtest=# create table dispatch (
labtest(# desp_id int PRIMARY key,
labtest(# time timestamp,
labtest(# date date,
labtest(# item_id int references product(item_id)
labtest(# );
CREATE TABLE
labtest=# insert into dispatch values
labtest-# (1, '2025-02-05 15:52:21', '2025-02-05', 3),
labtest-# (2, '2025-03-05 15:52:21', '2025-03-05', 4),
labtest-# (3, '2025-04-05 15:52:21', '2025-04-05', 5),
labtest-# (4, '2025-05-05 15:52:21', '2025-05-05', 1),
labtest-# (5, '2025-06-05 15:52:21', '2025-06-05', 2);
INSERT 0 5
labtest=# select * from dispatch;
 desp_id |        time         |    date    | item_id
---------+---------------------+------------+---------
       1 | 2025-02-05 15:52:21 | 2025-02-05 |       3
       2 | 2025-03-05 15:52:21 | 2025-03-05 |       4
       3 | 2025-04-05 15:52:21 | 2025-04-05 |       5
       4 | 2025-05-05 15:52:21 | 2025-05-05 |       1
       5 | 2025-06-05 15:52:21 | 2025-06-05 |       2
(5 rows)


labtest=# select * from customer where customer_no = (select customer_no from customer_order order by quantity desc limit 1);
 customer_no | customer_name | customer_dob | customer_address
-------------+---------------+--------------+------------------
           5 | Raja          | 2004-05-09   | timbactoo
(1 row)


labtest=# \d product
                       Table "public.product"
   Column   |         Type          | Collation | Nullable | Default
------------+-----------------------+-----------+----------+---------
 item_id    | integer               |           | not null |
 item_name  | character varying(40) |           |          |
 unit_price | integer               |           |          |
Indexes:
    "item_pkey" PRIMARY KEY, btree (item_id)
Referenced by:
    TABLE "dispatch" CONSTRAINT "dispatch_item_id_fkey" FOREIGN KEY (item_id) REFERENCES product(item_id)
    TABLE "customer_order" CONSTRAINT "item_fkey" FOREIGN KEY (item_id) REFERENCES product(item_id)


labtest=#
labtest=# select customer_order.invoice_no, customer_order.order_date, customer_order.quantity, customer_order.customer_no, customer_order.item_id,
labtest-#   product.item_name, product.unit_price from customer_order left outer product on customer_order.item_id = product.item_id;
ERROR:  syntax error at or near "product"
LINE 2: ...product.unit_price from customer_order left outer product on...
                                                             ^
labtest=#   product.item_name, product.unit_price from customer_order left outer product on customer_order.item_id = product.item_id;
ERROR:  syntax error at or near "product"
LINE 1: product.item_name, product.unit_price from customer_order le...
        ^
labtest=# select customer_order.invoice_no, customer_order.order_date, customer_order.quantity, customer_order.customer_no, customer_order.item_id,
labtest-#   product.item_name, product.unit_price from customer_order left outer join product on customer_order.item_id = product.item_id;
 invoice_no | order_date | quantity | customer_no | item_id | item_name | unit_price
------------+------------+----------+-------------+---------+-----------+------------
          1 | 2024-01-05 |       10 |           3 |       4 | Jet       |     500000
          2 | 2024-02-06 |        5 |           1 |       3 | Bike      |       4000
          3 | 2024-03-07 |        4 |           2 |       5 | Yacht     |     800000
          4 | 2024-04-08 |       12 |           4 |       2 | Truck     |      50000
          5 | 2024-05-09 |       15 |           5 |       1 | Car       |     300000
(5 rows)


labtest=# create view Dispatch as
labtest-# (select customer.customer_name, customer.customer_address, customer_order.invoice_no
labtest(# from customer left outer join customer_order
labtest(# on customer.customer_no = customer_order.customer_no);
ERROR:  relation "dispatch" already exists
labtest=# create view dispatch_view as
labtest-# (select customer.customer_name, customer.customer_address, customer_order.invoice_no
labtest(# from customer left outer join customer_order
labtest(# on customer.customer_no = customer_order.customer_no);
CREATE VIEW
labtest=# select * from dispatch_view;
 customer_name | customer_address | invoice_no
---------------+------------------+------------
 Ani           | timbactoo        |          1
 Bob           | timbactoo        |          2
 Tom           | timbactoo        |          3
 Bashu         | timbactoo        |          4
 Raja          | timbactoo        |          5
(5 rows)


labtest=# SELECT item_name from item WHERE item_name LIKE "A%";
ERROR:  relation "item" does not exist
LINE 1: SELECT item_name from item WHERE item_name LIKE "A%";
                              ^
labtest=# SELECT item_name from product WHERE item_name LIKE "A%";
ERROR:  column "A%" does not exist
LINE 1: SELECT item_name from product WHERE item_name LIKE "A%";
                                                           ^
labtest=# SELECT item_name from product WHERE item_name LIKE 'A%';
 item_name
-----------
(0 rows)


labtest=# select count(*) from dispatch WHERE date >= '2024-11-07';
 count
-------
     5
(1 row)


labtest=# select * from dispatch;
 desp_id |        time         |    date    | item_id
---------+---------------------+------------+---------
       1 | 2025-02-05 15:52:21 | 2025-02-05 |       3
       2 | 2025-03-05 15:52:21 | 2025-03-05 |       4
       3 | 2025-04-05 15:52:21 | 2025-04-05 |       5
       4 | 2025-05-05 15:52:21 | 2025-05-05 |       1
       5 | 2025-06-05 15:52:21 | 2025-06-05 |       2
(5 rows)


labtest=# select count(*) from dispatch WHERE date = '2024-11-07';
 count
-------
     0
(1 row)


labtest=# SELECT item_name from product WHERE item_name LIKE 'A%';
     item_name
--------------------
 Apacher Helicopter
(1 row)


labtest=# insert into dispatch values (6, '2024-11-07 15:00:00', '2024-11-07', 6);
INSERT 0 1
labtest=# select count(*) from dispatch WHERE date = '2024-11-07';
 count
-------
     1
(1 row)


labtest=# \dl
      Large objects
 ID | Owner | Description
----+-------+-------------
(0 rows)


labtest=# \d
              List of relations
 Schema |      Name      | Type  |   Owner
--------+----------------+-------+-----------
 public | customer       | table | aniruddha
 public | customer_order | table | aniruddha
 public | dispatch       | table | aniruddha
 public | dispatch_view  | view  | aniruddha
 public | product        | table | aniruddha
(5 rows)


labtest=# \d customer
                          Table "public.customer"
      Column      |         Type          | Collation | Nullable | Default
------------------+-----------------------+-----------+----------+---------
 customer_no      | integer               |           | not null |
 customer_name    | character varying(40) |           |          |
 customer_dob     | date                  |           |          |
 customer_address | text                  |           |          |
Indexes:
    "customer_pkey" PRIMARY KEY, btree (customer_no)
Referenced by:
    TABLE "customer_order" CONSTRAINT "customer_order_customer_no_fkey" FOREIGN KEY (customer_no) REFERENCES customer(customer_no)


labtest=# \d customer_order
             Table "public.customer_order"
   Column    |  Type   | Collation | Nullable | Default
-------------+---------+-----------+----------+---------
 invoice_no  | integer |           | not null |
 order_date  | date    |           |          |
 quantity    | integer |           | not null |
 customer_no | integer |           |          |
 item_id     | integer |           |          |
Indexes:
    "customer_order_pkey" PRIMARY KEY, btree (invoice_no)
Foreign-key constraints:
    "customer_order_customer_no_fkey" FOREIGN KEY (customer_no) REFERENCES customer(customer_no)
    "item_fkey" FOREIGN KEY (item_id) REFERENCES product(item_id)


labtest=# \d product
                       Table "public.product"
   Column   |         Type          | Collation | Nullable | Default
------------+-----------------------+-----------+----------+---------
 item_id    | integer               |           | not null |
 item_name  | character varying(40) |           |          |
 unit_price | integer               |           |          |
Indexes:
    "item_pkey" PRIMARY KEY, btree (item_id)
Referenced by:
    TABLE "dispatch" CONSTRAINT "dispatch_item_id_fkey" FOREIGN KEY (item_id) REFERENCES product(item_id)
    TABLE "customer_order" CONSTRAINT "item_fkey" FOREIGN KEY (item_id) REFERENCES product(item_id)


labtest=# \d dispatch
                        Table "public.dispatch"
 Column  |            Type             | Collation | Nullable | Default
---------+-----------------------------+-----------+----------+---------
 desp_id | integer                     |           | not null |
 time    | timestamp without time zone |           |          |
 date    | date                        |           |          |
 item_id | integer                     |           |          |
Indexes:
    "dispatch_pkey" PRIMARY KEY, btree (desp_id)
Foreign-key constraints:
    "dispatch_item_id_fkey" FOREIGN KEY (item_id) REFERENCES product(item_id)


labtest=#