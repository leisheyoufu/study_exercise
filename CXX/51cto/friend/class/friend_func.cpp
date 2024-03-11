// 友元函数
#include<iostream>

using namespace std;

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
    friend void func(const A& aObj, const B& bObj);
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

private:
    friend void func(const A& aObj, const B& bObj);
    void privateFunction() const {
        cout << "B privateFunction()" << endl;
    };

};

void func(const A& aObj, const B& bObj) {
    aObj.privateFunction();
    bObj.privateFunction();
}

int main() {

    func(A(), B());

    return EXIT_SUCCESS;
}