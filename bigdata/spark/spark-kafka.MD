## Setup kafka inside docker
docker pull wurstmeister/zookeeper
docker pull wurstmeister/kafka
docker run -d --name zookeeper -p 2181:2181 -t wurstmeister/zookeeper
docker run -d --name kafka --publish 9092:9092 --link zookeeper --env KAFKA_ZOOKEEPER_CONNECT=zookeeper:2181 --env KAFKA_ADVERTISED_HOST_NAME=<HOST_IP> --env KAFKA_ADVERTISED_PORT=9092 --volume /etc/localtime:/etc/localtime wurstmeister/kafka:latest

## Spark with kafka
/opt/kafka/bin/kafka-topics.sh  --create --zookeeper zookeeper:2181 --replication-factor 1 --partitions 1 --topic spark
/opt/kafka/bin/kafka-console-producer.sh --broker-list localhost:9092 --topic spark

## Producer command
/opt/kafka/bin/kafka-console-producer.sh --broker-list localhost:9092 --topic spark

## Consumer command
/opt/kafka/bin/kafka-console-consumer.sh --bootstrap-server localhost:9092 --topic spark --from-beginning


## For windows
https://github.com/steveloughran/winutils  // Download as HADOOP_HOME

## Offeset and checkpoint
query = decomp.writeStream\
    .format("text")\
    .option("path", \Data_directory_inHDFS) \
    .option("checkpointLocation", \pathinDHFS\) \
    .start()


.option("startingOffsets", "{\""+topic+"\":{\"0\":91332989,\"1\":16810853,\"2\":16810618}}")   // read
https://stackoverflow.com/questions/46612159/kafka-structured-streaming-checkpoint

## Reference
https://www.jianshu.com/p/c65008b29549    // Spark Structured Streaming 与Kafka的整合
https://mvnrepository.com/artifact/org.apache.spark/spark-streaming-kafka-0-10_2.11/2.4.5  // maven artifact
https://medium.com/knoldus/basic-example-for-spark-structured-streaming-kafka-integration-a6d0b3ffc3bd  // structure streaming write example 
https://stackoverflow.com/questions/55606034/geting-messages-of-offset-is-getting-reset-in-structured-streaming-mode-in-spark // example
https://databricks.com/blog/2017/04/26/processing-data-in-apache-kafka-with-structured-streaming-in-apache-spark-2-2.html   // json to schema with dataframe