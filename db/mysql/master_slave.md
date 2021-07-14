show slave status\G
Slave_IO_Running: Yes
Slave_SQL_Running: No

FLUSH TABLES WITH READ LOCK;
SET SESSION TRANSACTION ISOLATION LEVEL REPEATABLE READ;
START TRANSACTION /*!40108 WITH CONSISTENT SNAPSHOT */;
UNLOCK TABLES /* FTWRL */;
show open tables // 检查锁状态

select /*!40001 SQL_NO_CACHE */ * from db_test1.t_alter_table limit 10;
select COLUMN_NAME, DATA_TYPE from information_schema.COLUMNS where TABLE_SCHEMA='db_test1' and TABLE_NAME='t_alter_table'
