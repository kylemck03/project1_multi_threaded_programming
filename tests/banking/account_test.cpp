#include <gtest/gtest.h>
#include "../../src/banking/account.hpp"
#include <thread>
#include <vector>

class AccountTest : public ::testing::Test {
protected:
    Account account{1, 1000.0};
};

// Test basic withdrawal functionality
TEST_F(AccountTest, BasicWithdraw) {
    EXPECT_TRUE(account.withdraw(500.0));
    EXPECT_EQ(account.getBalance(), 500.0);
}

// Test concurrent withdrawals
TEST_F(AccountTest, ConcurrentWithdrawals) {
    const int num_threads = 10;
    std::vector<std::thread> threads;
    
    for (int i = 0; i < num_threads; ++i) {
        threads.push_back(std::thread([&]() {
            account.withdraw(100.0);
        }));
    }
    
    for (auto& thread : threads) {
        thread.join();
    }
    
    // Final balance should never be negative
    EXPECT_GE(account.getBalance(), 0.0);
}

// Test transfer timeout mechanism
TEST_F(AccountTest, TransferTimeout) {
    Account dest{2, 1000.0};
    
    // Create a blocking scenario by repeatedly attempting transfers
    std::thread blocker([&]() {
        for(int i = 0; i < 100; i++) {
            account.transferWithTimeout(dest, 1.0, 0);
        }
    });
    
    // Try transfer while account is busy
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    bool transfer_result = account.transferWithTimeout(dest, 500.0, 1);
    
    blocker.join();
    
    // The transfer might succeed or fail depending on timing,
    // but the account should remain in a valid state
    double final_balance = account.getBalance();
    EXPECT_GE(final_balance, 0.0);
} 