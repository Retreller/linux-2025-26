#pragma once

#include <queue>
#include <mutex>
#include <condition_variable>
#include <optional>

namespace rau {

    template <typename T>
    class blocking_queue {
    public:
        explicit blocking_queue(const std::size_t capacity) : max_size_{capacity} { }

        template <typename... Args>
        void push(Args&&... args) {
            std::unique_lock lock(mtx_);

            cv_not_full_.wait(lock, [this] {
                return data_.size() < max_size_;
            });

            data_.emplace(std::forward<Args>(args)...);
            cv_not_empty_.notify_one();
        }

        T pop() {
            std::unique_lock lock(mtx_);
            cv_not_empty_.wait(lock, [this] {
                return !data_.empty();
            });

            T res = std::move(data_.front());
            data_.pop();

            cv_not_full_.notify_one();
            return res;
        }

        std::optional<T> try_pop() {
            std::lock_guard lock(mtx_);
            if (data_.empty()) {
                return std::nullopt;
            }

            T res = std::move(data_.front());
            data_.pop();

            cv_not_full_.notify_one();
            return res;
        }

        std::size_t size() const {
            std::lock_guard lock(mtx_);
            return data_.size();
        }

        bool empty() const {
            std::lock_guard lock(mtx_);
            return data_.empty();
        }

    private:
        const std::size_t max_size_;
        std::queue<T> data_;

        mutable std::mutex mtx_;
        std::condition_variable cv_not_empty_;
        std::condition_variable cv_not_full_;
    };

}
