#include<iostream>
using namespace std;
class C;
class A;
class B
{
public:
	B(int j = 0) :m_j(j) {}
	void Sub(A& a, B& b, C& c);
	void Print(A& a);
private:
	int m_j;
};
class A
{
public:
	A(int i = 0) :m_i(i) {}
	friend void B::Sub(A& a, B& b, C& c);
	friend void B::Print(A&a);
private:
	int m_i;
};
class C
{
public:
	C(int k = 0) :m_k(k) {}
	friend void B::Sub(A& a, B& b, C& c);
private:
	int m_k;
};
void B::Sub(A& a,B&b,C&c)
{
	cout << a.m_i - m_j +c.m_k<< endl;
}
void B::Print(A&a)
{
	cout << a.m_i << endl;
}
int main()
{
	A a(10);
	B b(20);
	C c(30);
	b.Sub(a,b,c);
	b.Print(a);
    return 0;
}