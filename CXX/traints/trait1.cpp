#include<iostream>

using namespace std;
template<typename T>
struct my_is_void {
    static const bool value = false;
};

template<>
struct my_is_void<void> {
    static const bool value = true;
};

// 模板特化（Template Specialization

int main() {
    my_is_void<bool> t1;
    cout << t1.value << endl;  // 输出0
    my_is_void<void> t2;
    cout << t2.value << endl;  // 输出1
    return 0;
}
