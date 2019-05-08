package sql

import org.apache.spark.sql.SparkSession

object DataFrameDataSet {
  case class Person(name:String, age:Long)
  case class Data(a: Int, b: String)
  case class Person2(name: String, zip: Long)

  def main (args: Array[String])
  {
    val spark = SparkSession
      .builder()
      .master("local")
      .appName("Test Dataset and DataFrame Support")
      .config("spark.sql.warehouse.dir", "src/main/resources/tables")
      .getOrCreate();

    //createDataset(spark)
    //readDataset(spark)
    //dataframeToDataset(spark)
    example(spark)
  }

  def createDataset(spark : SparkSession): Unit ={
    import spark.implicits._
    val ds1 = spark.createDataset(1 to 5)
    ds1.show()

    val data=List(Person("zhangsan", 20), Person("lisi", 30))
    val ds2 = data.toDS()
    ds2.show()
  }

  def readDataset(spark : SparkSession): Unit ={
    import spark.implicits._
    spark.createDataset(spark.sparkContext.textFile("src/main/resources/people.txt")).show
  }

  def dataframeToDataset(spark : SparkSession): Unit ={
    import spark.implicits._
    val jsonDF = spark.read.json(("src/main/resources/people.json"))
    val jsonDS = jsonDF.as[Person]
    jsonDS.show()
  }

  def example(spark : SparkSession): Unit ={
    import spark.implicits._

    val ds = Seq(Data(1, "one"), Data(2, "two")).toDS()
    ds.show()

    val df = spark.read.json(spark.sparkContext.parallelize("""{"zip": 94709, "name": "Michael"}""" :: Nil).toDS())
    df.as[Person2].collect()
    df.as[Person2].show()


    import org.apache.spark.sql.functions._
    val ds2 = spark.read.text("src/main/resources/people.csv").as[String]
    val result = ds2.flatMap(_.split(","))toDF()
    result.groupBy($"value" as "word").agg(count("*") as "numOccurances").orderBy($"numOccurances" desc).show()
  }
}
