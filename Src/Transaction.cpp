#include "Transaction.h"
#include <cstdio>
Transaction::Transaction(ATM* serialNumber, Card* cardNumber, string type, Fee* fee) {

    // Transaction 공통사항

    this->cardNum = cardNumber->getAccountNum(); // Transaction의 cardnum을 지정
    this->transType = type;					  // Transtype을 지정
    this->transactionID = (100 * serialNumber->getSerialNum()) + serialNumber->getTransNum();
    // 임의로 거래 id를 ATM의 시리얼 넘버에 100을 곱한 후, TransNum을 더해준다.
    serialNumber->setTransNum(serialNumber->getTransNum() + 1);
    // 거래 번호를 1 더해서 저장해 둔다.
    if (serialNumber->getKR() == true) {
        cout << "[생성자] 새로운 거래가 생성되었습니다!: (" << this->transactionID << ")" << endl;
    }
    else {
        cout << "[Constructor]New transaction Created: (" << this->transactionID << ")" << endl;
    }

    // deposit or withdrawal

    if (type == "deposit") {
        this->deposit(serialNumber, cardNumber, fee); // deposit을 type으로 받으면, deposit 실행
    }
    else if (type == "withdrawal") {
        this->withdrawal(serialNumber, cardNumber, fee); // withdrawal이면 withdrawal 실행
    }
    else if (type == "cashtransfer") {
        this->cashtransfer(serialNumber, cardNumber, fee);
    }
}

Transaction::~Transaction() {
    cout << "Transaction Destructor called" << endl; // Destructor
}

void Transaction::deposit(ATM* serialNumber, Card* cardNumber, Fee* fee) {

    // cash , check를 판명한다.
    if (serialNumber->getKR() == true) {
        cout << "[현금 = 0 / 수표 = 1]" << endl;
    }
    else {
        cout << "[Cash = 0 / Check = 1]" << endl;
    }
    int cashorcheck;
    cin >> cashorcheck;
    if (cashorcheck == 0) {
        this->addcash(serialNumber, cardNumber, fee);
    }
    else if (cashorcheck == 1) {
        this->addcheck(serialNumber, cardNumber, fee);
    }
}

void Transaction::addcash(ATM* serialNumber, Card* cardNumber, Fee* fee) {
    if (serialNumber->getKR() == true) {
        cout << "각각 지폐를 얼마나 넣을지 순서대로 말씀해 주세요.[0 0 0 0]" << endl;
        cout << "1000원, 5000원, 10000원, 50000원" << endl;
    }
    else {
        cout << "Number of each bills. [0 0 0 0]" << endl;
        cout << "KRW 1,000, KRW 5,000,KRW 10,000, KRW 50,000" << endl;
    }

    // 천원, 오천원 , 만원 ,오만원권 얼마를 넣을지 고른다.
    int c, oc, m, om;
    cin >> c >> oc >> m >> om;
    int billamount = c + oc + m + om;
    int balanceadd = 1000 * c + 5000 * oc + 10000 * m + 50000 * om;


    int feemoney = 0; // 수수료 책정
    if (cardNumber->getPrimary(serialNumber) == true) {
        // primary가 맞을 때, 정해놓았던 fee를 불러온다.
        feemoney = fee->getdpFeePrim();
        if (serialNumber->getKR() == true) {
            cout << " 수수료는 " << feemoney << "원입니다. 당신의 카드는 주거래 카드입니다. " << endl;
        }
        else {
            cout << " The fee is " << feemoney << "won. Your card is primary." << endl;
        }

    }
    else {
        // 아닐 때, fee를 불러온다.
        feemoney = fee->getdpFeeNonp();
        if (serialNumber->getKR() == true) {
            cout << " 수수료는 " << feemoney << " 원입니다. 당신의 카드는 주거래 카드가 아닙니다. " << endl;
        }
        else {
            cout << " The fee is " << feemoney << " won.Your card is non-primary." << endl;
        }
    }

    if (billamount > 50 || balanceadd < feemoney) {
        if (serialNumber->getKR() == true) {
            cout << " 적절하지 않은 양입니다. 50장 이상이거나, 수수료보다 적습니다. " << endl; // 수수료보다 작은 값이거나, billamount 초과치를 넘어설 경우 오류 반환.
        }
        else {
            cout << " Error amount. " << endl; // 수수료보다 작은 값이거나, billamount 초과치를 넘어설 경우 오류 반환.
        }
    }
    else {
        if (serialNumber->getKR() == true) {
            cout << " 성공적으로  " << balanceadd << "원을 " << cardNumber->getAccountNum() << "에 입금하였습니다." << endl;
        }
        else {
            cout << " Successfully deposited " << balanceadd << " on card number" << cardNumber->getAccountNum() << endl;
        }

        // card의 account 부분의 balance를 교체한다. 이는 기존 잔액에서 추가 잔액을 더하고, 수수료를 뺀 값이다.
        cardNumber->setbalance(cardNumber->getbalance() + balanceadd - feemoney);

        // 각 지폐별로 증가시킴.
        serialNumber->set1000won(serialNumber->get1000won() + c);
        serialNumber->set5000won(serialNumber->get5000won() + oc);
        serialNumber->set10000won(serialNumber->get10000won() + m);
        serialNumber->set50000won(serialNumber->get50000won() + om);
        serialNumber->setCashAmount(serialNumber->getCashAmount() + balanceadd);

        ofstream history("transaction_history.txt", ios_base::app);
        if (history.is_open()) {
            history << "Transaction ID : " << this->transactionID << " / Card Number : " << cardNumber->getAccountNum() << " / Transaction Type : " << this->transType << " / Cash" << " Amount : " << balanceadd << "\n";
        }
        history.close();
        ofstream receipt("receipt.txt", ios::app);
        if (receipt.is_open()) {
            receipt << "Transaction ID : " << this->transactionID << " / Card Number : " << cardNumber->getAccountNum() << " / Transaction Type : " << this->transType << " / Cash" << " Amount : " << balanceadd << "\n";
        }
        receipt.close();
    }
}

