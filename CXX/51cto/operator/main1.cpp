// +运算符的重载
#include <iostream>

using namespace std;

class Person {

public:
  Person() {

  }

  Person(int a, int b) : personA(a), personB(b) {

  }

  // +号运算符重载, 成员函数
  //Person operator+(Person& person) {

  //  this->personA += person.personA;
  //  this->personB += person.personB;

  //  return *this;
  //}

  int personA;
  int personB;
};

// 利用全局函数 进行+号运算符的重载;
Person operator+(Person& person1, Person& person2) {
  Person tempPerson;

  tempPerson.personA = person1.personA + person2.personA;
  tempPerson.personB = person1.personB + person2.personB;

  return tempPerson;
}

Person operator+(Person& person1, int number) {
  Person tempPerson;

  tempPerson.personA = person1.personA + number;
  tempPerson.personB = person1.personB + number;

  return tempPerson;
}

void test01() {

  Person person1(10, 10);
  Person person2(10, 10);

  Person tempPerson = person1 + person2;

  cout << "tempPerson.personA: " << tempPerson.personA << endl;
  cout << "tempPerson.personB: " << tempPerson.personB << endl;

  Person person3 = person1 + 10;
  cout << "person3.personA: " << person3.personA << endl;
  cout << "person3.personB: " << person3.personB << endl;
}

int main() {

  test01();

  //system("pause");

  return EXIT_SUCCESS;
}