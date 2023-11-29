#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "Bank.h"
#include "ATM.h"
#include "Cardaccount.h"
#include "Transaction.h"
#include <fstream>
#include <cstdio>
using namespace std;

int main() {
    /*
    * [Init Section]
    */
    cout << "====================================================\n";
    cout << "|  DGIST CSE201 Term-Project / ATM Implementation  |\n";
    cout << "====================================================\n";

    // Containers
    map<string, Bank*> banks;       // Name: Bank
    map<int, ATM*> ATMs;            // SN: ATM
    map<long long, Card*> cardMap;        // No: Card
    //map<int, Account *> accountMap;  // No: Account

    // Bank
    int numOfBank;
    cout << "\n[Init] Please init bank instances.\n";
    cout << " - Enter the number of Banks: "; cin >> numOfBank;
    for (int i = 0; i < numOfBank; i++) {
        // Instanciate Banks!
        string bankname;
        cout << " - Enter the name of Bank: "; cin >> bankname;
        banks[bankname] = new Bank(bankname);
    }

    // ATM
    int numOfATM;
    cout << "\n[Init] Please init ATM instances.\n";
    cout << " - Enter the number of ATMs: "; cin >> numOfATM;
    for (int i = 0; i < numOfATM; i++) {
        // Init Inputs
        cout << "\n[ATM Init.] Please insert below.\n";
        string bank;
        int sn;
        string single;
        bool bilang = false;
        map<int, int> cash;
        bool validBank = false;
        do {
            cout << "Primary Bank      : "; cin >> bank;
            if (banks.find(bank) != banks.end()) {
                validBank = true;
            }
            else {
                cout << "[ValueError] Bank not found! Enter a valid bank name!\n";
            }
        } while (!validBank);

        bool duplicateSerial = false;
        do {
            cout << "Serial Number     : "; cin >> sn;
            // Check if the serial number already exists in the ATMs map
            if (ATMs.find(sn) != ATMs.end()) {
                cout << "[ValueError] Serial number already exists! Enter a valid number!\n";
                duplicateSerial = true;
            }
            else {
                duplicateSerial = false;
            }
        } while (duplicateSerial);
        bool realsingle;
        while (true) {
            cout << "Type(S - Single / M - Multi)         : "; cin >> single;
            if (single == "s" || single == "S") {
                realsingle = true;
                break;
            }
            else if (single == "m" || single == "M") {
                realsingle = false;
                break;
            }
            else {
                cout << "[ValueError] Invalid input! Enter 'S' or 'M'!\n";
            }
        }

        string tf;
        cout << "Bilingual(T/F)    : "; cin >> tf;
        if (tf == "T" || tf == "t") {
            bilang = true;
        }
        else if (tf == "F" || tf == "f") {
            bilang = false;
        }
        else {
            cout << "[ValueError] Invalid input! Enter 'T' or 'F'!\n";
        }
        cout << "Amount of 1000won : ";
        cin >> cash[1000];
        cout << "Amount of 5000won : ";
        cin >> cash[5000];
        cout << "Amount of 10000won: ";
        cin >> cash[10000];
        cout << "Amount of 50000won: ";
        cin >> cash[50000];
        cash[12345] = cash[1000] * 1000 + cash[5000] * 5000 + cash[10000] * 10000 + cash[50000] * 50000;
        ATMs[sn] = new ATM(banks[bank], sn, realsingle, bilang, cash);
    }

    // Card
    // ADMIN's Card
    int admin = 999999;

    // Customers' Cards
    int numOfAccounts;
    cout << "\n[Init] Please init Account/Card instances.\n";
    cout << " - Enter the number of Account: ";
    cin >> numOfAccounts;
    for (int i = 0; i < numOfAccounts; i++) {
        cout << "\n[Account/Card Init.] Please insert below.\n";
        string bank, username;
        long long accountnum;
        int funds;
        string issue;
        string password;
        bool validBank = false;
        do {
            cout << "Bank Name          : "; cin >> bank;
            if (banks.find(bank) != banks.end()) {
                validBank = true;
            }
            else {
                cout << "[ValueError] Bank not found! Enter a valid bank name!\n";
            }
        } while (!validBank);
        cout << "User Name          : "; cin >> username;
        bool duplicateAccount = false;
        do {
            cout << "Account/Card Number: "; cin >> accountnum;
            if (cardMap.find(accountnum) != cardMap.end()) {
                cout << "[ValueError] Account number already exists! Enter a valid number!\n";
                duplicateAccount = true;
            }
            else {
                duplicateAccount = false;
            }
        } while (duplicateAccount);
        cout << "Initial Balance    : "; cin >> funds;
        cout << "Password           : "; cin >> password;
        cardMap[accountnum] = new Card(bank, username, accountnum, funds, password);
    }

    // Fee
    cout << "\n[Init] Please init Fee instances\n";
    string feename = "fee";
    Fee* fee = new Fee(feename);


    /*
    * [Loop Sessions]
    */
    int selected = 0;
    while (selected != 4) {
        // Base Session
        cout << "\n======= Please select one =======\n";
        cout << "  1. Select an ATM\n";
        cout << "  2. Display ATM-Info.\n";
        cout << "  3. Display Account-Info.\n";
        cout << "  4. End the Base Session\n";
        cout << "=================================\n";
        cout << " - Select: "; cin >> selected;
        // Cases
        if (selected == 2) { // ATM-Info.
            cout << "\n[ATMs' Stats]\n";
            for (auto atm = ATMs.begin(); atm != ATMs.end(); ++atm) {
                cout << "<List of ATMs>\n";
                cout << " - S/N : " << atm->second->getSerialNum() << "\n";
                cout << " - Cash: " << atm->second->getCashAmount() << "\n";
            }
        }
        else if (selected == 3) { // Account-Info.
            cout << "\n[Accounts' Stats]\n";
            for (auto card = cardMap.begin(); card != cardMap.end(); ++card) {
                cout << "<List of Accounts>\n";
                cout << " - Bank   : " << card->second->getBankName() << "\n";
                cout << " - Owner  : " << card->second->getOwner() << "\n";
                cout << " - Balance: " << card->second->getbalance() << "\n";
            }
        }
        else if (selected == 4) { // Exit
            bool goBack;
            while (true) {
                string yn;
                cout << "\n========== Exit Called ==========\n";
                cout << " Do you really want to end?\n";
                cout << "  (Y/N): ";
                cin >> yn;
                if (yn == "Y" || yn == "y") {
                    cout << "\n Thanks for using!\n";
                    cout << "=================================\n";
                    goBack = false;
                    break;
                }
                else if (yn == "N" || yn == "n") {
                    cout << "\n Returning to the Base session.\n";
                    cout << "=================================\n";
                    goBack = true;
                    break;
                }
                else {
                    cout << "[ValueError] Invalid input! Enter 'Y' or 'N'!\n";
                }
            }
            if (goBack) {
                selected = 0;
            }
            else {
                break;
            }
        }
        else if (selected == 1) { // ATM Session
            int sn;
            ATM* currentATM;
            ofstream history("transaction_history.txt", ios::app);// 파일 열기
            ofstream receipt("receipt.txt"); // 파일 열기
            while (true) {
                cout << "\n[ATM] Select an ATM. Serial Numbers: ";
                cin >> sn;
                auto find = ATMs.find(sn);
                if (find != ATMs.end()) { // Exists
                    currentATM = ATMs[sn];
                    break;
                }
                else { // Error
                    cout << "[ValueError] Invalid serial number! Enter a valid serial number!\n";
                }
            }
            // Insert a Card
            long long no;
            Card* currentCard;
            while (true) {
                cout << "[Card] Insert a card to start: "; cin >> no;
                auto find = cardMap.find(no);
                // Check Admin
                if (no == admin) { // Admin
                    currentATM->adminMenu();
                    break;
                }
                else { // Customer
                    string cardpassword;
                    cout << "       PW: "; cin >> cardpassword;
                    if (cardMap[no]->verifyPassword(cardpassword) && find != cardMap.end()) { // Exists
                        if (currentATM->isSingleBank()) {
                            if (cardMap[no]->getPrimary(currentATM)) {
                                currentCard = cardMap[no];
                                break;
                            }
                            else {
                                cout << "[ValueError] This card cannot be used in this ATM. Try another card.\n";
                            }
                        }
                        else {
                            currentCard = cardMap[no];
                            break;
                        }
                    }
                    else { // Error
                        cout << "[ValueError] Invalid card! Insert a valid card!\n";
                    }
                }
            }
            if (no == admin) {
                continue;
            }
            // Set Language
            cout << "=================================\n";
            if (currentATM->isBilingual()) { // If bilingual
                currentATM->selectLanguage();
            }
            else { // If unilingual
                currentATM->setEN();
            }
            cout << "=================================\n";
            // Divide Language
            if (currentATM->getKR()) {
                // KR version
                while (selected != 6) {
                    // View Options
                    cout << "\n[정수로 옵션을 선택해주세요.]\n";
                    cout << " 1) 예금\n";
                    cout << " 2) 출금\n";
                    cout << " 3) 현금 이체\n";
                    cout << " 4) 계좌 이체\n";
                    cout << " 5) 영수증 출력\n";
                    cout << " 6) 종료\n";
                    cout << " - 선택: ";cin >> selected;
                    if (selected == 1) {
                        //Deposit
                        string type = "deposit";
                        Transaction deposit(currentATM, currentCard, type, fee);
                    }
                    else if (selected == 2) {
                        //Withdrawal
                        string type = "withdrawal";
                        Transaction withdrawal(currentATM, currentCard, type, fee);
                    }
                    else if (selected == 3) {
                        // Cash Transfer
                        long long accountNum;
                        Card* currentAccount;
                        string type = "cashtransfer";
                        while (true) {
                            cout << "어느 계좌로 보내고 싶으신가요?" << endl;
                            cin >> accountNum;
                            auto find = cardMap.find(accountNum);
                            if (find != cardMap.end()) { // Exists
                                currentAccount = cardMap[accountNum];
                                Transaction cashtransfer(currentATM, currentAccount, type, fee);
                                break;
                            }
                            else { // Error
                                cout << "[에러] 계좌 번호가 잘못되었습니다. 유효한 계좌 번호를 입력하세요!\n";
                            }
                        }
                    }
                    else if (selected == 4) {
                        // Account Transfer
                        long long accountNum;
                        Card* currentAccount;
                        string type = "cashAccount";
                        while (true) {
                            cout << "어느 계좌로 보내고 싶으신가요?" << endl;
                            cin >> accountNum;
                            auto find = cardMap.find(accountNum);
                            if (find != cardMap.end()) { // Exists
                                currentAccount = cardMap[accountNum];
                                Transaction accounttransfer(currentATM, currentCard, currentAccount, type, fee);
                                break;
                            }
                            else { // Error
                                cout << "[에러] 계좌 번호가 잘못되었습니다. 유효한 계좌 번호를 입력하세요!\n";
                            }
                        }
                    }
                    else if (selected == 5) {
                        // Print a Receipt
                        vector<string> data;
                        ifstream file("receipt.txt");

                        if (file.is_open()) {
                            string line;
                            while (getline(file, line)) {
                                data.push_back(line);
                            }
                            cout << "파일에서 데이터를 불러옵니다:\n";

                            for (const auto& line : data) {
                                cout << line << endl;
                            }
                        }
                        else {
                            cerr << "파일 읽기를 실패하였습니다.\n";
                        }
                    }
                    else if (selected == 6) {
                        // Exit
                        if (history.is_open()) {
                            history.close();
                        }
                        if (receipt.is_open()) {
                            receipt.close();
                        }
                        currentATM->deleteFile();
                        cout << " Exit  " << endl;
                        break;
                    }
                    else {
                        cout << "[에러] 올바른 값을 입력하세요. (1) ~ (6).!\n\n";
                    }
                }
            }
            else {
                // EN version
                // ATM Session Loop
                while (selected != 6) {
                    // View Options
                    cout << "[Please select an option as an integer.]\n";
                    cout << " 1) Deposit\n";
                    cout << " 2) Withdrawal\n";
                    cout << " 3) Cash Transfer\n";
                    cout << " 4) Account Transfer\n";
                    cout << " 5) Print a Receipt\n";
                    cout << " 6) Exit\n";
                    cout << " - Select: "; cin >> selected;
                    if (selected == 1) {
                        //Deposit
                        string type = "deposit";
                        Transaction deposit(currentATM, currentCard, type, fee);
                    }
                    else if (selected == 2) {
                        //Withdrawal
                        string type = "withdrawal";
                        Transaction withdrawal(currentATM, currentCard, type, fee);
                    }
                    else if (selected == 3) {
                        // Cash Transfer
                        long long accountNum;
                        Card* currentAccount;
                        string type = "cashtransfer";
                        while (true) {
                            cout << "Which account do you want to Transfer?" << endl;
                            cin >> accountNum;
                            auto find = cardMap.find(accountNum);
                            if (find != cardMap.end()) { // Exists
                                currentAccount = cardMap[accountNum];
                                Transaction cashtransfer(currentATM, currentAccount, type, fee);
                                break;
                            }
                            else { // Error
                                cout << "[ValueError] Invalid account number! Enter a valid account number!\n";
                            }
                        }
                    }
                    else if (selected == 4) {
                        // Account Transfer
                        long long accountNum;
                        Card* currentAccount;
                        string type = "cashAccount";
                        while (true) {
                            cout << "Which account do you want to Transfer?" << endl;
                            cin >> accountNum;
                            auto find = cardMap.find(accountNum);
                            if (find != cardMap.end()) { // Exists
                                currentAccount = cardMap[accountNum];
                                Transaction accounttransfer(currentATM, currentCard, currentAccount, type, fee);
                                break;
                            }
                            else { // Error
                                cout << "[ValueError] Invalid account number! Enter a valid account number!\n";
                            }
                        }
                    }
                    else if (selected == 5) {
                        // Print a Receipt
                        vector<string> data;
                        ifstream file("receipt.txt");
                        if (file.is_open()) {
                            string line;
                            while (getline(file, line)) {
                                data.push_back(line);
                            }
                            cout << "Data read from file:\n";
                            for (const auto& line : data) {
                                cout << line << endl;
                            }
                        }
                        else {
                            cerr << "Unable to open file for reading.\n";
                        }
                    }
                    else if (selected == 6) {
                        // Exit
                        if (receipt.is_open()) {
                            receipt.close();
                        }
                        if (history.is_open()) {
                            history.close();
                        }
                        currentATM->deleteFile();
                        cout << " Exit  " << endl;
                        break;
                    }
                    else {
                        cout << "[ValueError] Enter a valid option among (1) ~ (6).!\n\n";
                    }
                }
            }
            
        }
        else {
            cout << "[ValueError] Enter a valid option among (1) ~ (4).!\n\n";
        }
    }

    /*
    * [Deallocation]
    */
    // Delete Banks
    for (auto& bank : banks) {
        delete bank.second;
    }
    banks.clear();
    // Delete ATMs
    for (auto& atm : ATMs) {
        delete atm.second;
    }
    ATMs.clear();
    // Delete Cards
    for (auto& card : cardMap) {
        delete card.second;
    }
    cardMap.clear();
    return 0;
}

