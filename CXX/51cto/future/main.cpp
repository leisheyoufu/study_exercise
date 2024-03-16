#include <future>
#include<iostream>
#include <thread>
using namespace std;

int threadFunction() {
    std::cout << "threadFunction thread id: " << std::this_thread::get_id() << std::endl;

    std::chrono::milliseconds duration(5000);
    std::this_thread::sleep_for(duration);
    return 5;
}
void threadFunctionTest() {
    std::cout << "main thread id: " << std::this_thread::get_id() << std::endl;
    std::shared_future<int> result = std::async(threadFunction); // async 用来创建一个异步任务;
//    std::shared_future<int> result = std::async(std::launch::deferred, threadFunction); // deferred为延迟调用, 且不创建新线程;延迟到result调用.get(), 或 .wait()时才调用threadFunction();
//    std::shared_future<int> result = std::async(std::launch::async, threadFunction); // 从表象来看, std::launch::async参数写不写并不影响结果;
//    std::shared_future<int> result = std::async(std::launch::async|std::launch::deferred, threadFunction); // 系统自动判断, 立刻|延迟 创建新线程;
    std::cout << "end...: " << result.get() << std::endl;
}

int main() {
    threadFunctionTest();
    
    return 0;
}