void Transaction::addcheck(ATM* serialNumber, Card* cardNumber, Fee* fee) {
    if (serialNumber->getKR() == true) {
        cout << "수표 몇 장을 넣으실 건가요? (최대 10장)" << endl;
    }
    else {
        cout << "Number of checks (Max : 10)" << endl;
    }
    int howmanychecks;
    cin >> howmanychecks;
    if (howmanychecks > 10) {
        if (serialNumber->getKR() == true) {
            cout << "죄송합니다. 10장이 넘었습니다." << endl;
        }
        else {
            cout << "Sorry. You put more than 10." << endl;
        }
    }
    else {
        int balanceadd = 0;
        for (int i = 0; i < howmanychecks; i++) {
            if (serialNumber->getKR() == true) {
                cout << "수표 금액을 입력하십시오." << endl;
            }
            else {
                cout << "Put the value of Check." << endl;
            }
            int value;
            do {
                cin >> value;
                if (value < 100000) {
                    if (serialNumber->getKR() == true) {
                        cout << "수표의 최소 금액은 100,000원부터입니다. 다시 입력하십시오.\n";
                    }
                    else {
                        cout << "Minimum value of the check is 100,000won. Try again.\n";
                    }
                }
            } while (value < 100000);
            balanceadd += value;
        }
        int feemoney = 0; // 수수료 책정
        if (cardNumber->getPrimary(serialNumber) == true) {
            // primary가 맞을 때, 정해놓았던 fee를 불러온다.
            feemoney = fee->getdpFeePrim();
            if (serialNumber->getKR() == true) {
                cout << " 수수료는 " << feemoney << "원입니다. 당신의 카드는 주거래 카드입니다." << endl;
            }
            else {
                cout << " The fee is " << feemoney << "won. Your card is primary." << endl;
            }

        }
        else {
            // 아닐 때, fee를 불러온다.
            feemoney = fee->getdpFeeNonp();
            if (serialNumber->getKR() == true) {
                cout << " 수수료는 " << feemoney << "원입니다. 당신의 카드는 주거래 카드가 아닙니다." << endl;
            }
            else {
                cout << " The fee is " << feemoney << "won. Your card is non-primary." << endl;
            }
        }

        if (serialNumber->getKR() == true) {
            cout << " 성공적으로  " << balanceadd << "원을 " << cardNumber->getAccountNum() << "에 입금하였습니다." << endl;
        }
        else {
            cout << " Successfully deposited " << balanceadd << " on card number" << cardNumber->getAccountNum() << endl;
        }
        cardNumber->setbalance(cardNumber->getbalance() + balanceadd - feemoney);
        ofstream history("transaction_history.txt", ios_base::app);
        if (history.is_open()) {
            history << "Transaction ID : " << this->transactionID << " / Card Number : " << cardNumber->getAccountNum() << " / Transaction Type : " << this->transType << " / Check" << " Amount : " << balanceadd << "\n";
        }
        history.close();

        ofstream receipt("receipt.txt", ios::app);
        if (receipt.is_open()) {
            receipt << "Transaction ID : " << this->transactionID << " / Card Number : " << cardNumber->getAccountNum() << " / Transaction Type : " << this->transType << " / Check" << " Amount : " << balanceadd << "\n";
        }
        receipt.close();
    }
}




