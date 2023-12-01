#pragma once

#include "ATM.h"
#include "Cardaccount.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class Fee {
private:
    string feename;
    int dpFeeNonp;
    int dpFeePrim;
    int wdFeePrim;
    int wdFeeNonp;
    int atFeeBetPrim;
    int atFeeBetPNonp;
    int atFeeBetNonp;
    int ctFeeAny;
public:
    Fee(string name);
    int getdpFeeNonp();
    int getdpFeePrim();
    int getwdFeePrim();
    int getwdFeeNonp();
    int getatFeeBetPrim();
    int getatFeeBetPNonp();
    int getatFeeBetNonp();
    int getctFeeAny();
};
