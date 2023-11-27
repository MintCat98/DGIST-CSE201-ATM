#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "Bank.h"
#include "ATM.h"
#include "Customer.h"
#include "Card.h"
#include "Transaction.h"

using namespace std;

int main() {
	/*
	* [Init Section]
	*/
	cout << "====================================================\n";
	cout << "|  DGIST CSE201 Term-Project / ATM Implementation  |\n";
	cout << "====================================================\n";
	cout << "\n";
	// Containers
	map<string, Bank*> banks;   // Name: Bank
	map<int, ATM*> ATMs;        // SN: ATM
	map<string, Card*> cards;   // No.: Card
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
        // Init Inputs
        cout << "[ATM Init.] Please insert below.";
        string bank; int sn; string single; string bilang; map<int, int> cash;
        // Input check 구현 필요!!!!!!!!!!
        cout << "Primary Bank      : "; cin >> bank; cout << "\n";  // 존재 여부 확인
        cout << "Serial Number     : "; cin >> sn; cout << "\n";    // 중복 확인
        cout << "Type(S/NS)        : ";	cin >> single; cout << "\n";// 입력 확인
        cout << "Bilingual(T/F)    : ";	cin >> bilang; cout << "\n";// 입력 확인
        cout << "Amount of 1000won : ";	cin >> cash[1000]; cout << "\n";// 입력 확인
        cout << "Amount of 5000won : ";	cin >> cash[5000]; cout << "\n";// 입력 확인
        cout << "Amount of 10000won: ";	cin >> cash[10000]; cout << "\n";// 입력 확인
        cout << "Amount of 50000won: ";	cin >> cash[50000]; cout << "\n";// 입력 확인
        // Instantiation
        // 이거 확인 필요!!!!!!!!
        ATM atm = ATM(banks[bank], sn, true, true, cash);
        ATMs[sn] = &atm;
	}
	// Card
	int numOfCards;
	cout << "[Init] Please init Account/Card instances.\n";
	cout << "How many: "; cin >> numOfCards; cout << "\n";
	for (int i = 0; i < numOfCards; i++) {
		// Instanciate Cards!
	}

	/*
	* [Loop Sessions]
	* (Infinite loop until a user select End option.)
	* 0. Welcome message
	* 1. Insert a card
	*	 (Need to check whether it is primary.)
	* 2. Select language
		 (If an ATM is bilingual one.)
	* 3. View options
	* 4. If it ends, view a summary
	*/
    int selected{0};
    while (selected != 2) {
        // Base Session
        cout << "======= Please select one =======\n";
        cout << "  1. Select an ATM\n";
        cout << "  2. Exit the Whole Sessions\n";
        cout << "=================================\n";
        cout << " - Select: "; cin >> selected; cout << "\n";
        switch (selected) {
            case 2:
                break;
            case 1:
                // Select an ATM
                int sn;
                ATM* currentATM;
                while (true) {
                    cout << "[ATM] Select an ATM w.Serial Numbers: "; cin >> sn; cout << "\n";
                    auto find = ATMs.find(sn);
                    if (find != ATMs.end()) { // Exists
                        currentATM = ATMs[sn];
                        break;
                    }
                    else { // Error
                        cout << "[Error] Insert a valid serial number!\n";
                    }
                }
                // Insert a Card
                int no;
                Card* currentCard;
                while (true) {
                    cout << "[Card] Insert a card to start: "; cin >> no; cout << "\n"
                    auto find = cards.find(no); // 카드 인스턴스 안 만들어져서 오류
                    if (find != cards.end()) { // Exists
                        currentCard = cards[no];
                        break;
                    }
                    else { // Error
                        cout << "[Error] Insert a valid card!\n";
                    }
                }
                // Admin or Customer
                // 카드나 어카운트 수정 필요
                // Customer 기준
                cout << "======================================================\n";
                // Set Language
                if (currentATM->isBilingual()) { // If bilingual
                    currentATM->selectLanguage();
                }
                else { // If unilingual
                    currentATM->setEN();
                }
                // Session Loop
                cout << "======================================================\n";
                int option; option = 0; // 알 수 없는 에러 때문에 이렇게 초기화 함
                while (option != 5) {
                    // View Options
                    cout << "[Please select an option as an integer.]\n";
                    cout << " 1) Deposit\n";
                    cout << " 2) Withdrawal\n";
                    cout << " 3) Transfer\n";
                    cout << " 4) Print a Receipt\n";
                    cout << " 5) Exit\n";
                    cout << " - Select: "; cin >> selected; cout << "\n";
                    switch (option) {
                        case 1:
                            // Deposit
                        case 2:
                            // Withdrawal
                        case 3:
                            // Transfer
                        case 4:
                            // Print Receipts
                        case 5:
                            cout << "(Note) Sessions in ATM " << currentATM->getSerialNum() << "ended.\n";
                            break;
                        default:
                            cout << "[Error] Insert a valid option!\n\n";
                    }
                }
            default:
                cout << "[Error] Insert a valid option!\n\n";
        }
    }


    // Normal User

	return 0;
}