void Transaction::withdrawal(ATM* serialNumber, Card* cardNumber, Fee* fee) {
    serialNumber->setWdsuccess(false);
    if (serialNumber->getKR() == true) {
        cout << "얼마를 찾으실 것인지 입력하여 주십시오." << endl;
    }
    else {
        cout << "Withdraw amount" << endl;
    }
    int withdrawamount = 0;
    cin >> withdrawamount;

    bool canwithdrawal = true;
    int c, oc, m, om;
    int amount;
    amount = withdrawamount;

    // 5만원 제거식
    int noteCount = amount / 50000;
    if (noteCount > serialNumber->get50000won()) {
        noteCount = serialNumber->get50000won();
    }
    om = noteCount;
    amount -= 50000 * noteCount;


    // 만원 제거식
    noteCount = amount / 10000;
    if (noteCount > serialNumber->get10000won()) {
        noteCount = serialNumber->get10000won();
    }
    m = noteCount;
    amount -= 10000 * noteCount;


    // 5천원 제거식
    noteCount = amount / 5000;
    if (noteCount > serialNumber->get5000won()) {
        noteCount = serialNumber->get5000won();
    }
    oc = noteCount;
    amount -= 5000 * noteCount;


    // 천원 제거식
    noteCount = amount / 1000;
    if (noteCount > serialNumber->get1000won()) {
        noteCount = serialNumber->get1000won();
    }
    c = noteCount;
    amount -= 1000 * noteCount;


    if (amount > 0) {
        canwithdrawal = false;
    }

    int feemoney = 0; // 수수료 책정
    if (cardNumber->getPrimary(serialNumber) == true) {
        // primary가 맞을 때, 정해놓았던 fee를 불러온다.
        feemoney = fee->getwdFeePrim();
        if (serialNumber->getKR() == true) {
            cout << " 수수료는 " << feemoney << "원입니다. 당신의 카드는 주거래 카드입니다." << endl;
        }
        else {
            cout << " The fee is " << feemoney << "won. Your card is primary." << endl;
        }

    }
    else {
        // 아닐 때, fee를 불러온다.
        feemoney = fee->getwdFeeNonp();
        if (serialNumber->getKR() == true) {
            cout << " 수수료는 " << feemoney << "원입니다. 당신의 카드는 주거래 카드가 아닙니다." << endl;
        }
        else {
            cout << " The fee is " << feemoney << "won. Your card is non-primary." << endl;
        }
    }

    if (withdrawamount + feemoney > cardNumber->getbalance()) {
        if (serialNumber->getKR() == true) {
            cout << "잔액이 부족합니다." << endl;
        }
        else {
            cout << "Not enough money." << endl;
        }
    }
    else if (withdrawamount > 500000) {
        if (serialNumber->getKR() == true) {
            cout << "오류 : 인출 최대금액 50만원을 넘는 값입니다." << endl;
        }
        else {
            cout << "Error: The value exceeds the maximum withdrawal amount of 500,000 won." << endl;
        }
    }
    else if (withdrawamount % 1000 != 0) {
        if (serialNumber->getKR() == true) {
            cout << "1000원의 배수로 입력해 주십시오." << endl;
        }
        else {
            cout << "Please make the unit correctly." << endl;
        }
    }
    else if (withdrawamount > serialNumber->getCashAmount() || canwithdrawal == false) {
        if (serialNumber->getKR() == true) {
            cout << "ATM의 보유 현금이 부족합니다." << endl;
        }
        else {
            cout << "Not enough bills in the ATM." << endl;
        }
    }
    else {
        if (serialNumber->getKR() == true) {
            cout << withdrawamount << "원이 인출되었습니다." << endl;
            cout << "50000 원 -> " << om << " 장 10000 원 -> " << m << " 장 5000 원 -> " << oc << " 장 1000 원 -> " << c << " 장입니다." << endl;
        }
        else {
            cout << "Here is your money. " << withdrawamount << " won." << endl;
            cout << "50000 bill -> " << om << " 10000 bill -> " << m << " 5000 bill -> " << oc << " 1000 bill -> " << c << endl;
        }


        serialNumber->set1000won(serialNumber->get1000won() - c);
        serialNumber->set5000won(serialNumber->get5000won() - oc);
        serialNumber->set10000won(serialNumber->get10000won() - m);
        serialNumber->set50000won(serialNumber->get50000won() - om);
        serialNumber->setCashAmount(serialNumber->getCashAmount() - withdrawamount);
        cardNumber->setbalance(cardNumber->getbalance() - withdrawamount - feemoney);

        if (serialNumber->getKR() == true) {
            cout << " 성공적으로 " << withdrawamount << "원이 카드 번호 " << cardNumber->getAccountNum() << "에서 인출 되었습니다." << endl;
        }
        else {
            cout << " Successfully withdrawn " << withdrawamount << " with card number " << cardNumber->getAccountNum() << endl;
        }
        
        serialNumber->setWdsuccess(true);

        ofstream history("transaction_history.txt", ios_base::app);
        if (history.is_open()) {
            history << "Transaction ID : " << this->transactionID << " / Card Number : " << cardNumber->getAccountNum() << " / Transaction Type : " << this->transType << " / Amount : " << withdrawamount << "\n";
        }
        history.close();

        ofstream receipt("receipt.txt", ios::app);
        if (receipt.is_open()) {
            receipt << "Transaction ID : " << this->transactionID << " / Card Number : " << cardNumber->getAccountNum() << " / Transaction Type : " << this->transType << " / Amount : " << withdrawamount << "\n";
        }
        receipt.close();
    }
}


