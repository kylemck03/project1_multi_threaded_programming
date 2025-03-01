#include <iostream>
#include <string>
#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif

int main() {
    std::string line;
    while (std::getline(std::cin, line)) {
        std::cout << "Producer: " << line << std::endl;
    }
    return 0;
}
