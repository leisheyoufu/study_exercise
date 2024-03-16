// person.hpp 文件
#pragma once

#include <iostream>
#include <string>

using namespace std;


template<class T1, class T2>
class Person {

public:
  Person(T1 name, T2 age);

  void showPerson();

  T1 name;
  T2 age;
};


template<class T1, class T2>
Person<T1, T2>::Person(T1 name, T2 age) {
  this->name = name;
  this->age = age;
}


template<class T1, class T2>
void Person<T1, T2>::showPerson() {
  cout << "姓名: " << this->name << " 年龄: " << this->age << endl;
}