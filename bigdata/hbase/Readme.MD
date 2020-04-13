
wget https://mirrors.tuna.tsinghua.edu.cn/apache/hbase/2.1.10/hbase-2.1.10-bin.tar.gz
./bin/start-hbase.sh
jps
```
[root@airflow hbase-2.1.10]# jps
2370 Jps
1959 HMaster
```
Access http://<ip>:16010 to view the dashboard

## Use hbase shell to access Hbase
 ./bin/hbase shell
create 'test', 'cf'  // create table test, 列族 cf， 列族在创建表时必须给出
list 'test'
describe 'test'   // get detail information for table test
put 'test', 'row1', 'cf:a', 'vale1'
put 'test', 'row2', 'cf:b', 'vale2'
put 'test', 'row3', 'cf:c', 'vale3'

列标识不通，就是两行
hbase(main):009:0> scan 'test'
ROW                                COLUMN+CELL
 row1                              column=cf:a, timestamp=1586625057779, value=vale1
 row1                              column=cf:b, timestamp=1586625083652, value=value2
 row3                              column=cf:c, timestamp=1586625094331, value=value3
2 row(s)

## Reference 
https://www.zifangsky.cn/1285.html