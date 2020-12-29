create database if not exists `func`;
CREATE TABLE toku (
column_a int,
column_b int,
column_c int,
PRIMARY KEY index_a (column_a),
CLUSTERING KEY index_b (column_b)) ENGINE = TokuDB;

insert into toku(column_a,column_b,column_c) values(1,2,3);