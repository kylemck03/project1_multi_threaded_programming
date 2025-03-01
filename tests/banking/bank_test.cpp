#include <gtest/gtest.h>
#include "../../src/banking/bank.hpp"
#include <thread>
#include <chrono>
#include <sstream>

class BankTest : public ::testing::Test {
protected:
    Bank bank{5, 1000.0}; // 5 accounts with $1000 each
    
    // Helper to capture printed output
    double getTotalBalance() {
        std::stringstream buffer;
        std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
        bank.printAccountBalances();
        std::cout.rdbuf(old);
        
        double total = 0.0;
        std::string line;
        while (std::getline(buffer, line)) {
            if (line.find("Balance: $") != std::string::npos) {
                total += std::stod(line.substr(line.find("$") + 1));
            }
        }
        return total;
    }
};

// Test total money conservation
TEST_F(BankTest, MoneyConservation) {
    double initial_total = getTotalBalance();
    
    // Run multiple transactions
    bank.simulateTransactions(3);
    
    // Calculate final total
    double final_total = getTotalBalance();
    
    EXPECT_NEAR(initial_total, final_total, 0.01);
}

// Stress test with many threads
TEST_F(BankTest, StressTest) {
    EXPECT_NO_THROW(bank.simulateTransactions(20));
} 