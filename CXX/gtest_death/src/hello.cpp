#include <iostream>
#include "hello.h"

namespace death {

HelloWorld::HelloWorld()
{
    std::cout << "Constructed" << std::endl;
}
std::string HelloWorld::SayHello()
{
    return "hello world";
}

void HelloWorld::Die()
{
    int *ptr = 0;
    *ptr = 1;
}
}
