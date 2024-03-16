// C++ 的 .cpp 文件
#include <iostream>

#include "person.hpp"

using namespace std;

void test01() {

  // 类模板不要做分文件编写, 写到一个文件中即可, 在同一个文件中进行声明和实现， 最后把.h后缀名改为.hpp;
  Person<string, int>person("猪八戒", 10);
  person.showPerson();
}


int main() {

  test01();

  return EXIT_SUCCESS;
}