#include<iostream>
using namespace std;

int main()
{
    [] { std::cout << "Hello Lambda" << std::endl; };

    [] { std::cout << "Hello Lambda" << std::endl; }();

    auto l = [] { std::cout << "Hello Lambda" << std::endl; };
    l();

    int id = 0;
    auto f = [id] () mutable {
        std::cout << "id: " << id << std::endl;
        ++id;
    };
    id = 42;
    f();
    f();
    std::cout << id << std::endl;
    return 0;
}
/*
Hello Lambda
Hello Lambda
id: 0
id: 1
42
*/