// use of defaulted functions
#include <iostream>
using namespace std;

class A {
public:
    // A user-defined
    A(int x){
        cout << "This is a parameterized constructor";
    }

    // Using the default specifier to instruct
    // the compiler to create the default implementation of the constructor.
    A() = default;
};

int main(){
    A a;          //call A()
    A x(1);       //call A(int x)
    cout<<endl;

    template <typename T>
using Vec = std::vector<T, MyAlloc<T>>;

    return 0;
} 