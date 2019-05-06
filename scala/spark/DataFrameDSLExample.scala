import org.apache.spark.sql.{Column, DataFrame, Row, SparkSession}
import org.apache.spark.{SparkConf, SparkContext}

object DataFrameDSLExample {
  private val conf: SparkConf = new SparkConf().setAppName("TestTransformation").setMaster("local")
  private val sc = new SparkContext(conf)
  private val sparkSession = SparkSession.builder.appName("ReadTimestamp").getOrCreate()

  def main(args: Array[String]) {
    //    createDataFrameWithSchema()
        timeFormatDf()
//        timeDiffDf()
    //    selectAs()
    //unionAll()
    //selectSpecificColumn()
    sparkSession.stop()
  }

  def createDataFrameWithSchema(): Unit = {
    import org.apache.spark.sql.types._
    val schema = StructType(List(
      StructField("integer_column", IntegerType, nullable = false),
      StructField("string_column", StringType, nullable = true),
      StructField("comma_column", StringType, nullable = true),
      StructField("date_column", DateType, nullable = true)
    ))

    val rdd = sc.parallelize(Seq(
      Row(1, "First Value", "sub1:sub2", java.sql.Date.valueOf("2010-01-01")),
      Row(2, "Second Value", "sub3:sub4", java.sql.Date.valueOf("2010-02-01")),
      Row(3, "Thrid Value", "sub5:sub4", java.sql.Date.valueOf("2010-02-02"))
    ))
    val df = sparkSession.createDataFrame(rdd, schema)
    // cl very important to support DataFrame and Dataset
    import sparkSession.implicits._
    df.filter($"integer_column" < 2).show()

    // split DataFrame
    def splitDataFrame(df: DataFrame, index: Int): DataFrame = {
      import sparkSession.implicits._
      val fineDF = df.map(line => {
        val integer_column = line.getInt(0)
        val colArr = line.getString(index).split(":")
        val col1 = colArr(0)
        val col2 = colArr(1)
        (integer_column, col1, col2)
      }).toDF("integer_column", "col1", "col2")
      return fineDF
    }

    def filterAnd(df: DataFrame) = {
      import sparkSession.implicits._
      df.filter($"integer_column" === 2 && $"col2".equalTo("sub4")).show()
    }

    // split column
    val splittedDf = splitDataFrame(df, 2)
    splittedDf.show()
    // filter row
    filterAnd(splittedDf)
  }

  def timeFormatDf() = {
    import org.apache.spark.sql.functions._
    println("UTC time format")
    val df1 = sparkSession.range(10)
      .withColumn("today", current_date())
      .withColumn("now", date_format(current_timestamp(), "yyyy-MM-dd'T'HH:mm:ss.SSSX'Z'"))
      .withColumn("ticks", unix_timestamp())
    df1.show(false)
    println("UTC and CST time format")
    val df2 = df1.select(col("id"),
      col("today"),
      col("now").as("UTC  String"),
      date_format(col("today"), "yyyy-MM-dd").as("TodayString"),
      to_timestamp(col("now"), "yyyy-MM-dd'T'HH:mm:ss.SSSX'Z'").as("Timestamp"))
    df2.show(false)
    import sparkSession.implicits._
    val df3 = Seq(
      ("A", "2019-04-01T14:00:00.000+00Z"),
      ("B", "2019-04-01T15:00:00.000+00Z"))
     .toDF("Id", "Time")
    val df4 = df3.select(col("Id"), to_timestamp(col("Time"), "yyyy-MM-dd'T'HH:mm:ss.SSSX'Z'").as("Timestamp"))
    df4.show()
    df4.select(date_format(col("Timestamp"), "yyyy-MM-dd'T'HH:mm:ss.SSSX'Z'")).show(1,false)
  }

  def timeDiffDf() = {
    import org.apache.spark.sql.functions._
    import sparkSession.implicits._
    val df1 = Seq(("1/01/2017 12:01:00 AM"), ("1/1/2017 12:05:00 AM")).toDF("timex")
    val df2 = df1.withColumn("timex", to_timestamp('timex, "d/MM/yyyy hh:mm:ss a")).withColumn("curr", lit(current_timestamp()))
    df2.show()
    val df3 = df2.alias("t1").join(df2.alias("t2"), $"t2.timex" === to_timestamp($"t1.timex"), "leftOuter")
      .select(col("t1.timex").as("time1"), col("t2.curr").as("time2"))
    df3.withColumn("diff_sec", unix_timestamp('time2) - unix_timestamp('time1)).withColumn("diff_min", 'diff_sec / 60).show(false)
  }

  def selectAs() = {
    import org.apache.spark.sql.functions._
    import sparkSession.implicits._
    val df1 = Seq(
      ("A", 1, 5, 3),
      ("B", 3, 4, 2),
      ("C", 4, 6, 3),
      ("D", 5, 9, 1)).toDF("a", "b", "c", "d")
    df1.select(lit(" ").as("col1"),
      col("b").as("b1"),
      (col("c") + col("d")).as("e")).show()
  }

  def unionAll() = {
    import sparkSession.implicits._
    import org.apache.spark.sql.types._
    val schema = StructType(List(
      StructField("alphabet", ByteType, true),
      StructField("number", IntegerType, true),
      StructField("word", StringType, true)))
    var df = sparkSession.createDataFrame(sc.emptyRDD[Row], schema)

    for (i <- 0 to 10) {
      val dfi = Seq(
        ('a' + i, i, "Hello %c".format('a'+i))
      ).toDF("alphabet", "number", "word")
      df = df.union(dfi)
    }
    println(df.columns.length)
    // print first column name
    println(df.columns(0))
    df.show()
  }

  def selectSpecificColumn(): Unit ={
    val dataDF = sparkSession.createDataFrame(Seq(
      (1, 1, 2, 3, 8, 4, 5),
      (2, 4, 3, 8, 7, 9, 8),
      (3, 6, 1, 9, 2, 3, 6),
      (4, 10, 8, 6, 9, 4, 5),
      (5, 9, 2, 7, 10, 7, 3),
      (6, 1, 1, 4, 2, 8, 4)
    )).toDF("colToExclude", "col1", "col2", "col3", "col4", "col5", "col6")
    val colsToSelect = dataDF.columns.filter(_ != "colToExclude")

    // Take a look at the array as comma separate values.
    colsToSelect.mkString(",")

    // This method allows you to perform a simple selection
    dataDF.select(colsToSelect.head, colsToSelect.tail: _*).show()

    // This method creates a new dataframe using your column list
    // Filter dataDF using the colsToSelect array, and map
    // the results into columns.
    dataDF.select(dataDF.columns.filter(colName => colsToSelect.contains(colName)).map(colName => new Column(colName)): _*).show()
  }
}
