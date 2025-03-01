#include <iostream>
#include <random>
#include <chrono>
#include <thread>

int main() {
    // Set up random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 100);

    // Generate and send 10 random numbers
    for (int i = 0; i < 10; ++i) {
        int number = dis(gen);
        std::cout << number << std::endl;
        // Small delay to make the process visible
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    return 0;
}