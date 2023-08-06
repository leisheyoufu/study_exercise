#include<iostream>
#include<memory>
using namespace std;
class Object {
public:
    // C++中的explicit关键字通常用来将构造函数标记为显式类型转换，即在创建对象的时候不能进行隐式类型转换。
    explicit Object(const string& str) : str(str) 
    {
        cout << "Constructor " << str << endl;
    }
    Object(const Object * obj) : str(obj->str)
    {
        cout << "Constructor obj "<< str << endl;
    }
    Object()
    {
        cout << "Default constructor" << endl;
    }
    ~Object()
    {
        cout << "Destructor" << endl;
    }
    Object(const Object& rhs)
    {
        cout << "Copy constructor..." << endl;
    }
private:
    string str;
};

class Test {
public:
    Test();
    explicit Test(int a);
    ~Test();
    int a;    
};

Test::Test() {
         cout << "Test: Constructor called"<< endl;
    }
Test::Test(int a) : a(a) {
         cout << "Test: Constructor a called"<< endl;
    }       
Test::~Test() {
         cout << "Test: Destructor called"<< endl;
    }    
int main()
{
    cout << "Create smart_ptr using make_shared..." << endl;
    auto ptr_res1 = make_shared<Object>("make_shared");
    cout << "Create smart_ptr using make_shared: done, count: " << ptr_res1.use_count() << endl;
    cout << "Create smart_ptr using new..." << endl;
    shared_ptr<Object> ptr_res2(new Object("new"));
    cout << "Create smart_ptr using new: done, count: " << ptr_res2.use_count() << endl;

    cout << "Create shared ptr" << endl;
    auto p1 = new Test(3);
    shared_ptr<Test> sp(p1);
     std::cout << sp.use_count() << std::endl; // 打印引用计数
    {
        std::shared_ptr<Test> sp2(sp); // 创建另一个智能指针
        std::cout << sp.use_count() << std::endl; // 打印引用计数
    } // sp2生命周期结束，sp引用计数减1
    std::cout << sp.use_count() << std::endl; // 打印引用计数
    cout << "p1.a=" << p1->a << endl;
    cout << "sp.a=" << sp->a << endl;
    // p1 was desconstructed after sp.use_count() == 0
}

/*
Create smart_ptr using make_shared...
Constructor make_shared
Create smart_ptr using make_shared: done, count: 1
Create smart_ptr using new...
Constructor new
Create smart_ptr using new: done, count: 1
Create shared ptr
Test: Constructor a called
1
2
1
p1.a=3
sp.a=3
Test: Destructor called
Destructor
Destructor

*/