## Enable binlog

vim /etc/mysql/mysql.conf.d/mysqld.cnf
```
[mysqld]
#设置日志格式
binlog_format = row  #  statement, row, mixed
#设置日志路径，注意路经需要mysql用户有权限写
log-bin = /var/lib/mysql/binlog
#设置binlog清理时间
expire_logs_days = 7
#binlog每个日志文件大小
max_binlog_size = 100m
#binlog缓存大小
binlog_cache_size = 4m
#最大binlog缓存大小
max_binlog_cache_size = 100m
# very important
server-id = 112345
```
Can debug mysql configuration options with the following command
/usr/sbin/mysqld --log-error-verbosity=2 --validate-config --read_only=s --transaction_read_only=10

Check if binlog is enabled
```
mysql> show binary logs;
+---------------+-----------+
| Log_name      | File_size |
+---------------+-----------+
| binlog.000001 |       177 |
| binlog.000002 |       177 |
| binlog.000003 |       154 |
+---------------+-----------+
3 rows in set (0.00 sec)

mysql> show variables like '%log_bin%';
+---------------------------------+-----------------------------+
| Variable_name                   | Value                       |
+---------------------------------+-----------------------------+
| log_bin                         | ON                          |
| log_bin_basename                | /var/lib/mysql/binlog       |
| log_bin_index                   | /var/lib/mysql/binlog.index |
| log_bin_trust_function_creators | OFF                         |
| log_bin_use_v1_row_events       | OFF                         |
| sql_log_bin                     | ON                          |
+---------------------------------+-----------------------------+
6 rows in set (0.00 sec)
mysql> show binlog events in 'mysql-bin.000074';

```
## Test binlog
```
create database binlogdb default character set utf8mb4;

use binlogdb;
create table `t1` (
  `id` int(11) default null,
  `name` varchar(20) default null
) engine=innodb default charset=utf8mb4;

insert into t1(id,name) select 101,'tome101';
insert into t1(id,name) select 102,'tome102';
insert into t1(id,name) select 103,'tome103';
insert into t1(id,name) select 104,'tome104';
insert into t1(id,name) select 105,'tome105';
insert into t1(id,name) select 106,'tome106';
insert into t1(id,name) select 107,'tome107';
insert into t1(id,name) select 108,'tome108';

update t1 set name='jack101' where id=101;
update t1 set name='jack103' where id=103;
update t1 set name='jack105' where id=105;

delete from t1 where id=102;
delete from t1 where id=104;
delete from t1 where id=106;
```
mysql> flush logs; // 可以手动刷新日志，生成一个新的binlog文件

## Work with mysqlbinlog
mysql> show master status;
+---------------+----------+--------------+------------------+-------------------+
| File          | Position | Binlog_Do_DB | Binlog_Ignore_DB | Executed_Gtid_Set |
+---------------+----------+--------------+------------------+-------------------+
| binlog.000003 |     2800 |              |                  |                   |
+---------------+----------+--------------+------------------+-------------------+

mysqlbinlog /var/lib/mysql/binlog.000003
mysqlbinlog --no-defaults --database=binlogdb  --start-datetime='2020-06-28 00:00:00' --stop-datetime='2020-06-29 15:00:00'  /var/lib/mysql/binlog.000003 | more
可以控制输出语句输出base64编码的BINLOG语句;decode-rows：选项将把基于行的事件解码成一个SQL语句
mysqlbinlog  --no-defaults --database=binlogdb  --base64-output=decode-rows -v --start-datetime='2020-06-28 00:00:00' --stop-datetime='2020-06-29 15:00:00'  /var/lib/mysql/binlog.000003 | more
根据pos查询
mysqlbinlog  --no-defaults --database=binlogdb  --base64-output=decode-rows -v --start-position=154 --stop-position=970 /var/lib/mysql/binlog.000004

The output is like:
```
# at 8065298
#200708 12:54:33 server id 9527  end_log_pos 8065462 CRC32 0xf00b199d 	Update_rows: table id 108 flags: STMT_END_F
### UPDATE `binlogdb`.`sales`
### WHERE
###   @1=2
###   @2='name'
###   @3='AAAAAAAA'
###   @4=1594212871
###   @5=1594128201
###   @6=1594212875
### SET
###   @1=2
###   @2='name'
###   @3='BBBBBBBB'
###   @4=1594212873
###   @5=1594128201
###   @6=1594212877
```

## Clear binlog manually
purge master logs to BINLOGNAME;
purge master logs before DATE;