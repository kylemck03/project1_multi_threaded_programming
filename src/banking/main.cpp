#include "bank.hpp"
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    size_t num_accounts = 10;
    size_t num_threads = 5;
    if (argc > 2) {
        num_accounts = std::stoul(argv[1]);
        num_threads = std::stoul(argv[2]);
    }
    
    Bank bank(num_accounts, 1000.0); // Initialize accounts with $1000 each
    
    std::cout << "Initial account balances:" << std::endl;
    bank.printAccountBalances();
    
    std::cout << "\nStarting transactions with " << num_threads << " threads..." << std::endl;
    bank.simulateTransactions(num_threads);
    
    std::cout << "\nFinal account balances:" << std::endl;
    bank.printAccountBalances();
    
    return 0;
}
