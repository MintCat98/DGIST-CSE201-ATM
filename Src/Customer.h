#pragma once

#include "Bank.h"
#include "Card.h"

class Bank;
class Card;

class Customer {
private:
	string customerName;
	Bank* bankList[10];
	Card* cardList[100];
public:
	// Customer
	Customer(string name);
	~Customer();
	void getName();
	// Account
	void newAccount();
	void deleteAccount();
	void getAccountList();
	// Card
	void newCard();
	void deleteCard();
	void getCardList();
};