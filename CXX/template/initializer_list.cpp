#include <iostream>

void print(std::initializer_list<int> vals) {
    for (auto ite = vals.begin(); ite!=vals.end(); ++ite) {
        std::cout << *ite << "\n";
    }
}

int main() {
    print( {1,2,3,4} );				// 使用initalizer_list传参
}

// 即 {} 即可形成一个 initializer_list

// 不同于前面的 variadic template，这里的 initializer_list 需要的是固定类型 T 的任意多个参数。也可以看做是一种容器。

// initializer_list背后由array构建。

// intializer_list如果被拷贝，会是浅拷贝（引用语义）
