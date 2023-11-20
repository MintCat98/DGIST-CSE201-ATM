#pragma once

#include "Bank.h"
#include "Customer.h"
#include "Transaction.h"
using namespace std;

class Bank;
class Customer;
class Transaction;

class Account {
private:
    int accountNum;
    Bank* primaryBank;
    Customer* ownedBy;
    int balance;
    Transaction* accountHistory; // dynamic allocation
public:
    // Account
    Account() ;
    virtual ~Account();

    //getter
    int getAccountNum() const;
    void getBankName() const;
    void getOwner() const;
    int getBalance() const;

    void addTransaction(Transaction* transaction);
    void updateBalance();
    void updateHistory();

};

    // Account operations
    /*
    void deposit(int amount);
    void withdraw(int amount);

     */


//


