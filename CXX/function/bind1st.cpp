#include <iostream>
#include <functional>
#include <algorithm>
#include <vector>
using namespace std;
 
int main()
{
    vector<int> coll;
    for (int i = 1; i <= 10; ++i)
    {
        coll.push_back(i);
    }
 
    // 查找元素值大于10的元素的个数
    // 也就是使得10 < elem成立的元素个数 
    int res = count_if(coll.begin(), coll.end(), bind1st(less<int>(), 10));
    cout << res << endl;
 
    // 查找元素值小于10的元素的个数
    // 也就是使得elem < 10成立的元素个数 
    res = count_if(coll.begin(), coll.end(), bind2nd(less<int>(), 10));
    cout << res << endl;
 
    return 0;
}
/*
通过上面的代码明白了std::bind1st和std::bind2nd了么？还没有明白？好吧，我接着往细了讲。

对于上面的代码，less<int>()其实是一个仿函数，如果没有std::bind1st和std::bind2nd，那么我们可以这样使用less<int>()，代码如下：

less<int> functor = less<int>();
bool bRet = functor(10, 20); // 返回true
1
2
看到了么？less<int>()这个仿函数对象是需要两个参数的，比如10<20进行比较，那么10叫做left参数，20叫做right参数。

当使用std::bind1st的时候，就表示绑定了left参数，也就是left参数不变了，而right参数就是对应容器中的element；
当使用std::bind2nd的时候，就表示绑定了right参数，也就是right参数不变了，而left参数就是对应容器中的element。
*/