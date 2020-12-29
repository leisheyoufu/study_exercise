create user 'root'@'%' identified by '123456';
grant RELOAD,LOCK TABLES,REPLICATION CLIENT,REPLICATION SLAVE,SHOW DATABASES,SHOW VIEW,LOCK TABLES,PROCESS on *.* to 'root'@'%';
grant ALL PRIVILEGES on *.* to 'root'@'%';
grant SELECT on `mysql`.* to 'root'@'%';
select Show_db_priv, user,host from mysql.user;  // 查询用户show databases 权限