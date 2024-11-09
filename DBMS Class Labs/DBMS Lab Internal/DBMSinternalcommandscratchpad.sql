create table dispatch (
desp_id int PRIMARY key,
time timestamp,
date date,
item_id int references product(item_id)
);

CREATE TABLE customer_order (
    invoice_no SERIAL PRIMARY KEY,
    order_date DATE NOT NULL,
    quantity INT NOT NULL, 
    customer_no INT REFERENCES customer(customer_no),
    item_id INT,
    FOREIGN KEY (item_id) REFERENCES product(item_id)
);

alter table item rename product;

insert into customer values
(1, 'Bob', '2000-01-05', 'timbactoo'),
(2, 'Tom', '2001-02-06', 'timbactoo'),
(3, 'Ani', '2002-03-07', 'timbactoo'),
(4, 'Bashu', '2003-04-08', 'timbactoo'),
(5, 'Raja', '2004-05-09', 'timbactoo');

insert into product values
(1, 'Car', 300000),
(2, 'Truck', 50000),
(3, 'Bike', 4000),
(4, 'Jet', 500000),
(5, 'Yacht', 800000);

insert into customer_order values
(1, '2024-01-05', 10, 3, 4),
(2, '2024-02-06', 5, 1, 3),
(3, '2024-03-07', 4, 2, 5),
(4, '2024-04-08', 12, 4, 2),
(5, '2024-05-09', 15, 5, 1);

insert into dispatch values 
(1, '2025-02-05 15:52:21', '2025-02-05', 3),
(2, '2025-03-05 15:52:21', '2025-03-05', 4),
(3, '2025-04-05 15:52:21', '2025-04-05', 5),
(4, '2025-05-05 15:52:21', '2025-05-05', 1),
(5, '2025-06-05 15:52:21', '2025-06-05', 2);

select customer_order.invoice_no, customer_order.order_date, customer_order.quantity, customer_order.customer_no, customer_order.item_id,
  product.item_name, product.unit_price from customer_order left outer join product on customer_order.item_id = product.item_id;


create view dispatch_view as 
(select customer.customer_name, customer.customer_address, customer_order.invoice_no 
from customer left outer join customer_order
on customer.customer_no = customer_order.customer_no);

SELECT item_name from item WHERE item_name LIKE "A%";

select count(*) from dispatch WHERE date >= '2024-11-07';

