package sql

import org.apache.spark.sql.SparkSession

object UserDefinedFunction {
  def main (args: Array[String])
  {
    val spark = SparkSession
      .builder()
      .master("local")
      .appName("Test User Defined Function")
      .config("spark.sql.warehouse.dir", "src/main/resources/tables")
      .getOrCreate();

    import spark.implicits._
    val df = Seq(
      (0, "hello"),
      (1, "world")).toDF("id", "text")

    // Define a "regular" Scala function
    // It's a clone of upper UDF
    val toUpper: String => String = _.toUpperCase

    import org.apache.spark.sql.functions.udf
    val upper = udf(toUpper)
    df.withColumn("upper", upper('text)).show()
    // You could have also defined the UDF this way
    //val upperUDF = udf { s: String => s.toUpperCase }

    // or even this way
//    val upperUDF = udf[String, String](_.toUpperCase)
//    df.withColumn("upper", upperUDF('text)).show()
  }
}
