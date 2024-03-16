// *、-> 指针运算符重载
#include <iostream>
#include <string>

using namespace std;

class Person {

public:
  Person(int age, string name) {
    this->age = age;
    this->name = name;
  }

  Person(const Person& person) {
    this->age = person.age;
    this->name = person.name;
  }

  int showAge() {

    cout << "person age: " << this->age << endl;
    
    return this->age;
  }

  string showName(string name) {
    cout << "person name: " << this->name << endl;

    return this->name;
  }

  ~Person() {
    cout << this->name << " 析构函数 调用" << endl;
  }

private:
  int age;
  string name;

};


class SmartPointer {

public:
  SmartPointer(Person *person) {
    this->person = person;
  }
  
  // 重载 -> 让智能指针对象 像Person *p 一样去使用
  Person* operator->() {
    return this->person;
  }

  // 重载 *
  Person& operator*() {

    return *this->person;
  }

  ~SmartPointer() {
    if (this->person != NULL) {
      delete this->person;
      this->person = NULL;
    }
  }

private:
  Person* person;

};

void test01() {

  Person person1(19, "person1"); // 析构函数会 在栈区被释放后调用

  person1.showAge();

  Person* person2 = new Person(20, "person2");

  person2->showAge();

  Person* person3 = new Person(*person2); // 深拷贝

  delete person2;

  delete person3;
}

void test02() {
  SmartPointer smartPointer(new Person(21, "roger"));

  smartPointer->showAge();
  (*smartPointer).showAge();
}


int main() {

  //test01();

  test02();

  return EXIT_SUCCESS;
}