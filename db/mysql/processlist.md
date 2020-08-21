## 查询线程
show processlist;
```
3189 | root | 192.168.0.1:56870  | sbtest | Query            |  210 | User sleep                                                    | select sleep(1),id from sbtest1
```
show variables like 'log_slow_queries';  // 查询是否启用慢sql 日志
show variables like 'long_query_time';  // 查看执行慢于多少秒的SQL会记录到日志文件中
set long_query_time=1; 注： 我设置了1, 也就是执行时间超过1秒的都算慢查询。
select * from sys.session;


其中sys.session视图关联到sys.processlist，而sys.processlist又使用到`performance_schema`.`events_statements_current`。

 Mysql> show variables like “%timeout%”;

+-----------------------------+----------+
| Variable_name              | Value    |
+-----------------------------+----------+
| connect_timeout            | 10      | 
| delayed_insert_timeout      | 300      | 
| innodb_flush_log_at_timeout | 1        | 
| innodb_lock_wait_timeout    | 50      | 
| innodb_rollback_on_timeout  | OFF      | 
| interactive_timeout        | 28800    | 
| lock_wait_timeout          | 31536000 | 
| net_read_timeout            | 30      | 
| net_write_timeout          | 60      | 
| slave_net_timeout          | 3600    | 
| wait_timeout                | 28800    | 
+-----------------------------+----------+
11 rows in set (0.00 sec)

经查询发现原来mysql没有进行过优化，还是原来的默认值：28800（即8个小时）  连接太多
【mysqld】
wait_timeout=120
interactive_timeout=120

注意：要同时设置interactive_timeout和wait_timeout才会生效。


MySQL [sbtest]> show variables like '%connect%';
+-----------------------------------------------+-----------------+
| Variable_name                                 | Value           |
+-----------------------------------------------+-----------------+
| character_set_connection                      | utf8            |
| collation_connection                          | utf8_general_ci |
| connect_timeout                               | 10              |
| disconnect_on_expired_password                | ON              |
| init_connect                                  |                 |
| max_connect_errors                            | 100             |
| max_connections                               | 512             |
| max_user_connections                          | 0               |
| performance_schema_session_connect_attrs_size | 512             |

+-----------------------------------------------+-----------------+

 show full processlist;
 

## Reference
[如何查找MySQL中查询慢的SQL语句](https://www.cnblogs.com/zhuyalong/p/11335857.html)
[mysql的大量的sleep进程解决办法](https://www.cnblogs.com/gaoyuechen/p/10607439.html)