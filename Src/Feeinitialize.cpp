#include "Feeinitialize.h"


Fee::Fee(string fee) {
    feename = fee;
    int dfnpb, dfpb, wfpb, wfnpb, atfbpb, atfbpnpb, atfbnpb, ctfab;
    cout << "1. Deposit fee for non-primary banks\n";
    cout << "  > "; cin >> dfnpb;
    dpFeeNonp = dfnpb;
    cout << "2. Deposit fee for primary banks\n";
    cout << "  > "; cin >> dfpb;
    dpFeePrim = dfpb;
    cout << "3. Withdrawal fee for a primary bank\n";
    cout << "  > "; cin >> wfpb;
    wdFeePrim = wfpb;
    cout << "4. Withdrawal fee for non-primary banks\n";
    cout << "  > "; cin >> wfnpb;
    wdFeeNonp = wfnpb;
    cout << "5. Account Transfer fee between primary banks\n";
    cout << "  > "; cin >> atfbpb;
    atFeeBetPrim = atfbpb;
    cout << "6. Account Transfer fee between primary and non-primary banks\n";
    cout << "  > "; cin >> atfbpnpb;
    atFeeBetPNonp = atfbpnpb;
    cout << "7. Account Transfer fee between non-primary banks\n";
    cout << "  > "; cin >> atfbnpb;
    atFeeBetNonp = atfbnpb;
    cout << "8. Cash Transfer fee to any bank\n";
    cout << "  > "; cin >> ctfab;
    ctFeeAny = ctfab;
}

int Fee::getdpFeeNonp() {
    return dpFeeNonp;
}

int Fee::getdpFeePrim() {
    return dpFeePrim;
}

int Fee::getwdFeePrim() {
    return wdFeePrim;
}

int Fee::getwdFeeNonp() {
    return wdFeeNonp;
}

int Fee::getatFeeBetPrim() {
    return atFeeBetPrim;
}

int Fee::getatFeeBetPNonp() {
    return atFeeBetPNonp;
}
int Fee::getatFeeBetNonp() {
    return atFeeBetNonp;
}
int Fee::getctFeeAny() {
    return ctFeeAny;
}