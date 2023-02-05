#include <iostream> 
using namespace std; 
class A { 
public: 
    A(int) {} 

    // Declare the conversion constructor as a  deleted function. Without this step,  
    // even though A(double) isn't defined,  the A(int) would accept any double value
    //  for it's argumentand convert it to an int 
    A(double) = delete;  
}; 
int main() { 
    A A1(1); 
    // Error, conversion from  double to class A is disabled. 
    A A2(100.1); 
    return 0; 
} 
