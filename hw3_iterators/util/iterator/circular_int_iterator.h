#pragma once
#include <cstddef>

class CircularIterator {
public:
    CircularIterator(int* arr, std::size_t n) : arr(arr), n(n), pos(0) {}

    int& current() const { return arr[pos]; }

    CircularIterator& advance() {
        pos = (pos + 1) % n;
        return *this;
    }

private:
    int* arr;
    std::size_t n;
    std::size_t pos;
};

class CircularIteratorBuilder {
public:
    CircularIteratorBuilder(int* arr, std::size_t n) : arr(arr), n(n), it(arr, n) {}

    int& get() { return it.current(); }
    CircularIteratorBuilder& operator++() { it.advance(); return *this; }

private:
    int* arr;
    std::size_t n;
    CircularIterator it;
};
