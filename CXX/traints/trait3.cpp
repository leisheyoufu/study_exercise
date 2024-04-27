#include<iostream>
#include<vector>
using namespace std;

template<class IterT>
struct my_iterator_traits {
    typedef typename IterT::value_type value_type;
};

// 偏特化版本
template<class IterT>
struct my_iterator_traits<IterT*> {
    typedef IterT value_type;
};


void fun(int a) {
    cout << "fun(int) is called" << endl;
}

void fun(double a) {
    cout << "fun(double) is called" << endl;
}

void fun(char a) {
    cout << "fun(char) is called" << endl;
}

int main() {
    my_iterator_traits<vector<int>::iterator>::value_type a;
    fun(a);  // 输出 fun(int) is called
    my_iterator_traits<vector<double>::iterator>::value_type b;
    fun(b);  // 输出 fun(double) is called
    my_iterator_traits<char*>::value_type c;
    fun(c);  // 输出 fun(char) is called

    return 0;
}

/*
我们来解释 my_iterator_traits<vector<int>::iterator>::value_type a; 语句的含义。
vector<int>::iterator 为vector<int> 的迭代器，该迭代器包含了 value_type 的声明，由 vector 的代码可以知道该迭代器的value_type 即为 int 类型。
接着，my_iterator_traits<vector<int>::iterator> 会采用 my_iterator_traits 的通用版本，即 my_iterator_traits<vector<int>::iterator>::value_type 使用 typename IterT::value_type 这一类型声明，这里 IterT 为 vector<int>::iterator，故整个语句萃取出来的类型为 int 类型。

对 double 类型的 vector 迭代器的萃取也是类似的过程。

而 my_iterator_traits<char*>::value_type 则使用 my_iterator_traits 的偏特化版本，直接返回 char 类型。

由此看来，通过 my_iterator_traits ，我们正确萃取出了迭代器所指元素的类型。

总结一下我们设计并实现一个 traits class 的过程：
1）确认若干我们希望将来可取得的类型相关信息，例如，对于上面的迭代器，我们希望取得迭代器所指元素的类型；
2）为该信息选择一个名称，例如，上面我们起名为 value_type；
3）提供一个 template 和一组特化版本（例如，我们上面的 my_iterator_traits），内容包含我们希望支持的类型相关信息。
*/