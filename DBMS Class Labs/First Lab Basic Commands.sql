show databases;
use world;
show tables;

select * from city where countrycode = "IND";
select sum(population) as "Total Population" from city where countrycode = "IND";