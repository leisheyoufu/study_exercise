import java.util.Date

object Func {
  /* 这是我的第一个 Scala 程序
   * 以下程序将输出'Hello World!'
   */
  def func1(a: Int, b: Int): Unit = {
    println(a + b)
  }

  def fun2(num: Int): Int = {
    if (num == 1)
      num
    else
      num * fun2(num - 1)
  }


  def fun3(a: Int = 10, b: Int) = {
    println(a + b)
  }


  def ifElseFunc(): Unit = {
    println("-----------start if else function-----------")
    val age = 18
    if (age < 18) {
      println("no allow")
    } else if (18 <= age && age <= 20) {
      println("allow with other")
    } else {
      println("allow self")
    }
    println("-----------end if else function-----------")
  }

  val anonymousFunction1 = (a: Int) => {
    println(a)
  }

  //无参数匿名函数
  val anonymousFunction2 = () => {
    println("anoymous function with no argument")
  }
  //有返回值的匿名函数
  val anonymousFunction3 = (a: Int, b: Int) => {
    a + b
  }

  def anoymous(): Unit = {
    println("------------Start anoymous function-----------")
    anonymousFunction1(1)
    anonymousFunction2()
    println(anonymousFunction3(1, 1))
    println("-----------End anoymous function-----------")

  }

  def fun5(num: Int) = {
    def fun6(a: Int, b: Int): Int = {
      if (a == 1) {
        b
      } else {
        fun6(a - 1, a * b)
      }
    }

    fun6(num, 1)
  }

  //函数的参数是函数
  def f(v1: Int, v2: Int): Int = {
    v1 + v2
  }

  def hightFun(f: (Int, Int) => Int, a: Int): Int = {
    f(a, 100)
  }

  println(hightFun(f, 1))

  //函数的返回是函数
  //1，2,3,4相加
  def hightFun2(a: Int, b: Int): (Int, Int) => Int = {
    def f2(v1: Int, v2: Int): Int = {
      v1 + v2 + a + b
    }

    f2
  }

  println(hightFun2(1, 2)(3, 4))

  //函数的参数是函数，函数的返回是函数
  def hightFun3(f: (Int, Int) => Int): (Int, Int) => Int = {
    f
  }

  println(hightFun3(f)(100, 200))
  println(hightFun3((a, b) => {
    a + b
  })(200, 200))
  //以上这句话还可以写成这样
  //如果函数的参数在方法体中只使用了一次 那么可以写成_表示
  println(hightFun3(_ + _)(200, 200))

  def partialFunc() = {
    def log(date: Date, s: String) = {
      println("date is " + date + ",log is " + s)
    }

    val date = new Date()
    log(date, "log1")
    log(date, "log2")
    log(date, "log3")

    //想要调用log，以上变化的是第二个参数，用下划线表示，可以用偏应用函数处理
    val logWithDate = log(date, _: String)
    logWithDate("log11")
    logWithDate("log22")
    logWithDate("log33")
  }


  def closure() : Unit  ={
    println( "multiplier(1) value = " + multiplier(1) )
    println( "multiplier(2) value = " + multiplier(2) )
  }
  var factor = 3
  val multiplier = (i:Int) => i * factor


  def main(args: Array[String]) {
    func1(100, 101);
    print(fun2(5))
    fun3(b = 2)
    anoymous()
    ifElseFunc()
    partialFunc()
    closure()
  }
}


