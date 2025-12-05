#ifndef LINUX_2025_26_MAIN_PROCESS_H
#define LINUX_2025_26_MAIN_PROCESS_H

#endif //LINUX_2025_26_MAIN_PROCESS_H

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <cstdlib>

int do_command(const char* command) {
    pid_t pid = fork();
    if (pid < 0) return -1;

    if (pid == 0) {
        execl("/bin/sh", "sh", "-c", command, nullptr);
        _exit(127);
    } else {
        int status;
        if (waitpid(pid, &status, 0) < 0) return -1;
        return status;
    }
}

