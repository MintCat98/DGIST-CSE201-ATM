#pragma once

#include <map>
#include "Bank.h"
#include "Transaction.h"

class Bank;
class Transaction;

class ATM {
private:
    int aID;
	Bank* ownedBy;
	int serialNum;
	vector<Bank*> bankList;
	bool singleBank;
	bool biLanguage;
	bool isKorean;
	map<int, int> cashAmount; // sort: amount
	vector<Transaction*> transHistory;
    static int atmIDs;
	static int transNums;
public:
	// ATM
	ATM(Bank* primary, int sNum, bool single, bool lang, map<int,int> cash);
	~ATM();
	int getSerialNum();
	int getCashTotal();
    bool isBilingual();
	void selectLanguage(); // KR(true), EN(false)
    void setEN();
	
	// User Validation
	bool isCardAvailable();
	bool isAdmin();
	bool isCardPW();

	// Transaction
	void transaction();
	int decideFees();
	bool isSufficient();
	void updateCashAmmount(bool isDeposit);

	// Admin
	void printATMStatus();
	void printHistory();
};