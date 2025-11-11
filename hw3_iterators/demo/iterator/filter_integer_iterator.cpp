#include <iostream>
#include <vector>
#include <filter_integer_iterator.h>

bool is_even(int num) {
    return num % 2 == 0;
}

int main() {
    std::vector numbers = {1, 2, 3, 4, 5, 6};
    FilterIteratorBuilder even_iter(numbers.data(), numbers.size(), is_even);

    for (auto it = even_iter.begin(); it != even_iter.end(); ++it) {
        std::cout << *it << " ";
    }

    // 2 4 6
    std::cout << std::endl;
    return 0;
}
