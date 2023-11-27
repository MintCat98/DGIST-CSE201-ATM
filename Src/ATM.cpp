#include "ATM.h"

int ATM::transNum = 0;
ATM::ATM(Bank* primary, int sNum, bool single, bool lang, map<int, int> cash) {
	// Input Container
	vector<string> inputs(8);

	// Insert Info Section
	cout << "[ATM Init.] Please insert below.";
	cout << "Primary Bank      : "; cin >> inputs[0]; cout << "\n";
	cout << "Serial Number     : "; cin >> inputs[1]; cout << "\n";
	cout << "Type              : ";	cin >> inputs[2]; cout << "\n";
	cout << "Bilingual         : ";	cin >> inputs[3]; cout << "\n";
	cout << "Amount of 1000won : ";	cin >> inputs[4]; cout << "\n";
	cout << "Amount of 5000won : ";	cin >> inputs[5]; cout << "\n";
	cout << "Amount of 10000won: ";	cin >> inputs[6]; cout << "\n";
	cout << "Amount of 50000won: ";	cin >> inputs[7]; cout << "\n";

	// 할당 방법 논의 필요

	cout << "[Const-A] A new ATM is added.\n";
}
ATM::~ATM() {
	cout << "[Dest-A] ATM No." << this->serialNum << "is deleted.\n";
}
void ATM::sessionLoop() {

}
int ATM::getSerialNum() { return this->serialNum; }
bool ATM::selectLanguage() {
	string lang;
	// Loop until we get valid inputs.
	while (lang == "KR" || lang == "kr" || lang == "EN" || lang == "en") {
		// Select
		cout << "Please select language(KR/EN): "; cin >> lang; cout << "\n";
		// Check
		if (lang == "KR" || lang == "kr") {
			cout << "Language set as Korean.\n";
			return true;
		}
		else if (lang == "EN" || lang == "en") {
			cout << "Language set as English.\n";
			return false;
		}
		else {
			cout << "[Error] Please insert valid inputs!\n";
		}
	}
}
int ATM::getCashAmount() {

}
void ATM::setCashAmount(int CashAmount) {

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
void ATM::updateCashAmmount() {

}
void ATM::setTransNum(int transNumber) {

}
int ATM::getTransNum() {

}
/*
void ATM::settranslist(int num, string history) {
	this->transactionlist[num] = history;
} ???*/
void ATM::printATMStatus() {

}
void ATM::printHistory() {

}
