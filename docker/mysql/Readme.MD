docker network create service --subnet 172.18.0.0/16
docker run --name mysql-master -it --rm -e "MYSQL_ROOT_PASSWORD=123456" -p 3309:3306 --net=service -v `pwd`/conf/master:/etc/mysql/conf.d/ mysql:5.7
mysql -uroot -p123456 -h127.0.0.1 -P3309
