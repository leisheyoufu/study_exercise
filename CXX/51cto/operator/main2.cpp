// <<运算符的重载
#include <iostream>

using namespace std;

class Person {

  // 如果重载时想访问 person1 的私有成员, 那么全局函数要做Person的友元函数;
  friend ostream& operator<<(ostream& cout, Person& person1);

public:
  Person() {

  }

  Person(int a, int b) {
    this->personA = a;
    this->personB = b;
  }

  int personA;
  int personB;
};
// 必须要写成 全局函数;
ostream& operator<<(ostream &cout, Person &person1) {
  cout << "personA: " << person1.personA << "   personB: " << person1.personB << endl;

  return cout;
}

void test01() {
  Person person1(10, 10);

  cout << person1 << "hello world" << endl;
}

int main() {

  test01();

  //system("pause");

  return EXIT_SUCCESS;
}