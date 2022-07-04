使用grep -r 命令递归搜索的时候，子目录中有的时候存在链接文件。有些链接到搜索目录下的另外的一个文件。这样的话，被链接的文件夹就被grep了两次甚至更多。这样就出现了冗余的信息。如何使grep 不去搜索链接目录的文件呢？
find -P ./ -type f | xargs grep xxx
grep -A 10 "xxxx" #显示grep 到行的前后10行

带.gz文件
gzip -dc ./*.gz | grep "iotop"