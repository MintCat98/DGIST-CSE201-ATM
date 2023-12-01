#include "Transaction.h"
#include <cstdio>
Transaction::Transaction(ATM* serialNumber, Card* cardNumber, string type, Fee* fee) {

    // Transaction �������

    this->cardNum = cardNumber->getAccountNum(); // Transaction�� cardnum�� ����
    this->transType = type;					  // Transtype�� ����
    this->transactionID = (100 * serialNumber->getSerialNum()) + serialNumber->getTransNum();
    // ���Ƿ� �ŷ� id�� ATM�� �ø��� �ѹ��� 100�� ���� ��, TransNum�� �����ش�.
    serialNumber->setTransNum(serialNumber->getTransNum() + 1);
    // �ŷ� ��ȣ�� 1 ���ؼ� ������ �д�.
    if (serialNumber->getKR() == true) {
        cout << "[������] ���ο� �ŷ��� �����Ǿ����ϴ�!: (" << this->transactionID << ")" << endl;
    }
    else {
        cout << "[Constructor]New transaction Created: (" << this->transactionID << ")" << endl;
    }

    // deposit or withdrawal

    if (type == "deposit") {
        this->deposit(serialNumber, cardNumber, fee); // deposit�� type���� ������, deposit ����
    }
    else if (type == "withdrawal") {
        this->withdrawal(serialNumber, cardNumber, fee); // withdrawal�̸� withdrawal ����
    }
    else if (type == "cashtransfer") {
        this->cashtransfer(serialNumber, cardNumber, fee);
    }
}

Transaction::~Transaction() {
    cout << "Transaction Destructor called" << endl; // Destructor
}

