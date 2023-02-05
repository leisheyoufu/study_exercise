#include <memory>
#include <iostream>
using namespace std;

template <typename T>
void printX(T& lValue)
{
    cout << "lValue " << lValue << endl;
}

template  <typename T>
void printX(T&& rValue)
{
    cout << "rValue " << rValue << endl;
}

template <typename T>
void TestRValue(T && nValue)
{
    printX(nValue);
    printX(forward<T>(nValue));
    printX(move(nValue));
}
// lValue 4
// rValue 4
// rValue 4
// lValue 100
// lValue 100
// rValue 100
// lValue 100
// rValue 100
// rValue 100
int main(int argc, char *argv[])
{
    int nValue = 100;
    TestRValue(4); // 4 传给 nValue 变成了左值
    TestRValue(nValue);
    TestRValue(forward<int>(nValue));
}