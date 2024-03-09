// 友元成员函数  B.cpp

#include "A.h"
#include "B.h"

B::B() {
    cout << "B()" << endl;
}
B::~B() {
    cout << "~B()" << endl;
}

void B::func(const A& aObj) {
    aObj.privateFunction();
}