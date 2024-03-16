//
// Created by win10 on 2021/11/16.
//

#include <thread>
#include <iostream>
using namespace std;

int fibo_1(int index) { // 这个算法性能上有问题, index为64时不出结果
    if (index <= 1)
        return index;
    return fibo_1(index - 2) + fibo_1(index - 1);
}

int fibo_2(int index) {
    if (index <= 1)
        return index;

    int first(0);
    int second(1);

    for (size_t i(0); i < index - 1; i++) {
        int sumValue = first + second;
        first = second;
        second = sumValue;
    }

    return second;
}

template<class T>
double checkTime(T&& checkFunction, int index) {
    using namespace std::chrono;

    auto start = system_clock::now();
    checkFunction(index);
    duration<double> diff = system_clock::now() - start;

    std::cout << "time diff:" << diff.count() << std::endl;
    return diff.count();
}

int main() {

    int valueIndex = 20;

    double fibo_1_time = checkTime(fibo_1, valueIndex);
    double fibo_2_time = checkTime(fibo_2, valueIndex);

    if (fibo_1_time > fibo_2_time) {
        std::cout << "fibo_1_time big" << std::endl;
    } else if (fibo_1_time < fibo_2_time) {
        std::cout << "fibo_2_time big" << std::endl;
    } else {
        std::cout << "onaji" << std::endl;
    }

    return 0;
}