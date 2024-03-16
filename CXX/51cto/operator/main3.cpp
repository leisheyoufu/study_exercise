// ++、-- 前后置运算符的重载
#include <iostream>

using namespace std;

class MyInteger {

  friend ostream& operator<<(ostream& cout, MyInteger& integer);

public:

  MyInteger() {
    this->number = 0;
  }

  // 前置 ++重载
  MyInteger& operator++() {

    ++this->number;

    return *this;
  }

  // 后置 ++重载
  MyInteger& operator++(int) {

    this->number++;

    return *this;
  }

  // 前置 --重载
  MyInteger& operator--() {

    --this->number;

    return *this;
  }

  // 后置 --重载
  MyInteger& operator--(int) {
    
    this->number--;

    return *this;
  }

private:
  int number;

};

ostream& operator<<(ostream& cout, MyInteger &integer) {

  cout << integer.number;
  
  return cout;
}

// 前置 & 后置 ++ 运算符重载;
void test01() {
  MyInteger integer1, integer2;

  integer1++;
  cout << "integer1: " << integer1 << endl;
  
  ++integer2;
  cout << "integer2: " << integer2 << endl;
}

// 前置 & 后置 -- 运算符重载;
void test02() {

  MyInteger integer3, integer4;

  integer3--;
  cout << "integer3: " << integer3 << endl;

  --integer4;
  cout << "integer4: " << integer4 << endl;
}

int main() {

  test02();

  return EXIT_SUCCESS;
}