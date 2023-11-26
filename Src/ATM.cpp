#include "ATM.h"

int ATM::transNum = 0;
ATM::ATM() {

}
ATM::~ATM() {

}
void ATM::sessionLoop() {

}
int ATM::getSerialNum() {

}
void ATM::selectLanguage() {

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
void ATM::settranslist(int num, string history) {
	this->transactionlist[num] = history;
}
void ATM::printATMStatus() {

}
void ATM::printHistory() {

}
