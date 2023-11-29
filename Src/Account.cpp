#include "Cardaccount.h"
#include <iostream>
using namespace std;

Account::Account(string bankName, string userName, long long accountNum, int funds) {
    cout << "Account created" << endl;
    this->bankName_ = bankName;
    this->userName_ = userName;
    this->accountNum_ = accountNum;
    this->balance_ = funds;
}

Account::~Account() {
    cout << " Account is deleted.\n";
}

string Account::getBankName() const {
    return this->bankName_;
}

string Account::getOwner() const {
    return this->userName_;
}

long long Account::getAccountNum() const {
    return this->accountNum_;
}

void Account::setbalance(int balance) {
    this->balance_ = balance;
}

int Account::getbalance() const {
    return this->balance_;
}

bool Account::getPrimary(ATM* atm) {
    if (atm->getPrimaryBank() == this->bankName_) {
        return true;
    }
    else {
        return false;
    }
}