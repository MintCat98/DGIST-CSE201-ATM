#include "Bank.h"
#include <iostream>

using namespace std;



// Constructor
Bank::Bank() {
    for (int i = 0; i < 100; i++) {
        atmList[i] = nullptr;
    }
    for (int i = 0; i < 1000; i++) {
        customerList[i] = nullptr;
    }
    isPrimaryBank = false;
    cout << "[Const-B] Bank " << bankName << " is created." << endl;
}

// Destructor
Bank::~Bank() {
    cout << "[Dest-B] Bank " << this->bankName << " is deleted.\n";
}

void Bank::getName() {
    cout << bankName << endl;
}

void Bank::newATM(ATM* newATM) {
    for (int i = 0; i < 100; i++) {
        if (atmList[i] == nullptr) {
            atmList[i] = newATM;
            break;
        }
    }
}

void Bank::deleteATM(ATM* targetATM) {
    for (int i = 0; i < 100; i++) {
        if (atmList[i] == targetATM) {
            atmList[i] = nullptr;
            break;
        }
    }
}
//[atms of kookmin]:(111) (222)
void Bank::getATMList() {
    cout << "[ATMs of" << this->bankName << "]: ";
    for (int i = 0; i < 100; i++) {
        if (atmList[i] != nullptr) {
            cout << "(" << atmList[i]->getSerialNum() << ") ";
        }
    }
    cout << endl;
}


void Bank::newCustomer(Customer* newCustomer) {
    for (int i = 0; i < 1000; i++) {
        if (customerList[i] == nullptr) {
            customerList[i] = newCustomer;
            break;
        }
    }
}

void Bank::deleteCustomer(Customer* targetCustomer) {
    for (int i = 0; i < 1000; i++) {
        if (customerList[i] == targetCustomer) {
            customerList[i] = nullptr;
            break;
        }
    }
}

void Bank::getCustomerList() {
    for (int i = 0; i < 1000; i++) {
        if (customerList[i] != nullptr) {
            customerList[i]->getName();
            cout << "\n";
        }
    }
}
