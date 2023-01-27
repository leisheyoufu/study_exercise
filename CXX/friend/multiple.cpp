#include<iostream>
using namespace std;
class B;//前向引用声明
class C;
class A
{
public:
	A(int i = 0) :m_i(i) {}
	friend int Sum(A& a, B& b, C& c);
private:
	int m_i;
};
class B
{
public:
	B(int j = 0) :m_j(j) {}
	friend int Sum(A& a, B& b,C& c);
private:
	int m_j;
};
class C
{
public:
	C(int k = 0) :m_k(k) {}
	friend int Sum(A& a, B& b,C&c);
private:
	int m_k;
};
int Sum(A& a, B& b,C&c)
{
	return a.m_i + b.m_j+c.m_k;
}
int main()
{
	A a(10);
	B b(20);
	C c(30);
	cout << Sum(a, b, c) << endl;
    return 0;
}