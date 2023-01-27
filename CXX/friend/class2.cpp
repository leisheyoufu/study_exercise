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
	friend class B;
private:
	int m_a;
};
class B
{
public:
	B(int b=0):m_b(b){}
	friend class A;
	void Print(A& a);
private:
	int m_b;
};
void B::Print(A& a)
{
	cout << a.m_a << endl;
}
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
	b.Print(a);
    return 0;
}