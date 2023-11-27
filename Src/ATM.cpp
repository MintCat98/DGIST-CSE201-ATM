#include "ATM.h"

int ATM::atmIDs = 0;
int ATM::transNums = 0;

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
int ATM::getCashTotal() {
    // Ignore check papers
    int sum = 0;
    for (auto iter = this->cashAmount.begin(); iter != this->cashAmount.end(); iter++) {
        sum += (iter->first) * (iter->second);
    }
    return sum;
}
void ATM::selectLanguage() {
	string lang;
	// Loop until we get valid inputs.
	while (lang == "KR" || lang == "kr" || lang == "EN" || lang == "en") {
		// Select
		cout << "Please select language(KR/EN): "; cin >> lang; cout << "\n";
		// Check
		if (lang == "KR" || lang == "kr") {
			cout << "Language set as Korean.\n";
			this->isKorean = true;
		}
		else if (lang == "EN" || lang == "en") {
			cout << "Language set as English.\n";
			this->isKorean = false;
		}
		else {
			cout << "[Error] Please insert valid inputs!\n";
		}
	}
}
bool ATM::isBilingual() {
    return this->biLanguage;
}
void ATM::setEN() {
    this->isKorean = false;
}
bool ATM::isCardAvailable() {

}
bool ATM::isAdmin() {

}
bool ATM::isCardPW() {

}
void ATM::transaction() {

}
int ATM::decideFees() {

}
bool ATM::isSufficient() {

}
void ATM::updateCashAmmount(bool isDeposit) {

}
void ATM::printATMStatus() {

}
void ATM::printHistory() {

}
