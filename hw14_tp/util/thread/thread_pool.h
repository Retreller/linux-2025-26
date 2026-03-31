#pragma once

#include <vector>
#include <queue>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>
#include <type_traits>

class thread_pool {
public:
    explicit thread_pool(size_t thread_count = std::thread::hardware_concurrency()) 
        : is_running(true) 
    {
        for (size_t i = 0; i < thread_count; ++i) {
            workers.emplace_back([this] {
                while (true) {
                    std::function<void()> task;
                    {
                        std::unique_lock<std::mutex> lock(queue_lock);
                        pool_condition.wait(lock, [this] {
                            return !is_running || !tasks.empty();
                        });

                        if (!is_running && tasks.empty()) {
                            return;
                        }

                        task = std::move(tasks.front());
                        tasks.pop();
                    }
                    task();
                }
            });
        }
    }

    ~thread_pool() {
        {
            std::lock_guard<std::mutex> lock(queue_lock);
            is_running = false;
        }
        pool_condition.notify_all();
        for (std::thread& worker : workers) {
            if (worker.joinable()) {
                worker.join();
            }
        }
    }

    template<typename F, typename... Args>
    auto enqueue(F&& f, Args&&... args) -> std::future<typename std::result_of<F(Args...)>::type> {
        using return_type = typename std::result_of<F(Args...)>::type;

        auto task = std::make_shared<std::packaged_task<return_type()>>(
            std::bind(std::forward<F>(f), std::forward<Args>(args)...)
        );

        std::future<return_type> result = task->get_future();
        {
            std::lock_guard<std::mutex> lock(queue_lock);
            if (!is_running) {
                throw std::runtime_error("enqueue on stopped pool");
            }
            tasks.emplace([task] { (*task)(); });
        }
        pool_condition.notify_one();

        return result;
    }

    thread_pool(const thread_pool&) = delete;
    thread_pool& operator=(const thread_pool&) = delete;

private:
    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks;
    std::mutex queue_lock;
    std::condition_variable pool_condition;
    bool is_running;
};
