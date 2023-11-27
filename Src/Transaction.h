#pragma once

#include "ATM.h"
#include "Card.h"
#include "Feeinitialize.h"
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
	Transaction(ATM* serialNumber,Card* cardNumber, string type, Fee* fee);
	Transaction(ATM* serialNumber, Account* accountNumberTo, string type, Fee* fee);
	Transaction(ATM* serialNumber, Account* accountNumberFrom, Account* accountNumberTo, string type, Fee* fee);
	virtual ~Transaction();
	// Actions
	void deposit(ATM* serialNumber,Card* cardNumber, Fee* fee);
	void withdrawal(ATM* serialNumber,Card* cardNumber, Fee* fee);
	void addcash(ATM* serialNumber, Card* cardNumber, Fee* fee);
	void addcheck(ATM* serialNumber, Card* cardNumber, Fee* fee);
};

