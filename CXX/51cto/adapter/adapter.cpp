#include <iostream>

/*
 * 适配器模式
 * 适用于双方都不适合修改的时候
 */

class Target {
public:
    virtual void request() {
        std::cout << "Target request." << std::endl;
    }
};
class Adaptee {
public:
    virtual void specialRequest() {
        std::cout << "Adaptee specialRequest." << std::endl;
    }
};

class Adapter: public Target {
public:
    Adapter() {
        this->adaptee = new Adaptee();
    }
    virtual ~Adapter() {
        delete this->adaptee;
    }
    virtual void request() {
        Target::request();
        this->adaptee->specialRequest();
    }

private:
    Adaptee* adaptee;
};

int main() {

    Adapter* adapter = new Adapter();
    adapter->request();

    delete adapter;

    return 0;
}