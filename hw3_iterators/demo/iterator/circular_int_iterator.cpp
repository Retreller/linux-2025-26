#include <iostream>
#include <vector>
#include <circular_int_iterator.h>

int main() {
    std::vector numbers = {10, 20, 30};
    CircularIteratorBuilder circular(numbers.data(), numbers.size());

    for (int i = 0; i < 7; ++i) {
        std::cout << circular.get() << " ";
        ++circular;
    }

    // 10 20 30 10 20 30 10
    std::cout << std::endl;
    return 0;
}
