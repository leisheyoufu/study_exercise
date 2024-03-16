// 继承中静态成员的处理
#include <iostream>

using namespace std;

class Base {
public:
  static int a;

  static void publicFunction() {
    cout << "Base public function: " << endl;
  }

  static void publicFunction(int a) {
    cout << "Base public function(int a): " << a << endl;
  }

};
int Base::a = 10;


class Son : public Base {

public:
  static int a;

  static void publicFunction() {
    cout << "Son public function: " << endl;
  }

  static void publicFunction(int a) {
    cout << "Son public function(int a): " << a << endl;
  }

};
int Son::a = 20;


void test01() {

  cout << "Son::a : " << Son::a << endl; // 静态成员属性, 子类可以继承
  cout << "Son::Base::a : " << Son::Base::a << endl; // 打印父类的值

}

void test02() {
  Son::publicFunction(100);
  Son::Base::publicFunction(1000);

  Son::publicFunction();
  Son::Base::publicFunction();
}


int main() {
  
  test01();
  test02();

  return EXIT_SUCCESS;
}

/*
on::a : 20
Son::Base::a : 10
Son public function(int a): 100
Base public function(int a): 1000
Son public function: 
Base public function:
*/