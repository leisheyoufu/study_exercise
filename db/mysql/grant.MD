create user 'root'@'%' identified by '123456';
grant RELOAD,LOCK TABLES,REPLICATION CLIENT,REPLICATION SLAVE,SHOW DATABASES,SHOW VIEW,LOCK TABLES,PROCESS on *.* to 'root'@'%';
grant ALL PRIVILEGES on *.* to 'root'@'%';
grant SELECT on `mysql`.* to 'root'@'%';
