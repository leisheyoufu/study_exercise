// 友元成员函数  A.h

#ifndef CLIONTEST_A_H
#define CLIONTEST_A_H

#include <iostream>
using namespace std;

#include "B.h"

class A {
public:
    A();
    ~A();
    
private:
    friend void B::func(const A& aObj);
    void privateFunction() const;
};


#endif //CLIONTEST_A_H