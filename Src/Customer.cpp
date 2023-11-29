#include "Customer.h"

Customer::Customer(string name) {
    // Set name
    this->customerName = name;
    // Lists initialized
    for (int i = 0; i < 100; i++) {
        cardList[i] = nullptr;
    }
    cout << "[Const-C] A new user is added.\n";
}
Customer::~Customer() {
    cout << "[Dest-C] User " << this->customerName << "is deleted.\n";
}
void Customer::getName() { cout << this->customerName; }
void Customer::getAccountList() {
    // [Accounts owned by Name]: (Bank1,11111111) (Bank2,22222222)
    // If empty list => [Accounts owned by Name]:
    cout << "[Accounts owned by " << this->customerName << "]: ";
    for (int i = 0; i < 100; i++) {
        if (cardList[i] != nullptr) {
            cout << "(";
            cardList[i]->getBankName();
            cout << ",";
            cardList[i]->getAccountNum();
            cout << ") ";
        }
    }
    cout << "\n";
}
void Customer::newCard(Card* newCard) {
    for (int i = 0; i < 100; i++) {
        if (cardList[i] == nullptr) {
            cardList[i] = newCard;
            break;
        }
    }
}
void Customer::deleteCard(Card* targetCard) {
    for (int i = 0; i < 100; i++) {
        if (cardList[i] == targetCard) {
            cardList[i] = nullptr;
            break;
        }
    }
}
void Customer::getCardList() {
    // Same with getAccountList() method
    cout << "[Cards owned by " << this->customerName << "]: ";
    for (int i = 0; i < 100; i++) {
        if (cardList[i] != nullptr) {
            cout << "(";
            cardList[i]->getBankName();
            cout << ",";
            cardList[i]->getCardNum();
            cout << ")";
        }
    }
    cout << "\n";
}



