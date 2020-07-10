## Setup kafka inside docker
docker pull wurstmeister/zookeeper
docker pull wurstmeister/kafka
docker run -d --name zookeeper -p 2181:2181 -t wurstmeister/zookeeper
docker run -d --name kafka --publish 9092:9092 --link zookeeper --env KAFKA_ZOOKEEPER_CONNECT=zookeeper:2181 --env KAFKA_ADVERTISED_HOST_NAME=<HOST_IP> --env KAFKA_ADVERTISED_PORT=9092 --volume /etc/localtime:/etc/localtime wurstmeister/kafka:latest

## Topic command
/opt/kafka/bin/kafka-topics.sh --zookeeper zookeeper:2181 --list
/opt/kafka/bin/kafka-topics.sh --bootstrap-server 127.0.0.1:9092 --list
/opt/kafka/bin/kafka-topics.sh  --create --zookeeper zookeeper:2181 --replication-factor 1 --partitions 1 --topic demo
/opt/kafka/bin/kafka-topics.sh  --describe --zookeeper zookeeper:2181 --topic demo
/opt/kafka/bin/kafka-topics.sh --bootstrap-server 127.0.0.1:9092 --delete --topic demo

## Producer command
/opt/kafka/bin/kafka-console-producer.sh --broker-list localhost:9092 --topic demo

## Consumer command
/opt/kafka/bin/kafka-console-consumer.sh --bootstrap-server localhost:9092 --topic demo --from-beginning

## Spark bulk api
Set max.poll.records in consumer properties

## Reference
https://www.cnblogs.com/yxlblogs/p/10115672.html
https://studygolang.com/articles/17912
https://blog.csdn.net/tflasd1157/article/details/81985722
https://blog.csdn.net/nia305/article/details/88666663    // sarama-cluster