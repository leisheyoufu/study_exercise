## cmake build with debug
使用debug调试mysql的执行 http://blog.chinaunix.net/uid-20785090-id-4328033.html
mkdir build && cd build
cmake ../ -DWTITH_DEBUG=1

mysql修改源码发布及源码中的debug日志查看
https://blog.csdn.net/aoerqileng/article/details/109052926
https://www.cnblogs.com/jkin/p/16497783.html

mysql -uroot -P3334 --binary-as-hex=False
./bin/mysqld --debug=d,info --port 3334
## gdb 调试mysql
https://www.modb.pro/db/216318

## sql 字典表调用
https://baijiahao.baidu.com/s?id=1746342784983756518&wfr=spider&for=pc