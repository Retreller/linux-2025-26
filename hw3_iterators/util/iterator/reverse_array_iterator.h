#pragma once
#include <cstddef>

class ReverseIterator {
public:
    ReverseIterator(int* ptr) : cur(ptr) {}
    int& operator*() const { return *cur; }
    ReverseIterator& operator++() { --cur; return *this; }
    bool operator!=(const ReverseIterator& other) const { return cur != other.cur; }

private:
    int* cur;
};

class ReverseIteratorBuilder {
public:
    ReverseIteratorBuilder(int* arr, std::size_t n) : arr(arr), n(n) {}

    ReverseIterator begin() const { return ReverseIterator(arr + n - 1); }
    ReverseIterator end() const { return ReverseIterator(arr - 1); }

private:
    int* arr;
    std::size_t n;
};
