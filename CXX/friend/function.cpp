#include<iostream>
using namespace std;
class A
{
public:
	A(int i=0):m_i(i){}
	int GetI()const
	{
		return m_i;
	}
	friend void Add(A& a, A& b);//将Add函数作为类A的友元，在类外部定义，（不能在类A中定义）
protected:
	//friend void Add(A& a, A& b);
private:
	int m_i;
	//friend void Add(A& a, A& b);
};
 
//想在Add函数中访问私有数据成员，又不想通过接口（公有函数）
void Add(A& a, A& b)
{
	cout << a.m_i + b.m_i << endl;
	//cout << a.GetI() + b.GetI() << endl;//接口
}
int main()
{
	A a(5);
	A b(8);
	Add(a, b);
    return 0;
}