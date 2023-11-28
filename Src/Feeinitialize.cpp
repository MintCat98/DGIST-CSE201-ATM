#include "Feeinitialize.h"


Fee::Fee(string fee) {
    feename = fee;
    int dfnpb, dfpb, wfpb, wfnpb, atfbpb, atfbpnpb, atfbnpb, ctfab;
    cout << "Set deposit fee for non-primary banks" << endl;
    cin >> dfnpb;
    dpFeeNonp = dfnpb;
    cout << "Set deposit fee for primary banks" << endl;
    cin >> dfpb;
    dpFeePrim = dfpb;
    cout << "Set withdrawal fee for a primary bank" << endl;
    cin >> wfpb;
    wdFeePrim = wfpb;
    cout << " Set withdrawal fee for non-primary banks" << endl;
    cin >> wfnpb;
    wdFeeNonp = wfnpb;
    cout << " Set Account Transfer fee between primary banks" << endl;
    cin >> atfbpb;
    atFeeBetPrim = atfbpb;
    cout << " Set Account Transfer fee between primary and non-primary banks. " << endl;
    cin >> atfbpnpb;
    atFeeBetPNonp = atfbpnpb;
    cout << " Set Account Transfer fee between non-primary banks." << endl;
    cin >> atfbnpb;
    atFeeBetNonp = atfbnpb;
    cout << " Set Cash Transfer fee to any bank." << endl;
    cin >> ctfab;
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