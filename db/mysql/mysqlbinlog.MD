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

mysqlbinlog --no-defaults --read-from-remote-server --host=127.0.0.1 --user=root --password=xxxxx --port 3319 --skip-gtids --include-gtids 'a36fbe4c-a0d6-11eb-b2e5-0242ac1c0002:56127-56128' mysql-bin.00005

mysqlbinlog --no-defaults --read-from-remote-server --host=127.0.0.1  --user=yuntest --password=xxxx --port 3306 --include-gtids 'c73deb70-75ba-11eb-8769-52540032c10b:9007-9040' --base64-output=AUTO --verbose  mysql-bin.000011

mysqlbinlog --no-defaults --read-from-remote-server --host=127.0.0.1 --user=root --password=xxxx --port 3319 --include-gtids '2582e45b-de04-11eb-a671-0242ac100002:9329' --base64-output=AUTO --verbose  mysql-bin.000003

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

### GTID IN BINLOG
GTID_LOG_EVENT  
```
# at 448
#160818  5:37:32 server id 1  end_log_pos 496 CRC32 0xaeb24aac     GTID [commit=yes]
SET @@SESSION.GTID_NEXT= 'cad449f2-5d4f-11e6-b353-000c29c64704:3'/*!*/;
# at 496
#160818  5:37:32 server id 1  end_log_pos 571 CRC32 0x042ca092     Query    thread_id=2    exec_time=0    error_code=0
SET TIMESTAMP=1471469852/*!*/;
BEGIN
/*!*/;
# at 571
#160818  5:37:32 server id 1  end_log_pos 674 CRC32 0xa35beb37     Query    thread_id=2    exec_time=0    error_code=0
SET TIMESTAMP=1471469852/*!*/;
insert into test.t1 values(2,'b')
/*!*/;
# at 674
#160818  5:37:32 server id 1  end_log_pos 705 CRC32 0x1905d8c6     Xid = 12
COMMIT/*!*/;

mysql> show binlog events in 'mysql-bin.000033';
+------------------+-----+----------------+-----------+-------------+-------------------------------------------------------------------+
| Log_name         | Pos | Event_type     | Server_id | End_log_pos | Info                                                              |
+------------------+-----+----------------+-----------+-------------+-------------------------------------------------------------------+
| mysql-bin.000033 |   4 | Format_desc    |         1 |         120 | Server ver: 5.6.31-log, Binlog ver: 4                             |
| mysql-bin.000033 | 120 | Previous_gtids |         1 |         191 | cad449f2-5d4f-11e6-b353-000c29c64704:1                            |
| mysql-bin.000033 | 191 | Gtid           |         1 |         239 | SET @@SESSION.GTID_NEXT= 'cad449f2-5d4f-11e6-b353-000c29c64704:2' |
| mysql-bin.000033 | 239 | Query          |         1 |         314 | BEGIN                                                             |
| mysql-bin.000033 | 314 | Query          |         1 |         417 | insert into test.t1 values(1,'a')                                 |
| mysql-bin.000033 | 417 | Xid            |         1 |         448 | COMMIT /* xid=11 */                                               |
| mysql-bin.000033 | 448 | Gtid           |         1 |         496 | SET @@SESSION.GTID_NEXT= 'cad449f2-5d4f-11e6-b353-000c29c64704:3' |
| mysql-bin.000033 | 496 | Query          |         1 |         571 | BEGIN                                                             |
| mysql-bin.000033 | 571 | Query          |         1 |         674 | insert into test.t1 values(2,'b')                                 |
| mysql-bin.000033 | 674 | Xid            |         1 |         705 | COMMIT /* xid=12 */                                               |
| mysql-bin.000033 | 705 | Rotate         |         1 |         752 | mysql-bin.000034;pos=4                                            |
+------------------+-----+----------------+-----------+-------------+-------------------------------------------------------------------+
11 rows in set (0.00 sec)
```

