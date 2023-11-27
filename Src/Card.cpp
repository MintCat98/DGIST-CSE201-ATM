#include "Card.h"

#include "Card.h"

Card::Card() :cardNum(0) {
    cout<<'[Const-C] A new card created'<<endl;
}


int Card::getCardNum() const {
    return cardNum;
}


Card::~Card() {
    cout<<'[Dest-C] A card is deleted'<<endl;

}
