#include "account.hpp"
#include <iostream>
#include <thread>

Account::Account(int id, double initial_balance)
    : id_(id), balance_(initial_balance) {}

bool Account::withdraw(double amount) {
    std::lock_guard<std::timed_mutex> lock(mutex_);
    if (balance_ >= amount) {
        // Simulate some processing time
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        balance_ -= amount;
        return true;
    }
    return false;
}

void Account::deposit(double amount) {
    std::lock_guard<std::timed_mutex> lock(mutex_);
    // Simulate some processing time
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    balance_ += amount;
}

double Account::getBalance() const {
    std::lock_guard<std::timed_mutex> lock(mutex_);
    return balance_;
}

int Account::getId() const {
    return id_;
}

bool Account::transferWithTimeout(Account& dest, double amount, int thread_id) {
    using namespace std::chrono;
    auto timeout = milliseconds(100);

    {
        std::lock_guard<std::mutex> lock(cout_mutex);
        std::cout << "Thread " << thread_id 
                  << " attempting transfer with timeout: $" << amount 
                  << " from Account " << id_ << " to Account " 
                  << dest.id_ << std::endl;
    }

    // Try to lock source account
    if (!mutex_.try_lock_for(timeout)) {
        return false;
    }
    std::lock_guard<std::timed_mutex> lock_source(mutex_, std::adopt_lock);

    // Try to lock destination account
    if (!dest.mutex_.try_lock_for(timeout)) {
        return false;
    }
    std::lock_guard<std::timed_mutex> lock_dest(dest.mutex_, std::adopt_lock);

    if (balance_ >= amount) {
        balance_ -= amount;
        dest.balance_ += amount;
        return true;
    }
    return false;
}

bool Account::transferWithOrdering(Account& dest, double amount, int thread_id) {
    {
        std::lock_guard<std::mutex> lock(cout_mutex);
        std::cout << "Thread " << thread_id 
                  << " attempting ordered transfer: $" << amount 
                  << " from Account " << id_ << " to Account " 
                  << dest.id_ << std::endl;
    }

    // Always lock accounts in order of their IDs to prevent deadlock
    Account& first = (this->id_ < dest.id_) ? *this : dest;
    Account& second = (this->id_ < dest.id_) ? dest : *this;

    std::lock_guard<std::timed_mutex> lock_first(first.mutex_);
    std::lock_guard<std::timed_mutex> lock_second(second.mutex_);

    // If this is the source account
    if (this == &first) {
        if (balance_ >= amount) {
            balance_ -= amount;
            dest.balance_ += amount;
            return true;
        }
    } else {
        // If this is the destination account
        if (dest.balance_ >= amount) {
            dest.balance_ -= amount;
            balance_ += amount;
            return true;
        }
    }
    return false;
}
