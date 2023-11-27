#pragma once

#include <map>
#include "Bank.h"
#include "Transaction.h"

class Bank;
class Transaction;

class ATM {
private:
	int serialNum;
	Bank* ownedBy;
	vector<Bank*> bankList;
	bool singleBank;
	bool biLanguage;
	bool isKorean;
	map<int, int> cashAmount; // sort: amount
	vector<Transaction*> transHistory;
	static int transNum;
public:
	// ATM
	ATM(Bank* primary, int sNum, bool single, bool lang, map<int,int> cash);
	~ATM();
	void sessionLoop(); // 세션에서의 거래 내용 따로 리스트로 관리하다 종료 시 출력
	int getSerialNum();
	int getCashTotal();
	void selectLanguage(); // KR(true), EN(false)
	
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