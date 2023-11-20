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
	bool isCardPrimary;
public:
    // Account
    Account() ;
    virtual ~Account();

    // Get Methods
    int getAccountNum() const;
    void getBankName() const;
    void getOwner() const;
    int getBalance() const;

    // Transaction
    void setBalance(int changedBalance);
    void addTransaction(Transaction* transaction);
    void updateBalance();
    void updateHistory();
    bool getPrimary();
};
