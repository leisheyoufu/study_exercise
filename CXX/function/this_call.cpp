#include <iostream>
#include <functional>
using namespace std;
 
class View
{
public:
    void onClick(int x, int y)
    {
        cout << "X : " << x << ", Y : " << y << endl;
    }
};
 
// 定义function类型, 三个参数
function<void(View, int, int)> clickCallback;
 
int main(int argc, const char * argv[])
{
    View button;
 
    // 指向成员函数
    clickCallback = &View::onClick;
 
    // 进行调用
    clickCallback(button, 10, 123);
    return 0;
}