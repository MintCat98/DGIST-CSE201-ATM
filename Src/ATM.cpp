#include "ATM.h"

int ATM::transNum = 0;

ATM::ATM(Bank* primary, int sNum, bool single, bool lang, map<int, int> cash) {
	// Input Container
	vector<string> inputs(8);

	// Insert Info Section
	cout << "[ATM Init.] Please insert below.";
	cout << "Primary Bank      : "; cin >> inputs[0]; cout << "\n";
	cout << "Serial Number     : "; cin >> inputs[1]; cout << "\n";
	cout << "Type(S/NS)        : ";	cin >> inputs[2]; cout << "\n";
	cout << "Bilingual(T/F)    : ";	cin >> inputs[3]; cout << "\n";
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
	/*
	* [Infinite loop until an user select End option.]
	* 0. Welcome message
	* 1. Insert a card
	*	 (Need to check whether it is primary.)
	* 2. Select language
		 (If an ATM is bilingual one.)
	* 3. View options
	* 4. If it ends, view a summary
	*/

	// Welcome
	cout << "\n";
	cout << "=========================================\n";
	cout << "[ATM " << this->serialNum << "]\n";
	cout << "Welcome! To start, insert a card!\n";
	cout << "=========================================\n";
	// Insert a Card
	cout << "[Card]: "; // IDK how to do.
	// main.cpp로 옮기기

	// Normal User
	// Set Language
	if (this->biLanguage) {
		this->selectLanguage();
	}
	else {
		this->isKorean = false;
	}
	// Session Loop
	int selected = 0;
	while (selected != 5) {
		// View Options
		cout << "[Please select an option as an integer.]\n";
		cout << " 1) Deposit\n";
		cout << " 2) Withdrawal\n";
		cout << " 3) Transfer\n";
		cout << " 4) Print a Receipt\n";
		cout << " 5) Exit\n";
		cout << "- Select: "; cin >> selected; cout << "\n";
		continue;
	}
	// Admin
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
int ATM::getCashTotal() {
	// Ignore check papers
	int sum = 0;
	for (auto iter = this->cashAmount.begin(); iter != this->cashAmount.end(); iter++) {
		sum += (iter->first) * (iter->second);
	}
	return sum;
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
/*
void ATM::settranslist(int num, string history) {
	this->transactionlist[num] = history;
} ???*/
void ATM::printATMStatus() {

}
void ATM::printHistory() {

}
