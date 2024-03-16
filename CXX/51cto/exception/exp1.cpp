// 异常基本处理
#include <iostream>
#include <string>

using namespace std;

class MyException { // 自定义异常类

public:
  void printError() {
    cout << "自定义的异常" << endl;
  }

};

class Person {

public:
  Person(string name) {
    this->name = name;
    cout << "Person: " << this->name << " 构造函数" << endl;
  }

  ~Person() {
    this->name = name;
    cout << "Person: " << this->name << " 析构函数" << endl;
  }

private:
  string name;
};

int myDevide(int a, int b) {

  if (0 == b) {
    //throw - 1; // 抛出 int 类型的异常;
    //throw 3.14; // 抛出 double 类型的异常;
    //throw 'a'; // 抛出 char 类型的异常;(这三句代码谁先抛出异常, 就处理谁)

    // 栈解旋: 从try开始 到 throw 抛出异常之前 所有栈上的对象 都会被释放; 这个过程被称为栈解旋。
    Person person1("roger");
    Person person2("rei ri");
    Person* person3 = new Person("xiangkusu"); // 堆区的对象, 就没有被释放

    throw MyException(); // 匿名对象 (相当于调用了一个无参构造函数)
    delete person3; // 因为 MyException() 异常已经抛出, 所以 person3 的析构函数不会调用
  }

  return a / b;
}

void test01() {

  int a = 10;
  int b = -10;

  try {
    myDevide(a, 0);
  }
  catch (int) { // 捕获 int 异常
    cout << "int 类型异常捕获" << endl;
  }
  catch (double) {
    throw; // 如果不想处理这个异常, 可以继续向上抛出
    cout << "double 类型异常捕获" << endl;
  }
  catch (MyException exception) {
    cout << "MyException 类型异常捕获" << endl;
    exception.printError();
    throw;
    
  }
  catch (...) { // 捕捉其它异常
    cout << "char 类型异常捕获" << endl;
  }
}

int main() {

  try {
    test01();
  }
  catch(double) {
    cout << "main double 类型异常捕获" << endl;
  }
  catch (...) {
    cout << "main other 类型异常捕获" << endl;
  }

  return EXIT_SUCCESS;
}