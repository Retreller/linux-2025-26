#include <unistd.h>
#include <fcntl.h>
#include <iostream>

int do_magic() {
    int file = open("new_pts", O_RDONLY);
    if (file == -1) {
        std::cerr << "Failed to open 'new_pts'" << std::endl;
        return 1;
    }

    dup2(fd, STDIN_FILENO);
    close(fd);
    return 0;
}
