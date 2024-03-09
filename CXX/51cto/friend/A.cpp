// 友元成员函数  A.cpp

#include "A.h"

A::A() {
    cout << "A()" << endl;
}

A::~A() {
    cout << "~A()" << endl;
}

void A::privateFunction() const {
    cout << "A privateFunction()" << endl;
};