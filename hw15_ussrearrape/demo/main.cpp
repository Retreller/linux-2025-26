#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <random>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t spy_pid = fork();
    if (spy_pid == 0) {
        execl("./spionen", "spionen", (char *)NULL);
        return 0;
    }

    std::vector<int> pid_list = {1234, 5678, 9101, 1121, 3141};
    pid_list.push_back(spy_pid);

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(pid_list.begin(), pid_list.end(), g);

    std::ofstream ofs("/tmp/reichspost.txt");
    for (int p : pid_list) ofs << p << " ";
    ofs.close();

    pid_t hunter_pid = fork();
    if (hunter_pid == 0) {
        execl("./sturmbannfuhrer", "sturmbannfuhrer", (char *)NULL);
        return 0;
    }

    waitpid(hunter_pid, NULL, 0);
    kill(spy_pid, SIGKILL); 

    return 0;
}
