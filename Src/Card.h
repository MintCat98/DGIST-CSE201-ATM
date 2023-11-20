#pragma once

#include "Account.h"

class Card : public Account {
private:
	int cardNum;
public:
	// Card
	Card();
	int getCardNum();
	virtual ~Card();
	void getCardNum();
};