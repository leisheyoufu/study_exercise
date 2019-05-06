package cmd

object StringFmt {
  def main(args: Array[String]): Unit = {
    val streamFmt : String = "adl://obd-spark-c14.azuredatalakestore.net/local/loch/%s/ProcessedSignalLogs_Commercial_2019_04_01_%02d.ss"
    for(i <- 0 to 23){
      val inputStream = streamFmt.format("input",i)
      val outputStream = streamFmt.format("output", i)
      println(outputStream)
    }
  }
}
