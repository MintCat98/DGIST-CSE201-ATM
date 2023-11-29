#include "Cardaccount.h"

/*
Card::Card() :cardNum() {
    cout << "[Const - C] A new card created" << endl;
}
*/
/*
int Card::getCardNum() {
    return cardNum;
}
*/

Card::~Card() {
    cout << "[Dest-C] A card is deleted" << endl;

}

bool Card::verifyPassword(string inputPassword) {
    return password_ == inputPassword;
}

bool Card::accessAccount() {
    if (verifyPassword(getPasswordFromUser())) {
        cout << "Accessing Account ... \n ";
        return true;
    }
    else {
        cout << "Incorrect password. Access denied.\n";
        return false;
    }
}

int Card::getCardNum() {
    return getAccountNum();
}