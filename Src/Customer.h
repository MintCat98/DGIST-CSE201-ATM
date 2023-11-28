#pragma once

#include "Cardaccount.h"
#include <string>
using namespace std;
class Card;

class Customer {
private:
    string customerName;
    Card* cardList[100];
public:
    // Customer
    Customer(string name);
    ~Customer();
    void getName();
    // Account
    void getAccountList();
    // Card
    void newCard(Card* newCard);
    void deleteCard(Card* targetCard);
    void getCardList();
};