## Grant privilege for mysql
mysql> use mysql;
mysql> select user,host from user;
ALTER USER 'root'@'localhost' IDENTIFIED BY 'password' PASSWORD EXPIRE NEVER;   #修改加密规则
ALTER USER 'root'@'localhost' IDENTIFIED WITH mysql_native_password BY 'password';   #更新一下用户的密码


## Setup xtrabackup
wget https://www.percona.com/downloads/Percona-XtraBackup-2.4/Percona-XtraBackup-2.4.20/binary/debian/focal/x86_64/Percona-XtraBackup-2.4.20-rc8b4056-focal-x86_64-bundle.tar
dpkg -i percona-xtrabackup-*.deb   // may fail due to dependency error
apt-get -f -y install    // setup dependency


## Physical Full Backup (node1)
sysbench /usr/share/sysbench/oltp_read_write.lua --mysql-host=127.0.0.1 --mysql-port=3306 --mysql-user=root --mysql-password=123456 --mysql-db=sbtest --db-driver=mysql --tables=3 --table-size=100  prepare  // insert test data
mkdir -p /root/backup/full
innobackupex --defaults-file=/etc/mysql/mysql.cnf --user=root --password=123456 /root/backup/full

## Incremental Backup
mkdir -p /root/backup/incremental
innobackupex --defaults-file=/etc/mysql/mysql.cnf --user=root --password=123456  --incremental /root/backup/incremental/ --incremental-basedir=/root/backup/full/<data dir>/ --parallel=2

## Physical Full Recover (node2)
systemctl stop mysql
mv /var/lib/mysql /var/lib/mysql_back
scp <node1>:/root/backup <node2>:/root/backup
innobackupex --apply-log /root/backup/full/<data dir>
innobackupex --defaults-file=/etc/mysql/mysql.cnf --copy-back --rsync /root/backup/full/<data dir>  // this step copy file back to mysql data directory
chown -hR mysql:mysql /var/lib/mysql
systemctl start mysql

## Physical incremetal Recover (node2)
systemctl stop mysql
rm -rf /var/lib/mysql
scp <node1>:/root/backup <node2>:/root/backup
innobackupex --apply-log --redo-only  /root/backup/full/<data dir>   // full recover
innobackupex --apply-log /root/backup/full/<data dir>/ --incremental-dir=/root/backup/incremental/<data dir>/   // no redo-only at last incremental
innobackupex --apply-log /root/backup/full/<data dir>/   // apply on full data again
mkdir -p /var/lib/mysql
innobackupex --defaults-file=/etc/mysql/mysql.cnf --copy-back --rsync /root/backup/full/<data dir>
chown -hR mysql:mysql /var/lib/mysql
systemctl start mysql


## xtrabackup 原理，包含复制文件和redo处理
https://blog.csdn.net/nightelve/article/details/17397245