#include <iostream>

using namespace std;

class Animal {

public:
  virtual void speak() { // 动态联编
    cout << "Animal speak" << endl;
  }

};

class Cat : public Animal {

public:
  void speak() {
    cout << "Cat speak" << endl;
  }

};

// 调用doSpeak, speak函数的地址早就绑定好了, 早绑定, 静态联编, 编译阶段就确定好了地址;
// 如果想调用猫的speak, 不能提前绑定函数地址, 需要在运行时候再去确定函数地址;
// 动态联编: doSpeak方法改为虚函数, 在父类上声明虚函数, 发生了多态;
// 多态: 父类的指针 指向子类对象;
void doSpeak(Animal& animal) {

  animal.speak();
}

void test01() {
  Animal animal;
  Cat cat;

  doSpeak(animal);
  doSpeak(cat);
}

int main() {

  test01();

  return EXIT_SUCCESS;
}

/*
Animal speak
Cat speak
*/