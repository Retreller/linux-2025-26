#include <iostream>
#include <csignal>
#include <unistd.h>

siginfo_t last_info;

void handle_sigusr1(int sig, siginfo_t *info, void *context) {
    if (sig == SIGUSR1) {
        kill(info->si_pid, SIGUSR2);
    }
}

int main() {
    struct sigaction sa;
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = handle_sigusr1;
    sigemptyset(&sa.sa_mask);

    if (sigaction(SIGUSR1, &sa, NULL) == -1) {
        return 1;
    }

    while (true) {
        pause(); 
    }

    return 0;
}
