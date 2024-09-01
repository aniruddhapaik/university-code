\l -- list of databases
\d -- list of tables
\dt -- list of tables

create table student (
    sid SERIAL PRIMARY KEY NOT NULL,
    name VARCHAR(30) NOT NULL,
    state VARCHAR(20)
);
-- or
create table student (
    sid INT GENERATED ALWAYS AS IDENTITY PRIMARY KEY NOT NULL,
    name VARCHAR(30) NOT NULL,
    state VARCHAR(20)
);

ALTER TABLE student
ADD COLUMN sid SERIAL PRIMARY KEY;

alter table student drop constraint student_pkey;

