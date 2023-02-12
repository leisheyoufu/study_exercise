#include <iostream>
void print() {} // 1 CL: 递归关系不能省
template<typename T, typename... Types> // 2
void print(const T& firstArg, const Types&... args) { // 3
    std::cout << firstArg << std::endl;
    print(args...); // 4
}

// template <typename... Types>
// void print2(const Types&... args) {
//     if (sizeof(args) == 0) {
//         return;
//     }
//     std::cout << args[0] << std:endl;
//     print2(args...);
// /* --- */
// }

template <class T>
void printarg(T t)
{
   std::cout << t << std::endl;
}
 
 // 这种方式需要借助逗号表达式和初始化列表。比如前面print的例子可以改成这样：
template <class ...Args>
void expand(Args... args)
{
   int arr[] = {(printarg(args), 0)...};
   for(auto item : arr) {
       std::cout << "expand: " << item << std::endl;
   }
}
// expand函数中的逗号表达式：(printarg(args), 0)，也是按照这个执行顺序，先执行printarg(args)，再得到逗号表达式的结果0。同时还用到了C++11的另外一个特性——初始化列表，通过初始化列表来初始化一个变长数组, {(printarg(args), 0)...}将会展开成

// ((printarg(arg1),0), (printarg(arg2),0), (printarg(arg3),0), etc... )

// 最终会创建一个元素值都为0的数组int arr[sizeof...(Args)]。由于是逗号表达式，在创建数组的过程中会先执行逗号表达式前面的部分printarg(args)打印出参数，也就是说在构造int数组的过程中就将参数包展开了，这个数组的目的纯粹是为了在数组构造的过程展开参数包。我们可以把上面的例子再进一步改进一下，将函数作为参数，就可以支持lambda表达式了，从而可以少写一个递归终止函数了，具体代码如下：
// ————————————————
// 版权声明：本文为CSDN博主「wangx_x」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
// 原文链接：https://blog.csdn.net/wangx_x/article/details/122374408


template<class F, class... Args>
void expand2(const F& f, Args&&...args) 
{
//这里用到了完美转发，关于完美转发，
//读者可以阅读参考文献中的文章《通过4行代码看右值引用》
  auto array = std::initializer_list<int>{(f(std::forward<Args>(args)),0)...};
  for(auto item : array) {
      std::cout << "initializer_list item: " << item << std::endl;
  }
}



template<typename T>
T sum(T t)
{
    return t;
}
template<typename T, typename ... Args>
T sum (T first, Args... args)
{
    return first + sum<T>(args...);
}


int main() {
    print("dfafda", 's', 123);
    //print2("dfafda", 's', 123);
    
    std::cout << "sum:  你好" << std::ios::dec << sum(1,2,3,4) << std::endl; //10
    expand(1,2,3,4);
    expand2([](int i){std::cout<<i<<std::endl;}, 1,2,3);
}
// Result
// dfafda
// s
// 123