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
    Object(const Object * obj) : str(str)
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
};

Test::Test() {
         cout << "Test: Constructor called"<< endl;
    }
Test::Test(int a) {
         cout << "Test: Destructor called"<< endl;
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
    auto p1 = new Test;
    shared_ptr<Test> sp(p1);
     std::cout << sp.use_count() << std::endl; // 打印引用计数
    {
        std::shared_ptr<Test> sp2(sp); // 创建另一个智能指针
        std::cout << sp.use_count() << std::endl; // 打印引用计数
    } // sp2生命周期结束，sp引用计数减1
    std::cout << sp.use_count() << std::endl; // 打印引用计数
}
