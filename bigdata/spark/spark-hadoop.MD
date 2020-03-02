## Download hadoop
wget https://mirrors.tuna.tsinghua.edu.cn/apache/spark/spark-2.4.5/spark-2.4.5-bin-hadoop2.7.tgz
export HADOOP_HOME=/root/spark/hadoop-2.7.7

## Hadoop
cat $HADOOP_HOME/etc/hadoop/hadoop-env.sh
```
export JAVA_HOME=/usr/lib/jvm/jre-1.8.0-openjdk/
```


cat etc/hadoop/core-site.xml  // client
```
<configuration>
<property>
    <name>fs.default.name</name>
    <value>hdfs://localhost:8020</value>
</property>
</configuration>
```

### Start hdfs
cat etc/hadoop/hdfs-site.xml   // the location that data write into
```
<configuration>
<property>
        <name>hadoop.tmp.dir</name>
        <value>/opt/hadoop/tmp</value>
</property>
<property>
        <name>dfs.replication</name>
        <value>1</value>
</property>
</configuration>
```
export HADOOP_HOME=/root/spark/hadoop-2.7.7
export PATH=$PATH:$HADOOP_HOME/bin
hdfs namenode -format

### Start yarn
cat $HADOOP_HOME/etc/hadoop/yarn-site.xml
```
<property>
        <name>yarn.nodemanager.aux-services</name>
        <value>mapreduce_shuffle</value>
</property>
<property>
    <name>yarn.nodemanager.local-dirs</name>
    <value>/tmp</value>
</property>
```
cp $HADOOP_HOME/etc/hadoop/mapred-site.xml.template $HADOOP_HOME/etc/hadoop/mapred-site.xml
 cat $HADOOP_HOME/etc/hadoop/mapred-site.xml
```
<configuration>
<property>
    <name>mapreduce.framework.name</name>
    <value>yarn</value>
</property>
<property>
    <name>mapreduce.cluster.local.dir</name>
    <value>/tmp</value>
</property>
</configuration>
```
$HADOOP_HOME/sbin/start-yarn.sh



http://192.168.126.160:8042/  // hadoop web page

yarn logs -applicationId application_1583167963828_0003  // <application id>

## Hdfs
hdfs dfs -mkdir -p /data/input
hdfs dfs -copyFromLocal /root/spark-data/input/people.txt /data/input/

## Spark
cp $SPARK_HOME/conf/spark-env.sh.template $SPARK_HOME/conf/spark-env.sh
```
export JAVA_HOME=/usr/lib/jvm/jre-1.8.0-openjdk/
export SCALA_HOME=/root/spark/scala-2.11.12
export SPARK_MASTER_IP=192.168.126.160
export SPARK_LOCAL_IP=192.168.126.160
export SPARK_MASTER_PORT=7077
export SPARK_WORKER_MEMORY=1G
export SPARK_EXECUTOR_CORES=1
export HADOOP_HOME=/root/spark/hadoop-2.7.7
export HADOOP_CONF_DIR=$HADOOP_HOME/etc/hadoop
```
$SPARK_HOME/sbin/stop-all.sh
$SPARK_HOME/sbin/start-all.sh

## Try Spark
hdfs dfs -mkdir -p /data/input
hdfs dfs -mkdir -p /data/output
hdfs dfs -copyFromlocal people.txt /data/input/people.txt
spark-submit --master yarn --deploy-mode cluster --class main.scala.HelloYarnSpark /root/spark-data/jars/HelloYarnSpark.jar  // Jar input: /data/input/people.txt , output: /data/output/people.parquet




## Reference
https://www.cnblogs.com/traditional/p/11297049.html   setup hadoop and spark on sigle node
https://blog.csdn.net/m0_37568814/article/details/80784749

http://mail-archives.apache.org/mod_mbox/spark-user/201605.mbox/%3CCAJ3fcbCtuXo7Y_0D7WCwjCswdOSUKy+Q9snEvzRFNWUM99Zw7A@mail.gmail.com%3E   // solve issue application container does not exist , exit code -1