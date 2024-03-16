// () 函数调用运算符重载
#include <iostream>
#include <string>

using namespace std;

class MyPrint {

public:
  // 重写 ()
  void operator()(string printContent) {

    cout << printContent << endl;
  }
};

void test01() {

  MyPrint print;
  
  print("xuyushan is my lover");
}


class Person {

public:
  Person(string name) {
    this->name = name;
  }

  Person& eat(string food) {
    cout << this->name << " eat " << food << endl;

    return *this;
  }

  Person& drink(string water) {
    cout << this->name << " drink " << water << endl;

    return *this;
  }

private:
  string name;
};

void test02() {

  Person person1("roger");

  person1.eat("麦当劳").drink("可乐"); // 链式编程;
}

int main() {

  //test01();

  test02();

  system("pause");

  return EXIT_SUCCESS;
}