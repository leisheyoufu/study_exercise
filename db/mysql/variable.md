
select user,host from mysql.user;
show variables like 'sql_mode';
show global status like 'uptime';
select version();
show variables like '%innodb_data_file_path%';
show variables like '%innodb_file_per_table%' ;
show variables like 'gtid_mode';
show variables like '%server_id%'
show binary logs;
show variables like '%time_zone%';
set time_zone='+8:00';
SET names utf8mb4
set global secure_file_priv=''
reset master status
show table status where comment='view';
show variables like 'character\_set\_%';

show variables like "%expire_logs%"; // binlog 过期时间
select concat(round(sum(DATA_LENGTH/1024/1024),2),'MB') as data  from information_schema.TABLES;

set innodb_strict_mode  = 0 // Row size too large (> 8126)

## Reference
[mysql5.7 timestamp not null](https://stackoverflow.com/questions/9192027/invalid-default-value-for-create-date-timestamp-field)