#pragma once

#include "ATM.h"
#include "Card.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class ATM;
class Card;

class Transaction {
private:
	int transactionID;
	int cardNum;
	int serialNum;
	string transType;
	int transAmount;
public:
	Transaction(ATM* serialNumber,Card* cardNumber, string type );
	virtual ~Transaction();
	// Actions
	void deposit(ATM* serialNumber,Card* cardNumber);
	void withdrawal(ATM* serialNumber,Card* cardNumber);
	void cashtransfer(ATM* serialNumber, Account* accountNumberTo);
	void transfer(ATM* serialNumber, Account* accountNumberFrom, Account* accountNumberTo);
	void addcash(ATM* serialNumber, Card* cardNumber);
	void addcheck(ATM* serialNumber, Card* cardNumber);
};