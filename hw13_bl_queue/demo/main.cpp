#pragma once

#include <queue>
#include <mutex>
#include <condition_variable>

template <typename T>
class blocking_queue {
private:
    std::queue<T> q;
    const size_t max_size;
    mutable std::mutex m;
    std::condition_variable not_empty;
    std::condition_variable not_full;

public:
    explicit blocking_queue(size_t limit) : max_size(limit) {}

    void push(T value) {
        std::unique_lock<std::mutex> lock(m);

        not_full.wait(lock, [this]() {
            return q.size() < max_size;
        });

        q.push(std::move(value));
        not_empty.notify_one();
    }

    T pop() {
        std::unique_lock<std::mutex> lock(m);

        not_empty.wait(lock, [this]() {
            return !q.empty();
        });

        T value = std::move(q.front());
        q.pop();
        not_full.notify_one();
        return value;
    }

    bool try_pop(T& value) {
        std::lock_guard<std::mutex> lock(m);

        if (q.empty()) {
            return false;
        }

        value = std::move(q.front());
        q.pop();
        not_full.notify_one();
        return true;
    }

    size_t size() const {
        std::lock_guard<std::mutex> lock(m);
        return q.size();
    }

    bool empty() const {
        std::lock_guard<std::mutex> lock(m);
        return q.empty();
    }

    bool full() const {
        std::lock_guard<std::mutex> lock(m);
        return q.size() >= max_size;
    }
};
