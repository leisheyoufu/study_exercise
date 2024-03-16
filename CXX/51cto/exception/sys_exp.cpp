// 使用系统提供的标准异常
#include <iostream>
#include <string>

#include <stdexcept> // 系统提供的标准异常 要包含头文件;

using namespace std;

class Person {

public:
  Person(string name, int age) {
    this->name = name;

    if (age < 0 || age > 200) {

      throw length_error("长度越界");

      //throw out_of_range("年龄越界了!");
    }
  }

  string name;
  int age;
};


void test01() {
  try {
    Person person("roger", 201);
  }
  catch(out_of_range& exception) {
    cout << "out_of_range exception: " << exception.what() << endl; // exception.what(): 抛出异常时的错误提示
  }
  catch (length_error& exception) {
    cout << "length_error exception: " << exception.what() << endl;
  }
  catch (...) {
    cout << "... exception" << endl;
  }
}


int main() {

  test01();

  return EXIT_SUCCESS;
}

/*
length_error exception: 长度越界
*/