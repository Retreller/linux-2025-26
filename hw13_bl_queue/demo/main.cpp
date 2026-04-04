#include "ArmenianQueue.h"
#include <iostream>
#include <thread>
#include <vector>

int main() {
    const int iterations = 6;
    rau::blocking_queue<int> q(iterations);

    std::thread producer([&] {
        for (int i = 1; i <= iterations; ++i) {
            q.push(i);
            std::cout << "Produced: " << i << std::endl;
        }
    });

    std::thread consumer([&] {
        for (int i = 0; i < iterations; ++i) {
            const auto val = q.pop();
            std::cout << "Consumed: " << val << std::endl;
        }
    });

    producer.join();
    consumer.join();

    rau::blocking_queue<int> q2(5);
    q2.push(100);

    if (auto val = q2.try_pop()) {
        std::cout << "try_pop result: " << *val << std::endl;
    }

    if (auto val = q2.try_pop(); !val) {
        std::cout << "try_pop result: empty" << std::endl;
    }

    return 0;
}
