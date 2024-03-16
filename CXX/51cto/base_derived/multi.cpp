// 多继承
#include <iostream>
#include <string>

using namespace std;


class Animal {
public:
  int age;
};

class Sheep : virtual public Animal { // 虚基类
  
};

class Tuo : virtual public Animal {

};

class SheepTuo : public Sheep, public Tuo {

};


// 菱形继承的解决方案 利用虚基类
// 操作的是共享的一份数据
void test01() {

  SheepTuo sheepTuo;
  sheepTuo.Sheep::age = 10;
  sheepTuo.Tuo::age = 20;

  cout << sheepTuo.Sheep::age << endl;
  cout << sheepTuo.Tuo::age << endl;
  cout << sheepTuo.age << endl; // 可以直接访问了
}

int main() {

  test01();

  return EXIT_SUCCESS;
}

/*
20
20
20
*/