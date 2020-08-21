MySQL 8.0单个packet可以允许的最大值是1GB。
## 服务端
[mysqld]
max_allowed_packet=128M

当传输的packet大于max_allowed_packet时，触发错误EN_NET_PACKET_TOO_LARGE,并且关闭Connection。在有的客户端中也会显示信息Lost connection to MySQL server during query

MySQL [sys]> show variables like '%packet';
+--------------------------+------------+
| Variable_name            | Value      |
+--------------------------+------------+
| max_allowed_packet       | 16777216   |
| slave_max_allowed_packet | 1073741824 |
+--------------------------+------------+

## 客户端
mysql --max_allowed_packet=32M

