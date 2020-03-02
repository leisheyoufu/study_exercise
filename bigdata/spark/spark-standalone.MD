## Setup jdk

yum install java-1.8.0-openjdk.x86_64
export JAVA_HOME=/usr/lib/jvm/jre-1.8.0-openjdk/
export PATH=$PATH:$JAVA_HOME/bin
export CLASSPATH=.:$JAVA_HOME/lib/tools.jar:$JAVA_HOME/lib/dt.jar

## Setup scala

wget https://downloads.lightbend.com/scala/2.11.12/scala-2.11.12.tgz
tar xvfz scala-2.11.12.tgz
export SCALA_HOME=/root/spark/scala-2.11.12
export PATH=$PATH:$SCALA_HOME/bin

## Setup spark
export SPARK_HOME=/root/spark/spark-2.4.5-bin-hadoop2.7
export PATH=$PATH:$SPARK_HOME/bin
cp $SPARK_HOME/conf/spark-env.sh.template $SPARK_HOME/conf/spark-env.sh
cat $SPARK_HOME/conf/spark-env.sh

```
export JAVA_HOME=/usr/lib/jvm/jre-1.8.0-openjdk/
export SCALA_HOME=/root/spark/scala-2.11.12
export SPARK_MASTER_IP=192.168.126.160
export SPARK_LOCAL_IP=192.168.126.160
export SPARK_MASTER_PORT=7077
export SPARK_WORKER_MEMORY=1G
export SPARK_EXECUTOR_CORES=1
```
cp $SPARK_HOME/conf/slaves.template $SPARK_HOME/conf/slaves
cat $SPARK_HOME/conf/slaves
```
localhost
```
$SCALA_HOME/sbin/start-all.sh

Then access http://192.168.126.160:8080/ which is web interface of spark master


spark-submit --master spark://192.168.126.160:7077 --class main.scala.HelloWorld /root/spark-data/jars/HelloSpark.jar

# Docker
## Setup spark with docker
https://github.com/big-data-europe/docker-spark
git clone https://github.com/big-data-europe/docker-spark.git
docker-compose up


## Setup docker-compse
curl -L "https://github.com/docker/compose/releases/download/1.25.4/docker-compose-$(uname -s)-$(uname -m)" -o /usr/local/bin/docker-compose

## Reference
https://docs.docker.com/compose/install/
https://www.jianshu.com/p/7b1726e309e1   # setup spark on 3 virutual mathines
https://blog.csdn.net/u010416101/article/details/88897517  # spark standalone mode with 1 machine
https://mirrors.tuna.tsinghua.edu.cn/apache/  # 清华mirror for apache software