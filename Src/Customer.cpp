#include "Customer.h"

Customer::Customer(string name) {
	// Set name
	this->customerName = name;
	// Lists initialized
	for (int i = 0; i < 10; i++) {
		bankList[i] = nullptr;
	}
	for (int i = 0; i < 100; i++) {
		cardList[i] = nullptr;
	}
	cout << "[Const-C] A new user is added.\n";
}
Customer::~Customer() {
	cout << "[Dest-C] User " << this->customerName << "is deleted.\n";
}
void Customer::getName() {
	
}
void Customer::newAccount() {
	
}
void Customer::deleteAccount() {

}
void Customer::getAccountList() {

}
void Customer::newCard() {

}
void Customer::deleteCard() {

}
void Customer::getCardList() {

}