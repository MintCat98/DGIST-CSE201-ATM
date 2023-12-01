#pragma once
#include <fstream>
#include <map>
#include "Bank.h"
#include "Transaction.h"
#include <cstdio>
#include <vector>
#include <string>
class Bank;
class Transaction;

class ATM {
private:
    int aID;
    Bank* ownedBy;
    int serialNum;
    vector<Bank*> bankList;
    bool singleBank;
    bool biLanguage;
    bool isKorean;
    map<int, int> cashAmount; // sort: amount
    vector<Transaction*> transHistory;
    static int atmIDs;
    static int transNum;
    bool withdrawalsuccess;


public:
    void setWdsuccess(bool torf);
    bool getWdsuccess();

    // ATM
    ATM(Bank* primary, int sNum, bool single, bool lang, map<int, int> cash);
    ~ATM();
    int getSerialNum();
    bool isBilingual();
    void selectLanguage(); // KR(true), EN(false)
    void setEN();
    bool getKR();
    string getPrimaryBank();

    bool isSingleBank();


    // Transaction
    void transaction();
    void updateCashAmmount(bool isDeposit);
    int getTransNum();
    void setTransNum(int transnum);
    int get1000won();
    int get5000won();
    int get10000won();
    int get50000won();
    void set1000won(int bill);
    void set5000won(int bill);
    void set10000won(int bill);
    void set50000won(int bill);
    int getCashAmount();
    void setCashAmount(int cash);

    void deleteFile();

    void viewTransactionHistory() {
        vector<string> data;
        ifstream historyFile("transaction_history.txt");
        if (!historyFile) {
            cerr << "Error opening transaction history file.\n";
            return;
        }
        string line;
        while (getline(historyFile, line)) {
            cout << line << endl;
        }
        historyFile.close();
    }

    void adminMenu() {
        int choice;
        while (true) {
            // View Options
            cout << "\n==========[Admin Menu]===========\n";
            cout << "Please select an option as an integer.\n";
            cout << "  1) View Transaction History\n";
            cout << "  2) Exit\n";
            cout << " - Select: ";
            cin >> choice;
            if (choice == 1) {
                viewTransactionHistory();
                break;
            }
            else if (choice == 2) {
                cout << "Exiting Admin Menu\n";
                break;
            }
            else {
                cout << "[Error] Insert a valid option!\n";
            }
        }
    };
};