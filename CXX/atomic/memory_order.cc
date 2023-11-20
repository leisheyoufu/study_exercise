#include<iostream>
#include<atomic>
#include<thread>
#include<vector>

std::atomic<int> counter(0);
std::atomic<bool> ready(false);

void increase_counter() {
    counter.fetch_add(1, std::memory_order_relaxed);
    ready.store(true, std::memory_order_release);
}

void print_counter() {
    while (!ready.load(std::memory_order_acquire)) {
        std::this_thread::yield();
    }
    int c = counter.load(std::memory_order_relaxed);
    std::cout << "Counter: " << c << std::endl;
}

int main() {
    std::vector<std::thread> threads;
    for (int i = 0; i < 10; ++i) {
        threads.push_back(std::thread(increase_counter));
    }
    for (auto& t : threads) {
        t.join();
    }

    std::thread t(print_counter);
    t.join();

    return 0;
}