PREVIOUS_GTIDS_LOG_EVENT
开启GTID模式后，每个binlog开头都会有一个PREVIOUS_GTIDS_LOG_EVENT事件，它的值是上一个binlog的PREVIOUS_GTIDS_LOG_EVENT+GTID_LOG_EVENT，实际上，在数据库重启的时候，需要重新填充gtid_executed的值，该值即是最新一个binlog的PREVIOUS_GTIDS_LOG_EVENT+GTID_LOG_EVENT。
```
mysql> show binlog events in 'mysql-bin.000033';
+------------------+-----+----------------+-----------+-------------+-------------------------------------------------------------------+
| Log_name         | Pos | Event_type     | Server_id | End_log_pos | Info                                                              |
+------------------+-----+----------------+-----------+-------------+-------------------------------------------------------------------+
| mysql-bin.000033 |   4 | Format_desc    |         1 |         120 | Server ver: 5.6.31-log, Binlog ver: 4                             |
| mysql-bin.000033 | 120 | Previous_gtids |         1 |         191 | cad449f2-5d4f-11e6-b353-000c29c64704:1                            |
| mysql-bin.000033 | 191 | Gtid           |         1 |         239 | SET @@SESSION.GTID_NEXT= 'cad449f2-5d4f-11e6-b353-000c29c64704:2' |
| mysql-bin.000033 | 239 | Query          |         1 |         314 | BEGIN                                                             |
| mysql-bin.000033 | 314 | Query          |         1 |         417 | insert into test.t1 values(1,'a')                                 |
| mysql-bin.000033 | 417 | Xid            |         1 |         448 | COMMIT /* xid=11 */                                               |
| mysql-bin.000033 | 448 | Gtid           |         1 |         496 | SET @@SESSION.GTID_NEXT= 'cad449f2-5d4f-11e6-b353-000c29c64704:3' |
| mysql-bin.000033 | 496 | Query          |         1 |         571 | BEGIN                                                             |
| mysql-bin.000033 | 571 | Query          |         1 |         674 | insert into test.t1 values(2,'b')                                 |
| mysql-bin.000033 | 674 | Xid            |         1 |         705 | COMMIT /* xid=12 */                                               |
| mysql-bin.000033 | 705 | Rotate         |         1 |         752 | mysql-bin.000034;pos=4                                            |
+------------------+-----+----------------+-----------+-------------+-------------------------------------------------------------------+
11 rows in set (0.00 sec)

mysql> show binlog events in 'mysql-bin.000034';
+------------------+-----+----------------+-----------+-------------+------------------------------------------+
| Log_name         | Pos | Event_type     | Server_id | End_log_pos | Info                                     |
+------------------+-----+----------------+-----------+-------------+------------------------------------------+
| mysql-bin.000034 |   4 | Format_desc    |         1 |         120 | Server ver: 5.6.31-log, Binlog ver: 4    |
| mysql-bin.000034 | 120 | Previous_gtids |         1 |         191 | cad449f2-5d4f-11e6-b353-000c29c64704:1-3 |
+------------------+-----+----------------+-----------+-------------+------------------------------------------+
2 rows in set (0.00 sec)
mysql-bin.000033日志中的Previous_gtids是cad449f2-5d4f-11e6-b353-000c29c64704:1，GTID是cad449f2-5d4f-11e6-b353-000c29c64704:2和cad449f2-5d4f-11e6-b353-000c29c64704:3，这样，在下一个日志，即mysql-bin.000034中的Previous_gtids是cad449f2-5d4f-11e6-b353-000c29c64704:1-3。
# at 120
#160818  5:39:38 server id 1  end_log_pos 191 CRC32 0x4e84f3b5     Previous-GTIDs
# cad449f2-5d4f-11e6-b353-000c29c64704:1-3

```

## Clear binlog manually
purge master logs to BINLOGNAME;
purge master logs before DATE;

## Reference
- [MySQL binlog中的事件类型](https://www.cnblogs.com/ivictor/p/5780617.html)