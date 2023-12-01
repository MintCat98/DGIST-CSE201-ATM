#include "Bank.h"
#include <iostream>

using namespace std;



Bank::Bank(string name) {
    this->bankName = name;
    for (int i = 0; i < 100; i++) {
        atmList[i] = nullptr;
    }

    cout << "[Const-B]" << this->bankName << " Bank is created." << endl;
}


Bank::~Bank() {
    cout << "[Dest-B] Bank " << this->bankName << " Bank is deleted." << endl;
}

string Bank::getName() {
    return bankName;
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
