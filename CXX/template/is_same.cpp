#include<iostream>
#include <type_traits>
template<typename T>
T* PrintType(int* x)
{
	if (std::is_same<T, int>::value) {
		std::cout << "int type" << std::endl;
		return reinterpret_cast<T*>(x);
	}
	else {
		std::cout << "not int type" << std::endl;
		return nullptr;
	}
}
 
template<typename T>
const T* PrintType(const int* x)
{
	if (std::is_same<T, int>::value) {
		std::cout << "const int type" << std::endl;
		return reinterpret_cast<const T*>(x);
	}
	else {
		std::cout << "not const int type" << std::endl;
		return nullptr;
	}
}
 
void TestTemplateType()
{
	int x = 5;
	const int y = 6;
	PrintType<int>(&x);
	PrintType<double>(&x);
	PrintType<int>(&y);
	PrintType<double>(&y);
 
}


int main(int argc, char* argv[])
{
	TestTemplateType(); 
    int b = 1;
    static_assert(std::is_same_v<int, decltype(b)>, "error"); // C++17
	return 0;
}
