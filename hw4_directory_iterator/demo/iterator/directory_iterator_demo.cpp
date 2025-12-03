#include <filesystem>
#include <iostream>
#include <iterator/directory_iterator.h>

int main()
{
    recursive_directory_iterator your_it(".");
    auto your_end_it = std::filesystem::recursive_directory_iterator();

    namespace fs = std::filesystem;
    fs::recursive_directory_iterator it(".");
    auto end = std::filesystem::recursive_directory_iterator();
    for (;; ++it, ++your_it) {
        if (it == end && your_it == your_end_it) {
            std::cout << "Tests have passed!\n";
            exit(EXIT_SUCCESS);
        }

        if (it == end) {
            std::cout << "Fail: Built in iterator reached to end!\n";
            exit(EXIT_FAILURE);
        }

        if (your_it == your_end_it) {
            std::cout << "Fail: Your iterator reached to end!\n";
            exit(EXIT_FAILURE);
        }

        const bool same_path =
            it->path().string() == your_it->path().string();
        std::cout << std::boolalpha;
        std::cout << it->path() << ": "
            << (same_path ? "ok" : "fail") << "\n";
        if (!same_path) {
            exit(EXIT_FAILURE);
        }
    }
}