void Transaction::deposit(ATM* serialNumber, Card* cardNumber, Fee* fee) {

    // cash , check�� �Ǹ��Ѵ�.
    if (serialNumber->getKR() == true) {
        cout << "[���� = 0 / ��ǥ = 1]" << endl;
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
        cout << "���� ���� �󸶳� ������ ������� ������ �ּ���.[0 0 0 0]" << endl;
        cout << "1000��, 5000��, 10000��, 50000��" << endl;
    }
    else {
        cout << "Number of each bills. [0 0 0 0]" << endl;
        cout << "KRW 1,000, KRW 5,000,KRW 10,000, KRW 50,000" << endl;
    }

    // õ��, ��õ�� , ���� ,�������� �󸶸� ������ ����.
    int c, oc, m, om;
    cin >> c >> oc >> m >> om;
    int billamount = c + oc + m + om;
    int balanceadd = 1000 * c + 5000 * oc + 10000 * m + 50000 * om;


    int feemoney = 0; // ������ å��
    if (cardNumber->getPrimary(serialNumber) == true) {
        // primary�� ���� ��, ���س��Ҵ� fee�� �ҷ��´�.
        feemoney = fee->getdpFeePrim();
        if (serialNumber->getKR() == true) {
            cout << " ������� " << feemoney << "���Դϴ�. ����� ī��� �ְŷ� ī���Դϴ�. " << endl;
        }
        else {
            cout << " The fee is " << feemoney << "won. Your card is primary." << endl;
        }

    }
    else {
        // �ƴ� ��, fee�� �ҷ��´�.
        feemoney = fee->getdpFeeNonp();
        if (serialNumber->getKR() == true) {
            cout << " ������� " << feemoney << " ���Դϴ�. ����� ī��� �ְŷ� ī�尡 �ƴմϴ�. " << endl;
        }
        else {
            cout << " The fee is " << feemoney << " won.Your card is non-primary." << endl;
        }
    }

    if (billamount > 50 || balanceadd < feemoney) {
        if (serialNumber->getKR() == true) {
            cout << " �������� ���� ���Դϴ�. 50�� �̻��̰ų�, �����Ẹ�� �����ϴ�. " << endl; // �����Ẹ�� ���� ���̰ų�, billamount �ʰ�ġ�� �Ѿ ��� ���� ��ȯ.
        }
        else {
            cout << " Error amount. " << endl; // �����Ẹ�� ���� ���̰ų�, billamount �ʰ�ġ�� �Ѿ ��� ���� ��ȯ.
        }
    }
    else {
        if (serialNumber->getKR() == true) {
            cout << " ����������  " << balanceadd << "���� " << cardNumber->getAccountNum() << "�� �Ա��Ͽ����ϴ�." << endl;
        }
        else {
            cout << " Successfully deposited " << balanceadd << " on card number" << cardNumber->getAccountNum() << endl;
        }

        // card�� account �κ��� balance�� ��ü�Ѵ�. �̴� ���� �ܾ׿��� �߰� �ܾ��� ���ϰ�, �����Ḧ �� ���̴�.
        cardNumber->setbalance(cardNumber->getbalance() + balanceadd - feemoney);

        // �� ���󺰷� ������Ŵ.
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
        cout << "��ǥ �� ���� ������ �ǰ���? (�ִ� 10��)" << endl;
    }
    else {
        cout << "Number of checks (Max : 10)" << endl;
    }
    int howmanychecks;
    cin >> howmanychecks;
    if (howmanychecks > 10) {
        if (serialNumber->getKR() == true) {
            cout << "�˼��մϴ�. 10���� �Ѿ����ϴ�." << endl;
        }
        else {
            cout << "Sorry. You put more than 10." << endl;
        }
    }
    else {
        int balanceadd = 0;
        for (int i = 0; i < howmanychecks; i++) {
            if (serialNumber->getKR() == true) {
                cout << "��ǥ �ݾ��� �Է��Ͻʽÿ�." << endl;
            }
            else {
                cout << "Put the value of Check." << endl;
            }
            int value;
            do {
                cin >> value;
                if (value < 100000) {
                    if (serialNumber->getKR() == true) {
                        cout << "��ǥ�� �ּ� �ݾ��� 100,000�������Դϴ�. �ٽ� �Է��Ͻʽÿ�.\n";
                    }
                    else {
                        cout << "Minimum value of the check is 100,000won. Try again.\n";
                    }
                }
            } while (value < 100000);
            balanceadd += value;
        }
        int feemoney = 0; // ������ å��
        if (cardNumber->getPrimary(serialNumber) == true) {
            // primary�� ���� ��, ���س��Ҵ� fee�� �ҷ��´�.
            feemoney = fee->getdpFeePrim();
            if (serialNumber->getKR() == true) {
                cout << " ������� " << feemoney << "���Դϴ�. ����� ī��� �ְŷ� ī���Դϴ�." << endl;
            }
            else {
                cout << " The fee is " << feemoney << "won. Your card is primary." << endl;
            }

        }
        else {
            // �ƴ� ��, fee�� �ҷ��´�.
            feemoney = fee->getdpFeeNonp();
            if (serialNumber->getKR() == true) {
                cout << " ������� " << feemoney << "���Դϴ�. ����� ī��� �ְŷ� ī�尡 �ƴմϴ�." << endl;
            }
            else {
                cout << " The fee is " << feemoney << "won. Your card is non-primary." << endl;
            }
        }

        if (serialNumber->getKR() == true) {
            cout << " ����������  " << balanceadd << "���� " << cardNumber->getAccountNum() << "�� �Ա��Ͽ����ϴ�." << endl;
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
        cout << "�󸶸� ã���� ������ �Է��Ͽ� �ֽʽÿ�." << endl;
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

    // 5���� ���Ž�
    int noteCount = amount / 50000;
    if (noteCount > serialNumber->get50000won()) {
        noteCount = serialNumber->get50000won();
    }
    om = noteCount;
    amount -= 50000 * noteCount;


    // ���� ���Ž�
    noteCount = amount / 10000;
    if (noteCount > serialNumber->get10000won()) {
        noteCount = serialNumber->get10000won();
    }
    m = noteCount;
    amount -= 10000 * noteCount;


    // 5õ�� ���Ž�
    noteCount = amount / 5000;
    if (noteCount > serialNumber->get5000won()) {
        noteCount = serialNumber->get5000won();
    }
    oc = noteCount;
    amount -= 5000 * noteCount;


    // õ�� ���Ž�
    noteCount = amount / 1000;
    if (noteCount > serialNumber->get1000won()) {
        noteCount = serialNumber->get1000won();
    }
    c = noteCount;
    amount -= 1000 * noteCount;


    if (amount > 0) {
        canwithdrawal = false;
    }

    int feemoney = 0; // ������ å��
    if (cardNumber->getPrimary(serialNumber) == true) {
        // primary�� ���� ��, ���س��Ҵ� fee�� �ҷ��´�.
        feemoney = fee->getwdFeePrim();
        if (serialNumber->getKR() == true) {
            cout << " ������� " << feemoney << "���Դϴ�. ����� ī��� �ְŷ� ī���Դϴ�." << endl;
        }
        else {
            cout << " The fee is " << feemoney << "won. Your card is primary." << endl;
        }

    }
    else {
        // �ƴ� ��, fee�� �ҷ��´�.
        feemoney = fee->getwdFeeNonp();
        if (serialNumber->getKR() == true) {
            cout << " ������� " << feemoney << "���Դϴ�. ����� ī��� �ְŷ� ī�尡 �ƴմϴ�." << endl;
        }
        else {
            cout << " The fee is " << feemoney << "won. Your card is non-primary." << endl;
        }
    }

    if (withdrawamount + feemoney > cardNumber->getbalance()) {
        if (serialNumber->getKR() == true) {
            cout << "�ܾ��� �����մϴ�." << endl;
        }
        else {
            cout << "Not enough money." << endl;
        }
    }
    else if (withdrawamount > 500000) {
        if (serialNumber->getKR() == true) {
            cout << "���� : ���� �ִ�ݾ� 50������ �Ѵ� ���Դϴ�." << endl;
        }
        else {
            cout << "Error: The value exceeds the maximum withdrawal amount of 500,000 won." << endl;
        }
    }
    else if (withdrawamount % 1000 != 0) {
        if (serialNumber->getKR() == true) {
            cout << "1000���� ����� �Է��� �ֽʽÿ�." << endl;
        }
        else {
            cout << "Please make the unit correctly." << endl;
        }
    }
    else if (withdrawamount > serialNumber->getCashAmount() || canwithdrawal == false) {
        if (serialNumber->getKR() == true) {
            cout << "ATM�� ���� ������ �����մϴ�." << endl;
        }
        else {
            cout << "Not enough bills in the ATM." << endl;
        }
    }
    else {
        if (serialNumber->getKR() == true) {
            cout << withdrawamount << "���� ����Ǿ����ϴ�." << endl;
            cout << "50000 �� -> " << om << " �� 10000 �� -> " << m << " �� 5000 �� -> " << oc << " �� 1000 �� -> " << c << " ���Դϴ�." << endl;
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
            cout << " ���������� " << withdrawamount << "���� ī�� ��ȣ " << cardNumber->getAccountNum() << "���� ���� �Ǿ����ϴ�." << endl;
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
        cout << "���� ���� �󸶳� ������ ������� ������ �ּ���. [0 0 0 0]" << endl;
        cout << "1000��, 5000��, 10000��, 50000��" << endl;
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
            cout << "�ùٸ��� ���� �ݾ��Դϴ�. " << endl;
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
            cout << " ���������� " << balanceadd << "���� ���¹�ȣ " << cardNumber->getAccountNum() << "�� ���¿� ��ü�Ǿ����ϴ�." << endl;
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

    // Transaction �������
    this->cardNum = accountNumberFrom->getAccountNum();
    this->transType = type;					  // Transtype�� ����
    this->transactionID = (100 * serialNumber->getSerialNum()) + serialNumber->getTransNum();
    // ���Ƿ� �ŷ� id�� ATM�� �ø��� �ѹ��� 100�� ���� ��, TransNum�� �����ش�.
    serialNumber->setTransNum(serialNumber->getTransNum() + 1);
    // �ŷ� ��ȣ�� 1 ���ؼ� ������ �д�.
    if (serialNumber->getKR() == true) {
        cout << "[������] ���ο� �ŷ��� �����Ǿ����ϴ�!: (" << this->transactionID << ")";
    }
    else {
        cout << "[Constructor]New transaction Created: (" << this->transactionID << ")";
    }

    // transfer �Դϴ�.
    if (accountNumberFrom->getPrimary(serialNumber) == true && accountNumberTo->getPrimary(serialNumber) == true) {
        if (serialNumber->getKR() == true) {
            cout << "��ü ������ :" << fee->getatFeeBetPrim() << endl;
        }
        else {
            cout << "Transfer fee :" << fee->getatFeeBetPrim() << endl;
        }
        int transferfee = fee->getatFeeBetPrim();
        if (serialNumber->getKR() == true) {
            cout << "��ü�Ͻ� �ݾ��� �Է��Ͻʽÿ�. " << endl;
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
                cout << "���������� " << money << "���� ���¹�ȣ " << accountNumberFrom->getAccountNum() << "���� " << accountNumberTo->getAccountNum() << "���� ��ü�Ǿ����ϴ�." << endl;
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
                cout << "�ܾ��� �����մϴ�." << endl;
            }
            else {
                cout << "Not enough funds." << endl;
            }
        }
    }
    else if (accountNumberFrom->getPrimary(serialNumber) != accountNumberTo->getPrimary(serialNumber)) {
        if (serialNumber->getKR() == true) {
            cout << "��ü ������ : " << fee->getatFeeBetPNonp() << endl;
        }
        else {
            cout << "Transfer fee : " << fee->getatFeeBetPNonp() << endl;
        }
        int transferfee = fee->getatFeeBetPNonp();
        if (serialNumber->getKR() == true) {
            cout << "��ü�Ͻ� �ݾ��� �Է��Ͻʽÿ�. " << endl;
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
                cout << "���������� " << money << "���� ���¹�ȣ " << accountNumberFrom->getAccountNum() << "���� " << accountNumberTo->getAccountNum() << "���� ��ü�Ǿ����ϴ�." << endl;
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
                cout << "�ܾ��� �����մϴ�." << endl;
            }
            else {
                cout << "Not enough funds." << endl;
            }
        }
    }
    else {
        if (serialNumber->getKR() == true) {
            cout << "��ü ������ : " << fee->getatFeeBetNonp() << endl;
        }
        else {
            cout << "Transfer fee : " << fee->getatFeeBetNonp() << endl;
        }
        int transferfee = fee->getatFeeBetNonp();
        if (serialNumber->getKR() == true) {
            cout << "��ü�Ͻ� �ݾ��� �Է��Ͻʽÿ�. " << endl;
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
                cout << "���������� " << money << " ���� ���¹�ȣ " << accountNumberFrom->getAccountNum() << " ���� " << accountNumberTo->getAccountNum() << " ���� ��ü�Ͽ����ϴ�." << endl;
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
                cout << "�ܾ��� �����մϴ�." << endl;
            }
            else {
                cout << "Not enough funds." << endl;
            }
        }
    }
}