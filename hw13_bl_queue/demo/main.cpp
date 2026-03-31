#include <iostream>
#include <thread>
#include <chrono>
#include "ArmenianQueue.h"

blocking_queue<int> bq(5);

void producer() {
    for (int i = 1; i <= 10; ++i) {
        bq.push(i);
        std::cout << "Produced: " << i << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}

void consumer() {
    for (int i = 1; i <= 10; ++i) {
        int x = bq.pop();
        std::cout << "Consumed: " << x << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

int main() {
    std::thread t1(producer);
    std::thread t2(consumer);

    if (t1.joinable()) t1.join();
    if (t2.joinable()) t2.join();

    return 0;
}
