// 异常变量的生命周期
#include <iostream>

using namespace std;

class MyException {

public:
  MyException() {
    cout << "MyException 默认构造 函数" << endl;
  }

  MyException(const MyException& exception) {
    cout << "MyException 拷贝构造 函数" << endl;
  }

  ~MyException() {
    cout << "MyException 析构函数" << endl;
  }
};


void doWork() {
  throw new MyException();
  //throw MyException();
}

void test01() {

  try {
    doWork();
  }
  catch(MyException *exception) {
    cout << "*exception 异常" << endl;

    delete exception; // 异常对象的指针变量, 需要手动释放;
  }
  catch (MyException &exception) {
    cout << "exception 异常" << endl;
  }
  catch (...) {
    cout << "... 异常" << endl;
  }
}


int main() {

  test01();

  return EXIT_SUCCESS;
}

/*
MyException 默认构造 函数
*exception 异常
MyException 析构函数

*/