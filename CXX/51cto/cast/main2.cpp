#include <iostream>

using namespace std;

void test01() {

  char a = 'a';

  double d = static_cast<double>(a); // 静态类型转换

  cout << "d: " << d << endl;
}

// 父类、子类之间转换
class Base{
public:
  virtual void function() {

  }
};

class Child : public Base {
public:
  virtual void function() {

  }
};

void test02() {

  Base* base = NULL;
  Child* child = NULL;

  // 把 base 转为 Child*类型 向下转换 不安全;
  Child* child2 = static_cast<Child*>(base);

  // 把 child 转为 Base*类型 向上转换 安全;
  Base* base2 = static_cast<Base*>(child2);
}

void test03() {

  Base* base = NULL;
  Child* child = NULL;

  Base* base2 = dynamic_cast<Base*>(child);
  Child* child2 = dynamic_cast<Child*>(base2); // dynamic_cast如果发生了多态, 那么可以让基类转为派生类, 向下转换
}

// 常量转换
void test05() {
  const int* p = NULL;
  int* nwep = const_cast<int*>(p);

  int* p2 = NULL;
  const int* nwep2 = const_cast<const int*>(p2);

  int num = 10;
  int& numRef = num;

  const int& numRef2 = const_cast<const int&>(numRef);
}


int main() {

  test05();

  return EXIT_SUCCESS;
}