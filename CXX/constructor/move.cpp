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
    
    Integer(const Integer& source)
        : m_ptr(new int(*source.m_ptr)) {
        cout << "Call Integer(const Integer& source)拷贝" << endl;
    }

	Integer(Integer&& source)
	  : m_ptr(source.m_ptr) {
	    source.m_ptr= nullptr;
	    cout << "Call Integer(Integer&& source)移动" << endl;
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
    // CL: 编译器优化了，让a 和getNum返回的为同一个地址
    Integer a(getNum()); 
    cout << "a=" << a.GetValue() << " addr: " << &a << endl;
    cout << "-----------------" << endl;
    Integer temp(10000);
    Integer b(temp);
    cout << "b=" << b.GetValue() << endl;
    cout << "-----------------" << endl;

    cout << "------using std::move -----------" << endl;
    Integer c(getNum()); 
    cout << "c=" << c.GetValue() << " addr: " << &c << endl;
    cout << "-----------------" << endl;
    Integer temp2(10000);
    Integer d(std::move(temp2));
    cout << "d=" << d.GetValue() << endl;
    cout << "-----------------" << endl;

    return 0;
}


/*
Call Integer(int value)有参
inner a address: 0x61fd38
a=100 addr: 0x61fd38
-----------------
Call Integer(int value)有参
Call Integer(const Integer& source)拷贝
b=10000
-----------------
------using std::move -----------
Call Integer(int value)有参
inner a address: 0x61fd20
c=100 addr: 0x61fd20
-----------------
Call Integer(int value)有参
Call Integer(Integer&& source)移动
d=10000
-----------------
Call ~Integer()析构
Call ~Integer()析构
Call ~Integer()析构
Call ~Integer()析构
Call ~Integer()析构
Call ~Integer()析构
*/