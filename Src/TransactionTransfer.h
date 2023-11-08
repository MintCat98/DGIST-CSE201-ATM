#pragma once

#include "Transaction.h"

class Transaction;

class TransactionTransfer : public Transaction {
private:
	string transName;

public:
	// Transfer
	TransactionTransfer();
	~TransactionTransfer();
	// Action

};