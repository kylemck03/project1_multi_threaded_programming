#pragma once
#include "account.hpp"
#include <vector>
#include <memory>

class Bank {
public:
    Bank(size_t num_accounts, double initial_balance);
    
    void simulateTransactions(size_t num_threads);
    void printAccountBalances() const;
    
private:
    void performRandomTransactions(int thread_id);
    
    std::vector<std::unique_ptr<Account>> accounts_;
};
