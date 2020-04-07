package main.scala


import org.apache.spark.sql.SparkSession


object SparkStreamingKafka {
  def main(args: Array[String]): Unit = {
    val spark = SparkSession
      .builder()
      .master("local")
      .appName("Spark Kafka Example")
      //.config("spark.sql.warehouse.dir", "/warehouse")
      .getOrCreate()

    val df = spark
      .readStream
      .format("kafka")
      .option("kafka.bootstrap.servers", "192.168.126.160:9092")
      .option("subscribe", "spark")
      .load()
    df.writeStream
      .format("console")
      .option("truncate","false")
      .start()
      .awaitTermination()
  }
}
