#include <iostream>
#include <functional>
using namespace std;
 
int TestFunc(int a, char c, float f)
{
    cout << a << endl;
    cout << c << endl;
    cout << f << endl;
 
    return a;
}
 
int main()
{
    auto bindFunc1 = bind(TestFunc, std::placeholders::_1, 'A', 100.1);
    bindFunc1(10);
 
    cout << "=================================\n";
 
    auto bindFunc2 = bind(TestFunc, std::placeholders::_2, std::placeholders::_1, 100.1);
    bindFunc2('B', 10);
 
    cout << "=================================\n";
 
    auto bindFunc3 = bind(TestFunc, std::placeholders::_2, std::placeholders::_3, std::placeholders::_1);
    bindFunc3(100.1, 30, 'C');
 
    return 0;
}
/*
上面这段代码主要说的是bind中std::placeholders的使用。 std::placeholders是一个占位符。当使用bind生成一个新的可调用对象时，std::placeholders表示新的可调用对象的第 几个参数和原函数的第几个参数进行匹配，这么说有点绕。比如：
*/