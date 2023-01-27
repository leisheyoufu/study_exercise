#include<iostream>
using namespace std;
class B;
class A
{
public:
	A(int a = 0) :m_a(a) {}
	void print(B& b);
	void test(B& b);
	void show(B& b);
private:
	int m_a;
};
class B
{
public:
	B(int b=0):m_b(b){}
	friend class A;
private:
	int m_b;
};
 
void A::print(B& b)
{
	cout << "a::print:" << b.m_b << endl;
}
void A::test(B& b)
{
	cout << "a::test:" << b.m_b << endl;
}
void A::show(B& b)
{
	cout << "a::show:" << b.m_b << endl;
}
int main()
{
	A a(2);
	B b(10);
	a.print(b);
	a.show(b);
	a.test(b);
    return 0;
}