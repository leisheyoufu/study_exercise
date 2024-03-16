// 自己编写异常类
#include <iostream>
#include <string>

using namespace std;

class MyOutOfRangeException : public exception { // exception: 系统提供的异常基类

public:

  MyOutOfRangeException(string errorInfo) {
    this->errorInfo = errorInfo;
    cout << "MyOutOfRangeException: 有参构造函数" << endl;
  }

  virtual ~MyOutOfRangeException()
  {
    cout << "~MyOutOfRangeException: 析构函数" << endl;
  }

  virtual char const* what() const
  {
    return (this->errorInfo).c_str(); // string 转 char*
  }

private:
  string errorInfo;
};

class Person {

public:
  Person(string name, int age) {
    this->name = name;

    if (age < 0 || age > 200) {
      throw MyOutOfRangeException("so old");
    }
  }
  string name;
  int age;
};

void test01() {
  try {
    Person person("roger", 201);
  }
  catch (MyOutOfRangeException& myOutOfRangeException) { // 自定义异常类
    cout << "MyOutOfRangeException exception: " << myOutOfRangeException.what() << endl;
  }
  catch (...) {
    cout << "... exception" << endl;
  }
}

int main() {

  test01();

  return EXIT_SUCCESS;
}