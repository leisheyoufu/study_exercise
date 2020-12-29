## fltrw
这个命令是全局读锁定，执行了命令之后所有库所有表都被锁定只读。一般都是用在数据库联机备份，这个时候数据库的写操作将被阻塞，读操作顺利进行。
flush table with read lock

步骤一、请求获得相关类型的 MDL lock,这里我们暂时称之为 FTWRL_MDL_LOCK.
步骤二、清空query cache中的内容（当前应该很少有人开启这个功能了）
步骤三、FLUSH TABLES,将当前所有打开的table的fd关闭
步骤四、请求获得全局table-level lock
步骤五、上全局COMMIT锁(make_global_read_lock_block_commit)


解锁的语句是unlock tables

## 表级锁定
LOCK TABLES tbl_name [AS alias] {READ [LOCAL] | [LOW_PRIORITY] WRITE}


MySQL [sbtest]> lock table sbtest1 write;

另一个线程无法插入
insert sbtest1(id,k,c,pad) values(898, 33, "ddd","aaa");

```
MySQL [(none)]> show open tables from sbtest;
+----------+---------+--------+-------------+
| Database | Table   | In_use | Name_locked |
+----------+---------+--------+-------------+
| sbtest   | sbtest3 |      0 |           0 |
| sbtest   | sbtest2 |      0 |           0 |
| sbtest   | sbtest1 |      0 |           0 |
+----------+---------+--------+-------------+
MySQL [sbtest]> lock table sbtest2 read;
Query OK, 0 rows affected (0.00 sec)

MySQL [sbtest]> show open tables from sbtest;
+----------+---------+--------+-------------+
| Database | Table   | In_use | Name_locked |
+----------+---------+--------+-------------+
| sbtest   | sbtest3 |      0 |           0 |
| sbtest   | sbtest2 |      1 |           0 |
| sbtest   | sbtest1 |      0 |           0 |
+----------+---------+--------+-------------+
MySQL [sbtest]> insert sbtest2(id,k,c,pad) values(11898, 33, "ddd","aaa");   // 无法写入
```
show variables like "%gtid%";


mysql_get_server_version
## Reference
[为什么要使用FTWRL](https://www.cnblogs.com/conanwang/p/6925108.html)
[MySQL LOCK TABLES 与UNLOCK TABLES]https://blog.csdn.net/zyz511919766/article/details/16342003
