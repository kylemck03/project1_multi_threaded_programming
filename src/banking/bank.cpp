#include "bank.hpp"
#include <thread>
#include <random>
#include <iostream>

Bank::Bank(size_t num_accounts, double initial_balance) {
    for (size_t i = 0; i < num_accounts; ++i) {
        accounts_.push_back(std::make_unique<Account>(i, initial_balance));
    }
}

void Bank::simulateTransactions(size_t num_threads) {
    std::vector<std::thread> threads;
    
    for (size_t i = 0; i < num_threads; ++i) {
        threads.emplace_back(&Bank::performRandomTransactions, this, i);
    }
    
    for (auto& thread : threads) {
        thread.join();
    }
}

void Bank::performRandomTransactions(int thread_id) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> account_dist(0, accounts_.size() - 1);
    std::uniform_real_distribution<> amount_dist(1.0, 100.0);
    
    for (int i = 0; i < 10; ++i) {
        int from_acc = account_dist(gen);
        int to_acc = account_dist(gen);
        
        if (from_acc != to_acc) {
            double amount = amount_dist(gen);
            bool success = false;

            // Try transfer with timeout first
            success = accounts_[from_acc]->transferWithTimeout(*accounts_[to_acc], amount, thread_id);
            
            if (!success) {
                // If timeout-based transfer fails, try ordered transfer
                success = accounts_[from_acc]->transferWithOrdering(*accounts_[to_acc], amount, thread_id);
                
                std::lock_guard<std::mutex> lock(cout_mutex);
                std::cout << "Thread " << thread_id 
                          << " failed timeout transfer, using ordered transfer for $" 
                          << amount << " from account " << from_acc 
                          << " to account " << to_acc 
                          << " - Status: " << (success ? "Success" : "Failed") 
                          << std::endl;
            }
        }
    }
}

void Bank::printAccountBalances() const {
    for (const auto& account : accounts_) {
        std::cout << "Account " << account->getId() 
                  << ": $" << account->getBalance() << std::endl;
    }
}
