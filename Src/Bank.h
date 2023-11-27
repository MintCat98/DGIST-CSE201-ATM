#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "ATM.h"
#include "Customer.h"

using namespace std;
class ATM;
class Customer;

class Bank {
private:
	string bankName;
	ATM* atmList[100];
	Customer* customerList[1000];
	bool isPrimaryBank;
	
public:
	// Bank
	Bank(string name);
	~Bank();
	void getName();
	// ATM
	void newATM(ATM*);
	void deleteATM(ATM*);
	void getATMList();
	// Customer
	void newCustomer(Customer*);
	void deleteCustomer(Customer*);
	void getCustomerList();
};