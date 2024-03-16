#include <iostream>

void tqz_typeConvert() {

//    // 类型转换 (C++风格)
//    double valueDouble = 100.34f;
//    int valueInt = static_cast<int>(valueDouble);

//    // 类型转换 (去掉类型 的const 修饰), 但是当初始值是常量的情况下不要这么做转换;
//    const int a = 10;
//    const int a2 = 20;
//    const int* pointA = &a;
//    int *b = const_cast<int *>(pointA);
//
//    // *pointA = 11; // 报错 (编译就会过不去)
//    *b = 11;
//
//    pointA = &a2;
//    b = const_cast<int *>(&a2);
//
//    std::cout << "*pointA: " << *pointA << std::endl;
//    std::cout << "*b: " << *b << std::endl;

//    int i = 10;
//    int *pi = &i;
//
//    // 这种转换很万能, 但要慎用, 转换结果不可控;
//    void *pvoid = reinterpret_cast<void *>(pi); // 只能转指针
//    int *pi2 = reinterpret_cast<int *>(pvoid);
}

int main() {

    tqz_typeConvert();

    return 0;
}