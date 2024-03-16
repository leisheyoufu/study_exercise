// 继承方式
#include <iostream>

using namespace std;

class Base1 {
public:
  int a;
protected:
  int b;
private:
  int c;
};

class Son1: public Base1 {

public:
  void publicFunction() {
    cout << this->a << endl; // 父类中 共有的属性 可继承, 继承后是 public;
    cout << this->b << endl; // 父类中 保护的属性 可继承, 继承后是 protected;
    //cout << this->c << endl; // 父类中私有的属性 不可继承;
  }
};

void test01() {

  Son1 son1;

  son1.a = 10;

  cout << son1.a << endl;
}


class Base2 {
public:
  int a = 0;
protected:
  int b = 0;
private:
  int c = 0;
};

class Son2 : protected Base2 {

public:
  void func() {
    cout << this->a << endl; // 父类中 共有的属性 可继承, 继承后是 protected
    cout << this->b << endl; // 父类中 保护的属性 可继承, 继承后是 protected
    //cout << this->c << endl; // 父类中私有的属性 不可继承;
  }
};

class GrandSon2 : public Son2 {

public:
  void publicFunction() {
    cout << this->a << endl;
    cout << this->b << endl;
  }
protected:
  void protectedFunction() {
    cout << this->a << endl;
    cout << this->b << endl;
  }
private:
  void privateFunction() {
    cout << this->a << endl;
    cout << this->b << endl;
  }
};
void test02() {
  Son2 son2;

  GrandSon2 grandSon2;

  //son1.a = 10; // 继承后的 a 是保护属性, 外部不可以访问
  //cout << son1.a << endl;
  //grandSon2.a = 10; // 再次继承后的 a 也是保护属性, 外部不可以访问
}


class Base3 {
public:
  int a;
protected:
  int b;
private:
  int c;
};

class Son3 : private Base3 {

public:
  void publicFunction() {
    cout << this->a << endl; // 父类中 共有的属性 可继承, 继承后是 private;
    cout << this->b << endl; // 父类中 保护的属性 可继承, 继承后是 private;
    //cout << this->c << endl; // 父类中私有的属性 不可继承;
  }
};

class GrandSon3 : public Son3 {

public:
  void publicFunction() {
    //cout << this->a << endl; // 父类中 私有的属性 不可继承;
    //cout << this->b << endl; // 父类中 私有的属性 不可继承;
    //cout << this->c << endl; // 父类中 私有的属性 不可继承;
  }

};

void test03() {
  Son3 son3;

  son3.publicFunction();
}

int main() {

  test03();

  return EXIT_SUCCESS;
}

/*
1
41713760

*/