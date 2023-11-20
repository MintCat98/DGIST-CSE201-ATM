#include "Account.h"
#include <iostream>
using namespace std;

Account::Account() {
    accountNum = 0;
    primaryBank = nullptr;
    ownedBy = nullptr;
    balance = 0;
    accountHistory = new Transaction(); // I'm not sure
    cout << "[Const-A] A new account is created.\n";
}

Account::~Account() {
    delete accountHistory;
    cout << "[Dest-A] Account is deleted.\n";
}

int Account::getAccountNum() const {
    cout << "Account Number: " << accountNum << "\n";
    return accountNum;
}

void Account::getBankName() const{
    string bankName = "Not Assigned";
    if (primaryBank != nullptr) {
        bankName = primaryBank->getName();
    }
    cout << "Bank Name: " << bankName << "\n";
}
void Account::getOwner() const {
    string userName = "Not Assigned";
    if ( ownedBy != nullptr) {
        userName = ownedBy->getName();
    }
    cout << "User Name: " << userName << "\n";
}

int Account::getBalance() const {
    return balance;
}

void Account::addTransaction(Transaction* transaction) {

}
void Account::updateBalance() {

}
void Account::updateHistory() {

}

//