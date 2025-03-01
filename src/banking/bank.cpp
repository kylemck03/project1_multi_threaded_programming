#include "bank.hpp"
#include <thread>
#include <random>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <chrono>
#include <cstdio>

Bank::Bank(size_t num_accounts, double initial_balance) {
    for (size_t i = 0; i < num_accounts; ++i) {
        accounts_.push_back(std::make_unique<Account>(i, initial_balance));
    }
    
    // Open pipe to logger process
    #ifdef _WIN32
        loggerPipe = _popen("transaction_logger.exe", "w");
    #else
        loggerPipe = popen("./transaction_logger", "w");
    #endif
    
    if (!loggerPipe) {
        std::cerr << "Failed to open pipe to logger. Make sure transaction_logger is built and in the current directory." << std::endl;
    }
}

Bank::~Bank() {
    if (loggerPipe) {
        #ifdef _WIN32
            _pclose(loggerPipe);
        #else
            pclose(loggerPipe);
        #endif
    }
}

void Bank::logTransaction(const std::string& message) {
    if (loggerPipe) {
        fprintf(loggerPipe, "%s\n", message.c_str());
        fflush(loggerPipe);
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
            
            // Try transfer with timeout
            success = accounts_[from_acc]->transferWithTimeout(*accounts_[to_acc], amount, thread_id);
            
            std::stringstream log_message;
            log_message << "Thread " << thread_id 
                       << " transferred $" << std::fixed << std::setprecision(2) << amount 
                       << " from Account " << from_acc 
                       << " to Account " << to_acc 
                       << " - Status: " << (success ? "Success" : "Failed");
            
            logTransaction(log_message.str());
            
            // Small delay between transactions
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }
}

void Bank::printAccountBalances() const {
    for (const auto& account : accounts_) {
        std::cout << "Account " << account->getId() 
                  << ": $" << std::fixed << std::setprecision(2) 
                  << account->getBalance() << std::endl;
    }
}

void Bank::simulateTransactions(size_t num_threads) {
    std::vector<std::thread> threads;
    
    for (size_t i = 0; i < num_threads; ++i) {
        threads.push_back(std::thread(&Bank::performRandomTransactions, this, i));
    }
    
    for (auto& thread : threads) {
        thread.join();
    }
}