#pragma once
#include <string>
#include <iostream>
#include "Bank.h"
#include "Transaction.h"
#include "ATM.h"

using namespace std;
class Bank;
class Transaction;
class ATM;

class Account {
private:
    long long accountNum;
    Bank* primaryBank;
    int balance;
    Transaction* accountHistory; // dynamic allocation
    bool isCardPrimary;


    string bankName_;
    string userName_;
    long long accountNum_;
    int balance_;



public:
    // Account
    Account(string bankName, string userName, long long accountNum, int funds);
    virtual ~Account();

    // Get Methods
    long long getAccountNum() const;
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
    Card(string bankName, string userName, long long accountNum, int funds, string password) : Account(bankName, userName, accountNum, funds), password_(password) {}

    bool verifyPassword(string inputPassword);

    bool accessAccount();


    long long getCardNum();
    virtual ~Card();
};