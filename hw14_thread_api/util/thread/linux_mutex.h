#pragma once
#include <pthread.h>

class linux_mutex {
    pthread_mutex_t mtx;

public:
    linux_mutex();
    ~linux_mutex();

    void lock();
    void unlock();

    linux_mutex(const linux_mutex&) = delete;
    linux_mutex& operator=(const linux_mutex&) = delete;
};
