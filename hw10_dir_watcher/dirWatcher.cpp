#include <iostream>
#include <unistd.h>
#include <sys/inotify.h>

int main(int argCount, char* argList[]) {
    if (argCount !=2) {
        std::cout << "Usage: ./watcher <path>";
        return 1;
    }

    int watchFd = inotify_init();
    if (watchFd< 0) {
        std::cout <<"Failed to initialize inotify";
        return 1;
    }

    int watchDescriptor = inotify_add_watch(watchFd, argList[1], IN_ALL_EVENTS);
    if (watchDescriptor < 0) {
        std::cout << "Cannot watch" << argList[1] << " –something is wrong!!!!";
        return 1;
    }

    std::cout << "Mesheek is watching " << argList[1] << std::endl;

    char eventBuffer[4096];

    while (true) {
        ssize_t bytesRead = read(watchFd, eventBuffer, sizeof(eventBuffer));
        if (bytesRead < 0) break;

        int currentPos = 0;
        while (currentPos < bytesRead) {
            const inotify_event* currentEvent =
                reinterpret_cast<const inotify_event*>(&eventBuffer[currentPos]);

            std::cout << "ALERT! Someone is messing around!";

            if (currentEvent->len > 0) {
                std::cout << "Target file/directory: " << currentEvent->name << std::endl;
            }

            if (currentEvent->mask & IN_CREATE)  std::cout << "Something CREATED";
            if (currentEvent->mask & IN_DELETE)  std::cout << "Something DELETED";
            if (currentEvent->mask & IN_MODIFY)  std::cout << "Something MODIFIED";
            if (currentEvent->mask & IN_OPEN)    std::cout << " File OPENED";
            if (currentEvent->mask & IN_ACCESS)  std::cout << " File ACCESSED";

            currentPos += sizeof(inotify_event) + currentEvent->len;
        }
    }

    close(watchFd);
    return 0;
}
