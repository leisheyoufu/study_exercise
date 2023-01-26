#include <iostream>
#include <string>
using namespace std;
 
class X
{
public:
	X()
	{
		cout << "X's constructor" << endl;
	}
	~X()
	{
		cout << "X's destructor" << endl;
	}
 
	void* operator new(size_t size, string str)
 
	{
		cout << "operator new size " << size << " with string " << str << endl;
		return ::operator new(size);
	}
	void operator delete(void* pointer)
	{
		cout << "operator delete" << endl;
		::operator delete(pointer);
	}
private:
	int num;
};
 
int main()
{
	X *p = new("A new class") X;
	delete p;
	getchar();
	system("pause");
	return 0;
}