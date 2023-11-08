#pragma once

#include "Bank.h"
#include "Account.h"
#include "Card.h"

class Bank;
class Account;
class Card;

class Customer {
private:
	string customerName;
	Bank* bankList[10];
	Account* accountList[100];
	Card* cardList[100];
public:
	// Customer
	Customer();
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