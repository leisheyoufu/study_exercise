#include <variant>
#include<iostream>
#include<vector>

using namespace std;

void Print(std::variant<int, double, bool, string>& v) {
	int index = v.index();
	if (index == 0) {
		int value = std::get<0>(v);
		cout << "int: " << value << '\n'; 
	} else if (index == 1){
	    float value = std::get<1>(v);
		cout << "float: " << value << '\n';
	} else if (index == 2) {
        bool value = std::get<2>(v);
        cout << "bool: " << value << '\n';
    } else {
		std::string str = std::get<3>(v);
		cout << "str: " << str << '\n';
	}
}

int main() {
    using value = std::variant<int, double, bool, string>;
    // value a = "hello, world";
    // std::cout << a.index() << std::end;  //3， index 从0 开始

    // std::cout<<std::holds_alternative<std::string><<std::end;  //true

    // std::get<3>(value);
    // std::get<std::string>(value);
    
    // auto* v = std::get_if<std::string>(&value);
    // if (v){
    // std::cout<<*v<<std::end;  //"hello, world"
    // }

    std::vector<value> values = {0, true, 3.1415926, "hello world"};
    for(auto a : values) {
        Print(a);
    }
    value b = "this is string"s;
    Print(b);
}
/*
int: 0
bool: 1
float: 3.14159
bool: 1
str: this is string
*/

/*
 "hello"的类型是const char [6] ，它会衰减到const char * 。 从const char *到bool的转换是一个内置的转换，而从const char *到std::string转换是用户定义的转换，这意味着前者被执行。  
 由于您使用的是C ++> = 14，因此可以使用文本后缀s来表示std::string文本：  
using namespace std::string_literals;

var contains_string = "hello"s;

The type of "hello" is const char [6], which decays to const char *. The conversion from const char * to bool is a built-in conversion, while the conversion from const char * to std::string is a user-defined conversion, which means the former is performed. 
Since you're using C++ >= 14, you can use the literal suffix s to denote a std::string literal: 
using namespace std::string_literals;

var contains_string = "hello"s;
https://www.656463.com/wenda/wsmwdbzjstdstringzhwbool_95
*/

