#include <iostream>
#include <string>

void do_magic();

int main()
{
    system("echo \"String to be input\" > new_pts");
    do_magic();
    std::string s;
    std::getline(std::cin, s);
    std::cout << s << "\n";
}