#include <iostream>
#include <cstring>

using namespace std;


class Animal {

public:

  Animal() {
    cout << "Animal alloc" << endl;
  }

  virtual void speak() {
    cout << "Animal speak" << endl;
  }

   //普通析构 不会调用子类的析构, 所以可能会导致释放不干净;
  // 利用 虚析构 来解决这个问题;
  //virtual ~Animal() {
  //  cout << "Animal dealloc" << endl;
  //}

  // 纯虚函数 写法如下: 类内声明, 类外实现;
  // 如果函数中出现了 纯虚析构函数, 那么这个类也算抽象类;
  virtual ~Animal() = 0;
};
Animal::~Animal() {
  cout << "Animal pure dealloc" << endl;
}


class Cat :public Animal {

public:

  Cat(const char* name) {

    cout << "Cat alloc" << endl;

    this->name = new char[strlen(name) + 1];
    strcpy(this->name, name);
  }

  virtual void speak() {
    cout << "Cat speak" << endl;
  }


  ~Cat() {

    cout << "Cat dealloc" << endl;

    if (this->name != NULL) {
      delete[] this->name;
      this->name = NULL;
    }
  }

  char* name;
};

void test01() {

  Animal* animal = new Cat("some cat");

  animal->speak();

  delete animal;
}


int main() {

  test01();
  
  return EXIT_SUCCESS;
}