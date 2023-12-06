#include <iostream>
#include <memory>

/*

weak_ptr是C++11标准库中的一个类，用于解决shared_ptr的循环引用问题。weak_ptr可以从一个shared_ptr或另一个weak_ptr对象构造，它不会增加引用计数，也不会影响所指向对象的生命周期。weak_ptr可以通过lock()方法获取一个shared_ptr对象，如果获取成功，则说明所指向的对象仍然存在，否则说明所指向的对象已经被销毁。

因此，我们可以通过lock()方法判断一个weak_ptr所指向的shared_ptr是否已经失效。

*/

int main() {
    std::shared_ptr<int> sp(new int(42));
    std::weak_ptr<int> wp(sp);

    sp.reset(); // 释放shared_ptr对象

    std::shared_ptr<int> p = wp.lock(); // 获取shared_ptr对象
    if (p) {
        std::cout << "shared_ptr is valid\n";
    } else {
        std::cout << "shared_ptr is invalid\n";
    }

    return 0;
}