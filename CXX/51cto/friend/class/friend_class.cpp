#include<iostream>

using namespace std;

// 友元类

class B;

class A {
public:
    A() {
        cout << "A()" << endl;
    }
    ~A() {
        cout << "~A()" << endl;
    }

private:
    friend class B;
    void privateFunction() const {
        cout << "A privateFunction()" << endl;
    };
};

class B {
public:
    B() {
        cout << "B()" << endl;
    }
    ~B() {
        cout << "~B()" << endl;
    }

    void someFunc(const A& aObj) {
        // CL: 是A的友元类才能访问到A的私有方法
        aObj.privateFunction();
    }
};

int main() {

    B().someFunc(A());

    return EXIT_SUCCESS;
}