void Transaction::cashtransfer(ATM* serialNumber, Card* cardNumber, Fee* fee) {
    if (serialNumber->getKR() == true) {
        cout << "각각 지폐를 얼마나 넣을지 순서대로 말씀해 주세요. [0 0 0 0]" << endl;
        cout << "1000원, 5000원, 10000원, 50000원" << endl;
    }
    else {
        cout << "Put in the number of each bills. [0 0 0 0]" << endl;
        cout << "KRW 1,000, KRW 5,000,KRW 10,000, KRW 50,000" << endl;
    }



    int c, oc, m, om;
    cin >> c >> oc >> m >> om;
    int billamount = c + oc + m + om;
    int balanceadd = 1000 * c + 5000 * oc + 10000 * m + 50000 * om;



    if (billamount > 50 || fee->getctFeeAny() > balanceadd) {
        if (serialNumber->getKR() == true) {
            cout << "올바르지 않은 금액입니다. " << endl;
        }
        else {
            cout << "Error amount " << endl;
        }


    }
    else {

        cardNumber->setbalance(cardNumber->getbalance() + balanceadd - fee->getctFeeAny());

        serialNumber->set1000won(serialNumber->get1000won() + c);
        serialNumber->set5000won(serialNumber->get5000won() + oc);
        serialNumber->set10000won(serialNumber->get10000won() + m);
        serialNumber->set50000won(serialNumber->get50000won() + om);
        serialNumber->setCashAmount(serialNumber->getCashAmount() + balanceadd);
        if (serialNumber->getKR() == true) {
            cout << " 성공적으로 " << balanceadd << "원이 계좌번호 " << cardNumber->getAccountNum() << "인 계좌에 이체되었습니다." << endl;
        }
        else {
            cout << " Successfully transferred " << balanceadd << " to account " << cardNumber->getAccountNum() << endl;;
        }


        ofstream history("transaction_history.txt", ios_base::app);
        if (history.is_open()) {
            history << "Transaction ID : " << this->transactionID << " / Card Number : " << cardNumber->getAccountNum() << " / Transaction Type : " << this->transType << " / Cash" << " Amount : " << balanceadd << "\n";
        }
        history.close();
        ofstream receipt("receipt.txt", ios::app);
        if (receipt.is_open()) {
            receipt << "Transaction ID : " << this->transactionID << " / Card Number : " << cardNumber->getAccountNum() << " / Transaction Type : " << this->transType << " / Cash" << " Amount : " << balanceadd << "\n";
        }
        receipt.close();
    }
}

