#include "thread_pool.h"
#include <iostream>

int calculate(int x, int y) {
    return x * y;
}

int main() {
    thread_pool pool(4);

    auto job1 = pool.enqueue(calculate, 10, 5);
    auto job2 = pool.enqueue([](int n) { return n * n; }, 8);

    auto job3 = pool.enqueue([] {
        std::cout << "Background task running" << std::endl;
    });

    std::cout << "Result 1: " << job1.get() << "\n";
    std::cout << "Result 2: " << job2.get() << "\n";
    job3.get();

    return 0;
}
