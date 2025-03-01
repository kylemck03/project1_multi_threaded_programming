#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
#include <ctime>

int main() {
    std::ofstream logFile("transaction_log.txt", std::ios::app);
    
    if (!logFile.is_open()) {
        std::cerr << "Failed to open log file" << std::endl;
        return 1;
    }

    std::string transaction;
    while (std::getline(std::cin, transaction)) {
        auto now = std::chrono::system_clock::now();
        auto now_time = std::chrono::system_clock::to_time_t(now);
        
        logFile << std::ctime(&now_time) << transaction << std::endl;
        logFile.flush();
        
        // Echo to console as well
        std::cout << "Logged: " << transaction << std::endl;
    }

    logFile.close();
    return 0;
}