Transaction::Transaction(ATM* serialNumber, Card* accountNumberFrom, Card* accountNumberTo, string type, Fee* fee) {

    // Transaction 공통사항
    this->cardNum = accountNumberFrom->getAccountNum();
    this->transType = type;					  // Transtype을 지정
    this->transactionID = (100 * serialNumber->getSerialNum()) + serialNumber->getTransNum();
    // 임의로 거래 id를 ATM의 시리얼 넘버에 100을 곱한 후, TransNum을 더해준다.
    serialNumber->setTransNum(serialNumber->getTransNum() + 1);
    // 거래 번호를 1 더해서 저장해 둔다.
    if (serialNumber->getKR() == true) {
        cout << "[생성자] 새로운 거래가 생성되었습니다!: (" << this->transactionID << ")";
    }
    else {
        cout << "[Constructor]New transaction Created: (" << this->transactionID << ")";
    }

    // transfer 입니다.
    if (accountNumberFrom->getPrimary(serialNumber) == true && accountNumberTo->getPrimary(serialNumber) == true) {
        if (serialNumber->getKR() == true) {
            cout << "이체 수수료 :" << fee->getatFeeBetPrim() << endl;
        }
        else {
            cout << "Transfer fee :" << fee->getatFeeBetPrim() << endl;
        }
        int transferfee = fee->getatFeeBetPrim();
        if (serialNumber->getKR() == true) {
            cout << "이체하실 금액을 입력하십시오. " << endl;
        }
        else {
            cout << " Transfer amount " << endl;
        }

        int money;
        cin >> money;
        if (accountNumberFrom->getbalance() >= money + transferfee) {
            accountNumberFrom->setbalance(accountNumberFrom->getbalance() - money - transferfee);
            accountNumberTo->setbalance(accountNumberTo->getbalance() + money);
            if (serialNumber->getKR() == true) {
                cout << "성공적으로 " << money << "원이 계좌번호 " << accountNumberFrom->getAccountNum() << "에서 " << accountNumberTo->getAccountNum() << "으로 이체되었습니다." << endl;
            }
            else {
                cout << "Successfully transferred " << money << " from account " << accountNumberFrom->getAccountNum() << " to " << accountNumberTo->getAccountNum() << endl;
            }
            ofstream history("transaction_history.txt", ios_base::app);
            if (history.is_open()) {
                history << "Transaction ID : " << this->transactionID << " Transfer from " << accountNumberFrom->getAccountNum() << " Transfer to " << accountNumberTo->getAccountNum() << " amount : " << money;
                history.close();
            }
            ofstream receipt("receipt.txt", ios::app);
            if (receipt.is_open()) {
                receipt << "Transaction ID : " << this->transactionID << " Transfer from " << accountNumberFrom->getAccountNum() << " Transfer to " << accountNumberTo->getAccountNum() << " amount : " << money;
                receipt.close();
            }
        }
        else {
            if (serialNumber->getKR() == true) {
                cout << "잔액이 부족합니다." << endl;
            }
            else {
                cout << "Not enough funds." << endl;
            }
        }
    }
    else if (accountNumberFrom->getPrimary(serialNumber) != accountNumberTo->getPrimary(serialNumber)) {
        if (serialNumber->getKR() == true) {
            cout << "이체 수수료 : " << fee->getatFeeBetPNonp() << endl;
        }
        else {
            cout << "Transfer fee : " << fee->getatFeeBetPNonp() << endl;
        }
        int transferfee = fee->getatFeeBetPNonp();
        if (serialNumber->getKR() == true) {
            cout << "이체하실 금액을 입력하십시오. " << endl;
        }
        else {
            cout << " Transfer amount " << endl;
        }

        int money;
        cin >> money;
        if (accountNumberFrom->getbalance() >= money + transferfee) {
            accountNumberFrom->setbalance(accountNumberFrom->getbalance() - money - transferfee);
            accountNumberTo->setbalance(accountNumberTo->getbalance() + money);
            if (serialNumber->getKR() == true) {
                cout << "성공적으로 " << money << "원이 계좌번호 " << accountNumberFrom->getAccountNum() << "에서 " << accountNumberTo->getAccountNum() << "으로 이체되었습니다." << endl;
            }
            else {
                cout << "Successfully transferred " << money << " from account " << accountNumberFrom->getAccountNum() << " to " << accountNumberTo->getAccountNum() << endl;
            }
            ofstream history("transaction_history.txt", ios_base::app);
            if (history.is_open()) {
                history << "Transaction ID : " << this->transactionID << "Transfer from " << accountNumberFrom->getAccountNum() << " Transfer to " << accountNumberTo->getAccountNum() << " amount : " << money;
                history.close();
            }
            ofstream receipt("receipt.txt", ios::app);
            if (receipt.is_open()) {
                receipt << "Transaction ID : " << this->transactionID << "Transfer from " << accountNumberFrom->getAccountNum() << " Transfer to " << accountNumberTo->getAccountNum() << " amount : " << money;
                receipt.close();
            }
        }
        else {
            if (serialNumber->getKR() == true) {
                cout << "잔액이 부족합니다." << endl;
            }
            else {
                cout << "Not enough funds." << endl;
            }
        }
    }
    else {
        if (serialNumber->getKR() == true) {
            cout << "이체 수수료 : " << fee->getatFeeBetNonp() << endl;
        }
        else {
            cout << "Transfer fee : " << fee->getatFeeBetNonp() << endl;
        }
        int transferfee = fee->getatFeeBetNonp();
        if (serialNumber->getKR() == true) {
            cout << "이체하실 금액을 입력하십시오. " << endl;
        }
        else {
            cout << "Transfer amount " << endl;
        }

        int money;
        cin >> money;
        if (accountNumberFrom->getbalance() >= money + transferfee) {
            accountNumberFrom->setbalance(accountNumberFrom->getbalance() - money - transferfee);
            accountNumberTo->setbalance(accountNumberTo->getbalance() + money);
            if (serialNumber->getKR() == true) {
                cout << "성공적으로 " << money << " 원을 계좌번호 " << accountNumberFrom->getAccountNum() << " 에서 " << accountNumberTo->getAccountNum() << " 으로 이체하였습니다." << endl;
            }
            else {
                cout << "Successfully transfered " << money << " from account " << accountNumberFrom->getAccountNum() << " to " << accountNumberTo->getAccountNum() << endl;
            }
            ofstream history("transaction_history.txt", ios_base::app);
            if (history.is_open()) {
                history << "Transaction ID : " << this->transactionID << "Transfer from " << accountNumberFrom->getAccountNum() << " Transfer to " << accountNumberTo->getAccountNum() << " amount : " << money;
                history.close();
            }
            ofstream receipt("receipt.txt", ios::app);
            if (receipt.is_open()) {
                receipt << "Transaction ID : " << this->transactionID << "Transfer from " << accountNumberFrom->getAccountNum() << " Transfer to " << accountNumberTo->getAccountNum() << " amount : " << money;
                receipt.close();
            }
        }
        else {
            if (serialNumber->getKR() == true) {
                cout << "잔액이 부족합니다." << endl;
            }
            else {
                cout << "Not enough funds." << endl;
            }
        }
    }
}