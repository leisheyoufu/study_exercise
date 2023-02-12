#include <iostream>
#include <string>

using namespace std;

class Integer {
private:
    int* m_ptr;
public:
	Integer(int value)
        : m_ptr(new int(value)) {
        cout << "Call Integer(int value)有参" << endl;
    }
    //参数为常量左值引用的深拷贝构造函数，不改变 source.ptr_ 的值
    Integer(const Integer& source)
        : m_ptr(new int(*source.m_ptr)) {
        cout << "Call Integer(const Integer& source)拷贝" << endl;
    }
    //参数为左值引用的浅拷贝构造函数，转移堆内存资源所有权，改变 source.m_ptr的值 为nullptr
    Integer(Integer& source)
      : m_ptr(source.m_ptr) {
        source.m_ptr= nullptr;
        cout << "Call Integer(Integer& source)" << endl;
    }
    ~Integer() {
        cout << "Call ~Integer()析构" << endl;
        delete m_ptr;
    }

    int GetValue(void) { return *m_ptr; }
};

Integer getNum()
{
    Integer a(100);
    cout << "inner a address: " << &a << endl;
    return a;
}
int main(int argc, char const* argv[]) {
    Integer a(getNum()); 
    cout << "a=" << a.GetValue() << " addr: " << &a << endl;
    cout << "-----------------" << endl;
    Integer temp(10000);
    cout << "temp=" << temp.GetValue() << " addr: " << &temp << endl;
    Integer b(temp);
    cout << "b=" << b.GetValue() << " addr: " << &b << endl;
    cout << "-----------------" << endl;

    return 0;
}
/*
Call Integer(int value)有参
inner a address: 0x61fd38
a=100 addr: 0x61fd38
-----------------
Call Integer(int value)有参
temp=10000 addr: 0x61fd30
Call Integer(Integer& source)
b=10000 addr: 0x61fd28
-----------------
Call ~Integer()析构
Call ~Integer()析构
Call ~Integer()析构
*/
