#pragma once

#include "ATM.h"
#include "Cardaccount.h"
#include "Feeinitialize.h"
#include <iostream>
#include <string>
#include <fstream>
#include <cstdio>
using namespace std;

class ATM;
class Account;
class Card;
class Fee;
class Transaction {
private:
    int transactionID;
    long long cardNum;
    int serialNum;
    string transType;
    int transAmount;

public:
    Transaction(ATM* serialNumber, Card* cardNumber, string type, Fee* fee);

    Transaction(ATM* serialNumber, Card* accountNumberFrom, Card* accountNumberTo, string type, Fee* fee);

    virtual ~Transaction();

    // Actions
    void deposit(ATM* serialNumber, Card* cardNumber, Fee* fee);

    void withdrawal(ATM* serialNumber, Card* cardNumber, Fee* fee);



    void addcash(ATM* serialNumber, Card* cardNumber, Fee* fee);

    void addcheck(ATM* serialNumber, Card* cardNumber, Fee* fee);

    void cashtransfer(ATM* serialNumber, Card* cardNumber, Fee* fee);


};