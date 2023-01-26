#include <iostream>
using namespace std;
class A
{
public:
	A()
	{
		cout << "A's constructor" << endl;
	}
	~A()
	{
		cout << "A's destructor" << endl;
	}
	void show()
	{
		cout << "num:" << num << endl;
	}
private:
	int num;
};
 
int main()
{
	char mem[100];
	mem[0] = 'A';
	mem[1] = '\0';
	mem[2] = '\0';
	mem[3] = '\0';
	cout << (void*)mem << endl;
	A* p = new (mem)A;
	cout << p << endl;
	p->show();
	p->~A();
	getchar();
	system("pause");
	return 0;
}