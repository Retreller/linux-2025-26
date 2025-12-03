//
// Created by valeri on 10/31/25.
//#include <unistd.h>
#include <fcntl.h>
#include <iostream>

int main() {
    const char* path = "exclusive_file.log";

    int first = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (first == -1) {
        std::cerr << "Cannot open file" << std::endl;
        return 1;
    }

    int second = dup(first);
    if (second == -1) {
        std::cerr << "Cannot duplicate descriptor" << std::endl;
        close(first);
        return 1;
    }

    const char* msg1 = "First line.\n";
    const char* msg2 = "Second line.\n";

    ssize_t w1 = write(first, msg1, 12);
    ssize_t w2 = write(second, msg2, 13);

    if (w1 == -1 || w2 == -1)
        std::cerr << "Write failed" << std::endl;

    close(first);
    close(second);
    return 0;
}
