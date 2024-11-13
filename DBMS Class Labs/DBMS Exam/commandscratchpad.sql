create table tenant (
tenant_id int primary key,
name varchar(50),
contact_info varchar(50)
);

create table apartment (
apartment_id int primary key,
location varchar(50),
rent decimal(10,2)
);

create table lease (
lease_id int primary key,
tenant_id int references tenant(tenant_id),
apartment_id int references apartment(apartment_id),
start_date date,
end_date date
);
-- added security_deposit decimal(10,2) later

create table payment (
payment_id int primary key,
lease_id int references lease(lease_id),
payment_amount decimal(10,2),
payment_date date
);

insert into tenant (tenant_id, name, contact_info) values
(1, 'Ani', '1234567890'),
(2, 'Raja', '0987654321'),
(3, 'Sarthak', '1234509876'),
(4, 'Bhashu', '0987612345'),
(5, 'Bibek', '5432167890');

insert into apartment (apartment_id, location, rent) values
(1, 'Rainbow Nagar', 20000.00),
(2, 'Kuruchikuppam', 15000.00),
(3, 'Anna Salai', 30000.00),
(4, 'Kharagpur', 45000.00),
(5, 'Rajinder Nagar', 10000.00);

insert into lease (lease_id, tenant_id, apartment_id, start_date, end_date, security_deposit) values
(1, 2, 3, '2024-01-01', '2026-12-31', 15000.00),
(2, 1, 2, '2022-01-01', '2028-12-31', 7500.00),
(3, 4, 1, '2020-05-01', '2030-05-01', 10000.00),
(4, 5, 4, '2022-10-01', '2028-10-01', 22500.00),
(5, 3, 5, '2021-07-01', '2032-07-01', 5000.00);

insert into payment (payment_id, lease_id, payment_amount, payment_date) values
(1, 3, 20000.00, '2020-05-01'),
(2, 1, 30000.00, '2024-01-01'),
(3, 2, 15000.00, '2022-01-01'),
(4, 5, 10000.00, '2021-07-01'),
(5, 4, 45000.00, '2022-10-01'),
(6, 3, 20000.00, '2020-06-01'),
(7, 1, 30000.00, '2024-02-01'),
(8, 2, 15000.00, '2022-02-01'),
(9, 5, 10000.00, '2021-08-01'),
(10, 4, 45000.00, '2022-11-01'),
(11, 3, 20000.00, '2020-07-01'),
(12, 1, 30000.00, '2024-03-01'),
(13, 2, 15000.00, '2022-03-01'),
(14, 5, 10000.00, '2021-09-01'),
(15, 4, 45000.00, '2022-12-01');

alter table lease add column security_deposit decimal(10,2);

select a.apartment_id, a.location, sum(p.payment_amount) as "Total rent collected by apartment" from apartment a 
left outer join lease l on a.apartment_id = l.apartment_id
left outer join payment p on l.lease_id = p.lease_id
group by a.apartment_id;

select t.*, a.*, l.end_date - l.start_date as Lease_Duration_in_days
from tenant t 
left outer join lease l on t.tenant_id = l.tenant_id 
left outer join apartment a on l.apartment_id = a.apartment_id;

create view Tenant_details_Payment_history as (
select t.*, a.apartment_id, a.location, p.payment_amount, p.payment_date
from payment p 
left outer join lease l on p.lease_id = l.lease_id
left outer join apartment a on l.apartment_id = a.apartment_id
left outer join tenant t on l.tenant_id = t.tenant_id
order by t.tenant_id, p.payment_date asc);

select t.tenant_id, t.name, l.end_date - current_date as "Lease Time Remaining in Days"
from tenant t 
LEFT outer join lease l on t.tenant_id = l.tenant_id;

select t.tenant_id, t.name, sum(p.payment_amount) as "Paid more than 2000.00"
from tenant t
left outer join lease l on t.tenant_id = l.tenant_id
left outer join payment p on l.lease_id = p.lease_id
group by t.tenant_id
having sum(p.payment_amount) > 2000.00
order by sum(p.payment_amount) desc;

select tenant_id, name from tenant 
where tenant_id in 
  (select tenant_id from lease 
  where lease_id in
      (select lease_id from payment group by lease_id having sum(payment_amount) > 2000.00));

select tenant_id, name, contact_info from tenant where contact_info like '%gmail.com';

select location, avg(rent) as "Average Rent" from apartment group by location order by avg(rent) asc;