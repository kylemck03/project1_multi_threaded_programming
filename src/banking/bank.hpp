#pragma once
#include "account.hpp"
#include <vector>
#include <memory>
#include <cstdio>

class Bank {
public:
    Bank(size_t num_accounts, double initial_balance);
    ~Bank();
    
    void simulateTransactions(size_t num_threads);
    void printAccountBalances() const;
    void logTransaction(const std::string& message);
    
private:
    void performRandomTransactions(int thread_id);
    
    std::vector<std::unique_ptr<Account>> accounts_;
    FILE* loggerPipe;
};