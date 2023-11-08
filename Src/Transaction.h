#pragma once

#include "ATM.h"
#include "Card.h"

class ATM;
class Card;

class Transaction {
private:
	const int transactionID;
	Card* cardNum;
	string transType;
	int transAmount;
public:
	// Transaction
	Transaction();
	virtual ~Transaction();
	void updateInfo();
	void getInfo();
};