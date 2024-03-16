// == & != 关系运算符的重载
#include <iostream>
#include <string>

using namespace std;

class Person {

public:

  Person(string name, int age) {
    this->name = name;
    this->age = age;
  }

  bool operator==(Person &person) {
    return (this->name == person.name && this->age == person.age);
  }

  bool operator!=(Person& person) {
    return !(this->name == person.name && this->age == person.age);
  }

  string name;
  int age;

};

void test01() {

  Person person1("roger", 19), person2("roger", 19), person3("rei ri", 21);

  cout << ((person1 == person2) ? "person1 == person2" : "person1 != person2") << endl;
  cout << ((person2 == person3) ? "person2 == person3" : "person2 != person3") << endl;
}

int main() {
  
  test01();

  return EXIT_SUCCESS;
}