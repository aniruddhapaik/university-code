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
