#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "Bank.h"
#include "ATM.h"
#include "Customer.h"
#include "Card.h"
#include "Transaction.h"

int main() {
	/*
	* [Init Section]
	*/
	cout << "====================================================\n";
	cout << "|  DGIST CSE201 Term-Project / ATM Implementation  |\n";
	cout << "====================================================\n";
	cout << "\n";
	// Containers
	map<string, Bank*> banks;
	map<int, ATM*> ATMs;
	map<string, Card*> cards;
	// Bank
	int numOfBank;
	cout << "[Init] Please init bank instances.\n";
	cout << "How many: "; cin >> numOfBank; cout << "\n";
	for (int i = 0; i < numOfBank; i++) {
		// Instanciate Banks!
	}
	// ATM
	int numOfATM;
	cout << "[Init] Please init ATM instances.\n";
	cout << "How many: "; cin >> numOfATM; cout << "\n";
	for (int i = 0; i < numOfATM; i++) {
		// Instanciate ATMs!
	}
	// Account and Card
	int numOfCards;
	cout << "[Init] Please init Account/Card instances.\n";
	cout << "How many: "; cin >> numOfCards; cout << "\n";
	for (int i = 0; i < numOfCards; i++) {
		// Instanciate Cards!
	}


	/*
	* [Loop Sessions]
	*/

	return 0;
}