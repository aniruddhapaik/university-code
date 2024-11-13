-- Show the total number of orders placed by each customer. Display the customer name and order count.
select c.customer_name, count(c.customer_no) 
from customer c 
right join customer_order co on c.customer_no = co.customer_no 
group by c.customer_no;


-- Calculate the total sales (quantity * unit_price) for each product. Show product name and total sales amount.
select p.item_name, sum(quantity)*p.unit_price as "total sales" 
from customer_order co 
left join product p on co.item_id = p.item_id 
group by p.item_id;

-- Find the total quantity of each product sold. Return the product name and the total quantity ordered.
select p.item_name, sum(quantity) AS "Total Quantity Ordered" 
from customer_order co 
left join product p on co.item_id = p.item_id 
group by p.item_id 
order by p.item_id;

-- List all orders along with the customer and product details for each order. 
-- Show customer name, product name, order date, and quantity.
select c.customer_name, p.item_name, co.order_date, co.quantity 
from customer_order co 
left join product p on co.item_id = p.item_id 
left join customer c on co.customer_no = c.customer_no 
order by c.customer_no asc;

-- List each product that has a total order quantity of more than 10. 
-- Show the product name and total ordered quantity.
select p.item_name, sum(co.quantity) as "total quantity ordered" 
from customer_order co 
left join product p on co.item_id = p.item_id 
group by p.item_id 
having sum(co.quantity) > 10;

-- Find the names of customers who have placed at least one order.
select c.customer_name 
from customer c 
where c.customer_no 
in (select customer_no from customer_order);

-- Retrieve the details of the product with the highest unit price.
select item_name, unit_price 
from product 
where unit_price = (select max(unit_price) from product);

-- Get the names of customers who haven’t placed any orders.
select c.customer_name 
from customer c 
where c.customer_no 
not in (select distinct customer_no from customer_order);

select c.customer_name, d.date, p.item_name, co.quantity, d.invoice_no from customer_order co
right outer join dispatch d on co.invoice_no = d.invoice_no
left outer join customer c on co.customer_no = c.customer_no
left outer join product p on d.item_id = p.item_id
WHERE d.date >= NOW() - INTERVAL '30 days' AND d.date <= NOW();

select p.item_name, sum(co.quantity), max(d.date) from product p 
right outer join dispatch d on p.item_id = d.item_id
left outer join customer_order co on d.invoice_no = co.invoice_no
where d.date >= NOW() - INTERVAL '3 months' AND d.date <= NOW()
group by p.item_id;

