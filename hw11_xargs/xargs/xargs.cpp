#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include "../util/io/process.h"

int main(int argc, char* argv[]) {
    if (argc<2) {
        std::cerr <<"Usage "<<argv[0]<<"command";
        return 1;
    }
    std::string base_command = argv[1];
    std::string line;
    while (std::getline(std::cin, line)) {
        std::istringstream iss(line);
        std::string arg;
        std::string full_command =base_command;

        while (iss>>arg){
            full_command+=" " +arg;
        }
        int status=do_command(full_command.c_str());
        if (status != 0) {
            std::cerr<<"Command faile with status"<<status;
        }
    }
    return 0;
}
