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
public:
	// Account
	Account();
	virtual ~Account();
	void getAccountNum();
	void getBankName();
	void getOwner();
	void updateBalance();
	void updateHistory();
};