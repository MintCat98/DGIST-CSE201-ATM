#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "ATM.h"

using namespace std;
class ATM;

class Bank {
private:
    string bankName;
    ATM* atmList[100];

public:
    // Bank
    Bank(string name);
    ~Bank();
    string getName();
    // ATM
    void newATM(ATM*);
    void deleteATM(ATM*);
    void getATMList();
};