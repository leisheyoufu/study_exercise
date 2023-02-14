#include<iostream>
#include<string>
#include<tuple>
using namespace std;
class Person {
    int age;
    string name;

public:
    Person(int age= 10, const string& name = "xiaoming") {
        this->age = age;
        this->name = name;
    }
    friend ostream &operator<<(ostream &os, const Person &person) {
        os << "Person{age: " << person.age << " name: " << person.name << "}";
        return os;
    }
};

class TestMultipleRet {
	// 返回多个值的函数
    tuple<int, string, Person> test() {
        return {1,"xiaoming", Person()};
    }

public:
    void client() {
    	// 获取各个返回值
        auto [age, name, person] = test();
        cout << age << " " << name << " " << person << endl;
    }
};

int main() {
    TestMultipleRet r;
    r.client();
    return 0;
}
