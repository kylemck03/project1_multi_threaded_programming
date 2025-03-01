#include <iostream>
#include <vector>
#include <numeric>
#include <cmath>

int main() {
    std::vector<int> numbers;
    int number;

    // Read numbers from stdin until EOF
    while (std::cin >> number) {
        numbers.push_back(number);
        
        // Calculate running statistics
        double sum = std::accumulate(numbers.begin(), numbers.end(), 0.0);
        double mean = sum / numbers.size();
        
        // Calculate standard deviation
        double sq_sum = std::inner_product(numbers.begin(), numbers.end(), 
                                         numbers.begin(), 0.0);
        double stdev = std::sqrt(sq_sum / numbers.size() - mean * mean);

        // Output statistics
        std::cout << "Received number: " << number << std::endl;
        std::cout << "Current statistics:" << std::endl;
        std::cout << "Count: " << numbers.size() << std::endl;
        std::cout << "Mean: " << mean << std::endl;
        std::cout << "Standard Deviation: " << stdev << std::endl;
        std::cout << "------------------------" << std::endl;
    }

    return 0;
}