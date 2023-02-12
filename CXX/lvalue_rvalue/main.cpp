#include<iostream>

void process_value(int& i) {
    std::cout << "LValue processed: " << i << std::endl;
}
void process_value(int&& i) {
    std::cout << "RValue processed: " << i << std::endl;
}

template <class T> void swap1(T& a, T& b)
{
       T tmp(a);   // copy a to tmp
       a = b;      // copy b to a
       b = tmp;    // copy tmp to b
}
//有了 std::move，swap 函数的定义变为 :
template <class T> void swap2(T& a, T& b)
{
       T tmp(std::move(a)); // move a to tmp
       a = std::move(b);    // move b to a
       b = std::move(tmp);  // move tmp to b
}


int main() {
    int a = 0;
    process_value(a);
    process_value(1);
    // LValue processed: 0
    // RValue processed: 1
    a = 3;
    process_value(a);
//     std::move基本等同于一个类型转换：
//   T& lvalue;
//   T&& rvalue = static_cast<T&&>(lvalue);
    process_value(std::move(a));
}
  

