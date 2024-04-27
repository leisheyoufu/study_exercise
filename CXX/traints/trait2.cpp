// 偏特化（Patial Spcialization

#include<iostream>
#include<vector>

using namespace std;
template<typename T>
struct my_is_pointer {
    static const bool value = false;
};

template<typename T>
struct my_is_pointer<T*> {
    static const bool value = true;
};

// 模板特化（Template Specialization


template<typename T>
typename T::value_type top(const T &c) // CL：vector<int> value_type 就是int, T是vector
{
    if (!c.empty())
        return c.back();
    else
        return typename T::value_type();
}

int main() {
    my_is_pointer<int> p1;
    cout << p1.value << endl;  // 输出 0，使用原始模板
    my_is_pointer<int*> p2;
    cout << p2.value << endl;  // 输出 1，使偏特化模板，因为指定了 int * 类型的参数

    vector<int> vec;
    cout << top<vector<int> >(vec) << endl;  // 输出0
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    cout << top<vector<int> >(vec) << endl;  // 输出3
    return 0;
}
