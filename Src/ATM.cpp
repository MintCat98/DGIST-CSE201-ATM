#include "ATM.h"
#include <cstdio>
int ATM::atmIDs = 0;
int ATM::transNum = 0;

ATM::ATM(Bank* primary, int sNum, bool single, bool lang, map<int, int> cash) {
    ATM::atmIDs++;
    this->aID = atmIDs;
    this->ownedBy = primary;
    this->serialNum = sNum;
    this->singleBank = single;
    this->biLanguage = lang;
    this->cashAmount = cash;
    cout << "[Const-A] A new (ATM " << this->aID << ") is added.\n";
}
ATM::~ATM() {
    cout << "[Dest-A] ATM No." << this->serialNum << "is deleted.\n";
}
int ATM::getSerialNum() { return this->serialNum; }
/*
int ATM::getCashTotal() {
    // Ignore check papers
    int sum = 0;
    for (auto iter = this->cashAmount.begin(); iter != this->cashAmount.end(); iter++) {
        sum += (iter->first) * (iter->second);
    }
    return sum;
}
*/
void ATM::selectLanguage() {
    string lang;
    // Loop until we get valid inputs.
    while (true) {
        // Select
        cout << "Please select language(KR/EN): "; cin >> lang;
        // Check
        if (lang == "KR" || lang == "kr") {
            cout << "Language set as Korean.\n";
            this->isKorean = true;
            break;
        }
        else if (lang == "EN" || lang == "en") {
            cout << "Language set as English.\n";
            this->isKorean = false;
            break;
        }
        else {
            cout << "[ValueError] Invalid inputs! Enter 'KR' or 'EN'!\n";
        }
    }
}
bool ATM::isBilingual() {
    return this->biLanguage;
}
void ATM::setEN() {
    this->isKorean = false;
}
bool ATM::getKR() {
    return this->isKorean;
}
int ATM::getTransNum() {
    return this->transNum;
}
void ATM::setTransNum(int transnum) {
    this->transNum = transnum;
}

int ATM::get1000won() {
    return cashAmount[1000];
}

int ATM::get5000won() {
    return cashAmount[5000];
}

int ATM::get10000won() {
    return cashAmount[10000];
}

int ATM::get50000won() {
    return cashAmount[50000];
}

void ATM::set1000won(int bill) {
    cashAmount[1000] = bill;
}

void ATM::set5000won(int bill) {
    cashAmount[5000] = bill;
}

void ATM::set10000won(int bill) {
    cashAmount[10000] = bill;
}

void ATM::set50000won(int bill) {
    cashAmount[50000] = bill;
}

int ATM::getCashAmount() {
    return cashAmount[12345];
}

void ATM::setCashAmount(int cash) {
    cashAmount[12345] = cash;
}


string ATM::getPrimaryBank() {
    return ownedBy->getName();
}

void ATM::deleteFile() {
    const char filename[] = "receipt.txt";
    if (remove(filename) == 0) {
        std::cout << "File '" << filename << "' deleted successfully.\n";
    }
    else {
        std::perror("Error deleting file");
    }
}

bool ATM::isSingleBank() {
    return singleBank;
}

