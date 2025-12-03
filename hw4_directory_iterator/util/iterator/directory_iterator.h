#pragma once
#include <dirent.h>
#include <sys/stat.h>
#include <string>
#include <stack>

class directory_iterator {
public:
    directory_iterator() = default;
    explicit directory_iterator(const std::string& path) {
        open_dir(path);
        advance();
    }

    ~directory_iterator() {
        if (dir)
            closedir(dir);
    }

    const std::string& operator*() const { return current; }

    directory_iterator& operator++() {
        advance();
        return *this;
    }

    bool operator==(const directory_iterator& other) const {
        return current.empty() && other.current.empty();
    }

    bool operator!=(const directory_iterator& other) const {
        return !(*this == other);
    }

protected:
    void open_dir(const std::string& path) {
        dir = opendir(path.c_str());
        base_path = path;
    }

    void advance() {
        if (!dir) {
            current.clear();
            return;
        }

        struct dirent* entry;
        while ((entry = readdir(dir)) != nullptr) {
            std::string name = entry->d_name;
            if (name == "." || name == "..") continue;
            current = base_path + "/" + name;
            return;
        }

        current.clear();
        closedir(dir);
        dir = nullptr;
    }

    DIR* dir = nullptr;
    std::string base_path;
    std::string current;
};

class recursive_directory_iterator {
public:
    recursive_directory_iterator() = default;
    explicit recursive_directory_iterator(const std::string& path) {
        push_dir(path);
        advance();
    }

    const std::string& operator*() const { return current; }

    recursive_directory_iterator& operator++() {
        advance();
        return *this;
    }

    bool operator==(const recursive_directory_iterator& other) const {
        return current.empty() && other.current.empty();
    }

    bool operator!=(const recursive_directory_iterator& other) const {
        return !(*this == other);
    }

private:
    struct DirState {
        std::string path;
        DIR* dir;
    };

    std::stack<DirState> stack;
    std::string current;

    void push_dir(const std::string& path) {
        DIR* d = opendir(path.c_str());
        if (d)
            stack.push({path, d});
    }

    void advance() {
        current.clear();
        while (!stack.empty()) {
            auto& top = stack.top();
            struct dirent* entry = readdir(top.dir);
            if (!entry) {
                closedir(top.dir);
                stack.pop();
                continue;
            }

            std::string name = entry->d_name;
            if (name == "." || name == "..") continue;

            std::string full_path = top.path + "/" + name;
            struct stat st{};
            if (stat(full_path.c_str(), &st) == 0 && S_ISDIR(st.st_mode)) {
                push_dir(full_path);
            }

            current = full_path;
            return;
        }
    }
};
