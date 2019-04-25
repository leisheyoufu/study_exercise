// Databricks notebook source
display(dbutils.fs.ls("/delta"))

// COMMAND ----------

import org.apache.spark.sql._
import org.apache.spark.sql.functions._

val events = spark.read
  .option("inferSchema", "true")
  .json("/databricks-datasets/structured-streaming/events/")
  .withColumn("date", expr("time"))
  .drop("time")
  .withColumn("date", from_unixtime($"date", "yyyy-MM-dd"))

display(events)

// COMMAND ----------

import org.apache.spark.sql.SaveMode
events.write.format("delta").mode("overwrite").partitionBy("date").save("/delta/events/")

val events_delta = spark.read.format("delta").load("/delta/events/")
display(events_delta)

// COMMAND ----------

import org.apache.spark.sql._
import org.apache.spark.sql.functions._

display(events_delta.groupBy("action","date").agg(count("action").alias("action_count")).orderBy("date", "action"))

// COMMAND ----------
