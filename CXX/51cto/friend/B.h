// 友元成员函数  B.h

#ifndef CLIONTEST_B_H
#define CLIONTEST_B_H

#include <iostream>
using namespace std;
// CL: 这里不能include A.h
class A;

class B {
public:
    B();
    ~B();

    void func(const A& aObj);  // 直有public 成员函数才能被用作友元
};

#endif //CLIONTEST_B_H