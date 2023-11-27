#pragma once

#include "ATM.h"
#include "Card.h"
#include <iostream>
#include <string>
#include <fstream>


class Fee {
private:
	string feeName;
	int dpFeeNonp;
	int dpFeePrim;
	int wdFeePrim;
	int wdFeeNonp;
	int atFeeBetPrim;
	int atFeeBetPNonp;
	int afFeeBetNonp;
	int ctFeeAny;
public:
	Fee(string name);
	int getdpFeeNonp();
	int getdpFeePrim();
	int getwdFeePrim();
	int getwdFeeNonp();
	int getatFeeBetPrim();
	int getatFeeBetPNonp();
	int getafFeeBetNonp();
	int getctFeeAny();
};

