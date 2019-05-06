package sql

import org.apache.spark.sql.SparkSession

object HiveTest {
  def main (args: Array[String])
  {
    val spark = SparkSession
      .builder()
      .master("local")
      .appName("Test Hive Support")
      //.config("hive.metastore.uris", "jdbc:mysql://localhost/metastore")
      .config("spark.sql.warehouse.dir", "src/main/resources/tables")
      //.enableHiveSupport
      .getOrCreate();

    import spark.implicits._
    val testdf = Seq(("Word1", 1), ("Word4", 4), ("Word8", 8)).toDF;
    testdf.show;
    testdf.write.mode("overwrite").saveAsTable("WordCount");
  }
}
