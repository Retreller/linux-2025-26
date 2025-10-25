#include <iostream>
#include <reverse_array_iterator.h>

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    ReverseIteratorBuilder rit(arr, sizeof(arr) / sizeof(arr[0]));

    for (auto it = rit.begin(); it != rit.end(); ++it) {
        std::cout << *it << " ";
    }

    // 5 4 3 2 1
    std::cout << std::endl;
    return 0;
}
