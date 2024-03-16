// 继承中的同名处理
#include <iostream>

using namespace std;

class Base {

public:
  Base() {
    this->a = 100;
  }

  void publicFunction() {
    cout << "Base public function" << endl;
  }

  void publicFunction(int a) {
    cout << "Base public function(int a)" << endl;
  }

  int a;
};

class Son : public Base {

public:
  Son() {
    this->a = 200;
  }

  void publicFunction() {
    cout << "Son public function" << endl;
  }

  void publicFunction(int a) {
    cout << "Son public function(int a)" << endl;
  }

  int a;
};

void test01() {
  Son son1;

  // 成员属性
  cout << son1.a << endl; // 如无特殊声明, 子类对象会直接调用本类的属性;
  cout << son1.Base::a << endl; // 子类对象 调用父类的 a 属性;
  
  // 成员函数
  son1.publicFunction(); // 直接调用时, 会先调用子类; 
  son1.Base::publicFunction(); // 父类的同名函数会被隐藏, 除非用作用域运算符去调用;

  son1.publicFunction(10);
  son1.Base::publicFunction(10);
}

int main() {

  test01();

  return EXIT_SUCCESS;
}

/*
200
100
Son public function
Base public function
Son public function(int a)
Base public function(int a)

*/