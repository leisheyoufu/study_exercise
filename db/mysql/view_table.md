show full tables where Table_type = 'BASE TABLE'; // mysql查看所有的基本表(不包含视图)
SHOW FULL TABLES WHERE Table_type = 'VIEW'  // MySQL查看库中所有视图的语句

COALESCE(LOWER(CONV(BIT_XOR(CAST(CRC32(<column>) AS UNSIGNED)), 10, 16)), 0)
select CONSTRAINT_SCHEMA,TABLE_NAME,UNIQUE_CONSTRAINT_SCHEMA,REFERENCED_TABLE_NAME,UPDATE_RULE,DELETE_RULE from information_schema.referential_constraints;
alter table <table> comment '修改后的表的注释';
select concat(round(sum(DATA_LENGTH/1024/1024),2),'MB') as data  from information_schema.TABLES WHERE TABLE_SCHEMA='<db name>' AND TABLE_NAME='<table name>'; // 表占用空间大小



<!-- 查询myisam表-->
select table_schema as database_name,
       table_name
from information_schema.tables tab
where engine = 'MyISAM'
      and table_type = 'BASE TABLE'
      and table_schema not in ('information_schema', 'sys',
                               'performance_schema','mysql')
      -- and table_schema = 'your database name' 
order by table_schema,
         table_name;

<!-- 主键唯一键的表 -->
select table_schema,table_name from information_schema.tables where ((table_schema,table_name) not in(
select distinct table_schema,table_name from information_schema.columns where COLUMN_KEY='PRI')
or (table_schema,table_name) in ( select distinct table_schema,table_name from information_schema.columns ))
and table_schema not in ('sys','mysql','information_schema','performance_schema')

<!-- privilege -->
SELECT
    IF(table_name='user','Global',IF(table_name='db','Database','Table')) priv_level,
    REPLACE(LEFT(column_name,LENGTH(column_name) - 5),'_',' ') priv_type
    FROM (SELECT table_name,column_name FROM information_schema.columns
    WHERE table_schema='mysql' AND table_name IN ('user','db','tables_priv')
    AND column_name LIKE '%\_priv') AAA
    ORDER BY table_name='user' DESC,table_name,column_name;

<!-- myisam fix table -->
SELECT TABLE_SCHEMA, TABLE_NAME, ROW_FORMAT FROM INFORMATION_SCHEMA.TABLES WHERE (ROW_FORMAT='Fixed' OR CREATE_OPTIONS like '%row_format=FIXED%');