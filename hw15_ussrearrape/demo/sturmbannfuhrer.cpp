#include <iostream>
#include <fstream>
#include <vector>
#include <csignal>
#include <unistd.h>

volatile sig_atomic_t protocol_confirmed = 0;

void handle_sigusr2(int sig) {
    if (sig == SIGUSR2) {
        protocol_confirmed = 1;
    }
}

int main() {
    signal(SIGUSR2, handle_sigusr2);
    
    std::ifstream file("/tmp/reichspost.txt");
    std::vector<pid_t> pids;
    pid_t temp;

    while (file >> temp) {
        pids.push_back(temp);
    }
    file.close();

    for (pid_t target : pids) {
        protocol_confirmed = 0;
        
        if (kill(target, SIGUSR1) == -1) continue;

        if (protocol_confirmed) {
            kill(target, SIGILL);
            return 0;
        }
    }

    return 1;
}
