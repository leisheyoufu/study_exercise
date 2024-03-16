// 析构与构造函数的调用顺序
#include <iostream>

using namespace std;


class Base {

public:
  int a;
protected:
  int b;
private:
  int c;

};

// 实际上 子类中会继承父类的 private 成员变量, 只是被编译器给隐藏起来了, 所以访问不到私有成员;
class Son : public Base {

public:
  int d;

};

void test01() {
  cout << sizeof(Base) << endl;
  cout << sizeof(Son) << endl;
}


class Base2 {

public:
  Base2(int a) {
    cout << "Base2 有参构造函数 调用" << endl;
    this->a = a;
  }

  ~Base2() {
    cout << "Base2 析构函数 调用" << endl;
  }

  int a;
};


class Son2 : public Base2 {
public:
  Son2(int a): Base2(a) { // 利用初始化列表方式 显示调用 有参构造
    cout << "Son2 有参构造函数 调用" << endl;
  }

  ~Son2() {
    cout << "Son2 析构函数 调用" << endl;
  }
};

void test02() {
  Son2 son2(1000); // 构造函数先调用父类, 后调用子类; 析构函数先调用父类, 后调用子类; 另外 子类不会继承父类的构造函数和析构函数;
}

int main() {

  test02();

  return EXIT_SUCCESS;
}

/*
Base2 有参构造函数 调用
Son2 有参构造函数 调用
Son2 析构函数 调用
Base2 析构函数 调用

*/