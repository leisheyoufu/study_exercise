// = 赋值运算符重载
#include <iostream>
#include <string>

using namespace std;

class Person {

public:
  Person(int a) {
    this->a = a;
  }

  int a;
};


void test01() {
  Person person1(19), person2(20);

  person1 = person2;

  cout << "person1.a: " << person1.a << endl;
}

class Person2 {

public:
  Person2(const char* name) {
    this->name = new char[strlen(name) + 1];
    strcpy(this->name, name);
  }

  Person2& operator=(const Person2& person) {
    if (this->name != NULL) {
      delete[] this->name;
      this->name = NULL;
    }

    this->name = new char[strlen(person.name) + 1];
    strcpy(this->name, person.name);

    return *this;
  }

  ~Person2() {
    if (this->name != NULL) {
      delete[] this->name;
      this->name = NULL;
    }
  }

  char* name;
};

void test02() {
  Person2 person1("roger");

  Person2 person2("rei ri");

  Person2 person3("jia ba");

  person3 = person2 = person1;

  cout << "person1.name: " << person1.name << endl;
  cout << "person2.name: " << person2.name << endl;
  cout << "person3.name: " << person3.name << endl;
}

int main() {

  //test01();

  test02();

  return EXIT_SUCCESS;
}