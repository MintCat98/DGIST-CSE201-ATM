#pragma once
#include <string>
#include <iostream>
#include "Bank.h"
#include "Customer.h"
#include "Transaction.h"
#include "ATM.h"

using namespace std;
class Bank;
class Customer;
class Transaction;
class ATM;

class Account {
private:
    int accountNum;
    Bank* primaryBank;
    Customer* ownedBy;
    int balance;
    Transaction* accountHistory; // dynamic allocation
    bool isCardPrimary;


    string bankName_;
    string userName_;
    int accountNum_;
    int balance_;



public:
    // Account
    Account(string bankName, string userName, int accountNum, int funds);
    virtual ~Account();

    // Get Methods
    int getAccountNum() const;
    string getBankName() const;
    string getOwner() const;
    int getBalance() const;

    // Transaction
    void setbalance(int balance);
    int getbalance() const;


    bool getPrimary(ATM* atm);

};


class Card : public Account {
private:
    string password_;
    string getPasswordFromUser() const {
        string inputPassword;
        cout << "Enter password: "; cin >> inputPassword;
        return inputPassword;
    }
public:
    // Card
    Card(string bankName, string userName, int accountNum, int funds, string password) : Account(bankName, userName, accountNum, funds), password_(password) {}

    bool verifyPassword(string inputPassword);

    bool accessAccount();


    int getCardNum();
    virtual ~Card();
};
