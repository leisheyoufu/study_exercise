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
		// cl size 是X 需要的对象的大小，这里试有int num, 所以是4
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

/*
operator new size 4 with string A new class
X's constructor
X's destructor
operator delete
*/