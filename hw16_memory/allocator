#include <iostream>
#include <vector>

template <typename T>
class allocator {
public:
    using value_type = T;

    allocator() noexcept {
    }

    template <typename U>
    allocator(const allocator<U>&) noexcept {
    }

    T* allocate(std::size_t n) {
        return static_cast<T*>(::operator new(n * sizeof(T)));
    }

    void deallocate(T* p, std::size_t) {
        ::operator delete(p);
    }

    template <typename U>
    bool operator==(const allocator<U>&) const noexcept {
        return true;
    }

    template <typename U>
    bool operator!=(const allocator<U>&) const noexcept {
        return false;
    }
};

int main() {
    std::vector<int, allocator<int>> nums;

    nums.push_back(10);
    nums.push_back(20);
    nums.push_back(30);

    std::cout << "Vector elements: ";

    for (int i = 0; i < nums.size(); ++i) {
        std::cout << nums[i] << " ";
    }

    std::cout << "\n";

    auto my_alloc = nums.get_allocator();
    allocator<int> another_alloc;

    std::cout << std::boolalpha;
    std::cout << "my_alloc == another_alloc: "
              << (my_alloc == another_alloc) << "\n";

    std::cout << "my_alloc != another_alloc: "
              << (my_alloc != another_alloc) << "\n";

    return 0;
}
