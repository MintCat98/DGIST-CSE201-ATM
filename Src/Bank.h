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

public:
    // Bank
    Bank(string name);
    ~Bank();
    string getName();
    // ATM
    void newATM(ATM*);
    void deleteATM(ATM*);
    void getATMList();
    // Customer
    void newCustomer(Customer*);
    void deleteCustomer(Customer*);
    void getCustomerList();
};