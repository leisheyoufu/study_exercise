#include <iostream>
#include <map>
#include <utility>
#include <list>
#include <future>

#include <thread>
using namespace std;

void threadIdTest() { // 获取当前线程id
    std::thread::id threadId = std::this_thread::get_id();
    std::cout << "threadId: " << threadId << std::endl;
}


int threadFunction(int var) {
    std::chrono::milliseconds duration(5000); // 5s.
    std::cout << "var: " << var << std::endl;
    std::this_thread::sleep_for(duration);
    return 50;
}
void threadFunctionTest() {
    std::packaged_task<int(int)> task(threadFunction); // 通过 packaged_task 来包装函数 threadFunction;
    std::thread currentThread(std::ref(task), 2); // 执行 线程任务 task, 第二个参数为线程入口函数的参数; (另外ref代表引用task对象)

    currentThread.join(); // 卡住线程, 直到任务执行结束
    std::cout << "task end..." << std::endl;
}


//void threadFunctionFuture(std::future<int> &tmpf)
void threadFunctionFuture(std::shared_future<int>& tempFuture) {
    std::cout << "threadFunctionFuture begin, threadId: " << std::this_thread::get_id() << std::endl;

    auto result = tempFuture.get(); // 只能get一次, 因为get本身是移动语义
    std::cout << "threadFunctionFuture end, result: " << result << std::endl;
}
void threadFunctionFutureTest() {
    std::packaged_task<int(int)> threadTask(threadFunction);

   std::future<int> result = threadTask.get_future(); // 应该是相当于把, 把任务上锁同时返回？
   if (result.valid()) {
       std::cout << "1 yes" << std::endl; // bingo
   } else {
       std::cout << "1 no" << std::endl;
   }

    std::shared_future<int> result_s = std::move(result); // 这句话执行完, result为空;

    if (result.valid()) {
        std::cout << "2 yes" << std::endl;
    } else {
        std::cout << "2 no" << std::endl; // bingo
    }

   result_s = result.share(); // 这句话执行完, result依旧为空;
   if (result.valid()) {
       std::cout << "3 yes" << std::endl;
   } else {
       std::cout << "3 no" << std::endl; // bingo
   }

    // result_s = threadTask.get_future();
    // std::thread currentThread(threadFunctionFuture, std::ref(result_s));

    // currentThread.join(); // 从现象来看, 线程会一直守护在这.
}

int main() {
//    threadIdTest();
//    threadFunctionTest();

    threadFunctionFutureTest();

    return 0;
}