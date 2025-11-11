#pragma once
#include <cstddef>
#include <functional>

class FilterIterator {
public:
    FilterIterator(int* start, int* finish, std::function<bool(int)> pred)
        : cur(start), end(finish), pred(pred) { skip_invalid(); }

    int& operator*() const { return *cur; }
    FilterIterator& operator++() { ++cur; skip_invalid(); return *this; }
    bool operator!=(const FilterIterator& other) const { return cur != other.cur; }

private:
    int* cur;
    int* end;
    std::function<bool(int)> pred;

    void skip_invalid() {
        while (cur != end && !pred(*cur)) ++cur;
    }
};

class FilterIteratorBuilder {
public:
    FilterIteratorBuilder(int* data, std::size_t size, std::function<bool(int)> pred)
        : data(data), size(size), pred(pred) {}

    FilterIterator begin() const { return FilterIterator(data, data + size, pred); }
    FilterIterator end() const { return FilterIterator(data + size, data + size, pred); }

private:
    int* data;
    std::size_t size;
    std::function<bool(int)> pred;
};
