#pragma once
#include <mutex>
#include <iostream>
#include <thread>
#include <chrono>

// At global/class scope
static std::mutex cout_mutex;

class Account {
public:
    explicit Account(int id, double initial_balance = 0.0);
    
    bool withdraw(double amount);
    void deposit(double amount);
    double getBalance() const;
    int getId() const;
    
    // Declare the functions here
    bool transferWithTimeout(Account& dest, double amount, int thread_id);
    bool transferWithOrdering(Account& dest, double amount, int thread_id);

private:
    int id_;
    double balance_;
    mutable std::timed_mutex mutex_;
};
