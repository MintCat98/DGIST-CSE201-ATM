#pragma once

#include "Bank.h"
#include "Customer.h"
#include "Transaction.h"

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
	Account();
	virtual ~Account();
	int getAccountNum();
	void getBankName();
	void getOwner();
	int getbalance();
	void setbalance(int changedbalance);
	void updateBalance();
	void updateHistory();
	bool getPrimary();
};
