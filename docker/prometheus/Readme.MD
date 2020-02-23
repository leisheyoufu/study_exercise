tzselect
export TZ='Asia/Shanghai'
date -R
date -s "02/23/2020 10:46:30"

wget https://github.com/prometheus/node_exporter/releases/download/v0.18.1/node_exporter-0.18.1.linux-amd64.tar.gz
nohup ./node_exporter >> node_exporter.log 2>&1 &
/root/prometheus/node_exporter-0.18.1.linux-amd64/

docker run --name prometheus -d -p 9090:9090 -v /etc/prometheus/prometheus.yml:/etc/prometheus/prometheus.yml -v /etc/prometheus/:/etc/prometheus/ prom/prometheus --config.file=/etc/prometheus/prometheus.yml

cpu使用率:100 - (avg by (instance) (irate(node_cpu_seconds_total{mode="idle"}[1m])) * 100) 
内存使用率：100*(node_memory_MemTotal_bytes - node_memory_MemFree_bytes - node_memory_Buffers_bytes - node_memory_Cached_bytes) / node_memory_MemTotal_bytes

磁盘使用：100.0 - 100 * ((node_filesystem_avail_bytes{mountpoint=~"/", device!="rootfs"} / 1000 / 1000 ) / (node_filesystem_size_bytes{mountpoint=~"/", device!="rootfs"} / 1024 / 1024))

docker run --name grafana -d -p 8011:3000 grafana/grafana

## MySql
docker run --name mysql -v /home/ubuntu/mysql/:/var/lib/mysql -e MYSQL_ROOT_PASSWORD=123456. -p 8888:3306 -d mysql:5.5
docker run -d --name mysql-exporter -p 9104:9104 -e DATA_SOURCE_NAME="root:123456.@(192.168.126.160:8888)/mysql" prom/mysqld-exporter
docker restart prometheus


## Reference
https://testerhome.com/topics/21807
https://www.cnblogs.com/bigberg/p/10118137.html