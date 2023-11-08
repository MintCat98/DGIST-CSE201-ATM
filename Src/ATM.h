#pragma once

#include "Bank.h";
#include "Transaction.h";

class Bank;
class Transaction;

class ATM {
private:
	int serialNum;
	Bank* ownedBy;
	Bank* bankList[10];
	bool singleBank;
	bool biLanguage;
	int cashAmount;
	Transaction* transHistory; // dynamic allocation
public:
	// ATM
	ATM();
	~ATM();
	void sessionLoop(); // 세션에서의 거래 내용 따로 리스트로 관리하다 종료 시 출력
	void getSerialNum();
	void selectLanguage();
	int getCashAmount();
	// User Validation
	bool isCardAvailable();
	bool isAdmin();
	bool isCardPW();
	// Transaction
	void transaction();
	int decideFees();
	bool isSufficient();
	void updateCashAmmount();
	// Admin
	void printATMStatus();
	void printHistory();
};