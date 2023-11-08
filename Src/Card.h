#pragma once

#include "Account.h"

class Card : public Account {
private:
	int cardNum;
public:
	// Card
	Card();
	virtual ~Card();
	void getCardNum();
};