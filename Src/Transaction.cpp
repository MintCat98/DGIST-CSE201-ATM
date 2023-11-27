#include "Transaction.h"

Transaction::Transaction(ATM* serialNumber, Card* cardNumber, string type, Fee* fee) {

	// Transaction �������

	this->cardNum = cardNumber->getCardNum(); // Transaction�� cardnum�� ����
	this->transType = type;					  // Transtype�� ����
	this->transactionID = (100 * serialNumber->getSerialNum()) + serialNumber->getTransNum();
	// ���Ƿ� �ŷ� id�� ATM�� �ø��� �ѹ��� 100�� ���� ��, TransNum�� �����ش�.
	serialNumber->setTransNum(serialNumber->getTransNum() + 1);
	// �ŷ� ��ȣ�� 1 ���ؼ� ������ �д�.
	cout << "[Constructor]New transaction Created: (" << this->transactionID << ")";

	// deposit or withdrawal

	if (type == "deposit") {
		this->deposit(serialNumber,cardNumber, fee); // deposit�� type���� ������, deposit ����
	}
	else if (type == "withdrawal") {
		this->withdrawal(serialNumber,cardNumber, fee); // withdrawal�̸� withdrawal ���� 
	}
}

Transaction::~Transaction() {
	cout << "Transaction Destructor called" << endl; // Destructor
}

void Transaction::deposit(ATM* serialNumber, Card* cardNumber, Fee* fee) {

	// cash , check�� �Ǹ��Ѵ�. 

	cout << "Cash or Check?" << endl;
	string cashorcheck;
	cin >> cashorcheck;
	
	if (cashorcheck == "Cash" || cashorcheck == "cash") {
		this->addcash(serialNumber, cardNumber,fee);
	}
	else if (cashorcheck == "Check" || cashorcheck == "check") {
		this->addcheck(serialNumber, cardNumber,fee);
	}
}

void Transaction::addcash(ATM* serialNumber, Card* cardNumber, Fee* fee) {
	cout << "Please tell me how many bills you would like to put in each unit." << endl;
	cout << "KRW 1,000, KRW 5,000,KRW 10,000, KRW 50,000" << endl;
	// õ��, ��õ�� , ���� ,�������� �󸶸� ������ ����.
	int c, oc, m, om;
	cin >> c >> oc >> m >> om;
	int billamount = c + oc + m + om;
	int balanceadd = 1000 * c + 5000 * oc + 10000 * m + 50000 * om;


	int feemoney = 0; // ������ å��
	if (cardNumber->getPrimary() == true) {
		// primary�� ���� ��, ���س��Ҵ� fee�� �ҷ��´�.
		feemoney = fee->getdpFeePrim();
		cout << " The fee is " << feemoney << "won.Your card is primary." << endl;
	}
	else {
		// �ƴ� ��, fee�� �ҷ��´�.
		feemoney = fee->getdpFeeNonp();
		cout << " The fee is " << feemoney << "won.Your card is non - primary." << endl;
	}




	if (billamount > 50 || balanceadd < feemoney) {
		cout << " Error amount. " << endl; // �����Ẹ�� ���� ���̰ų�, billamount �ʰ�ġ�� �Ѿ ��� ���� ��ȯ.
	}
	else {
		
		cout << " Successfully deposited " << balanceadd << "on card number" << cardNumber->getCardNum() << endl;
		// card�� account �κ��� balance�� ��ü�Ѵ�. �̴� ���� �ܾ׿��� �߰� �ܾ��� ���ϰ�, �����Ḧ �� ���̴�.
		cardNumber->setbalance(cardNumber->getbalance() + balanceadd - feemoney);
		
		// �� ���󺰷� ������Ŵ.
		serialNumber->set1000won(serialNumber->get1000won() + c);
		serialNumber->set5000won(serialNumber->get5000won() + oc);
		serialNumber->set10000won(serialNumber->get10000won() + m);
		serialNumber->set50000won(serialNumber->get50000won() + om);
		serialNumber->setCashAmount(serialNumber->getCashAmount() + balanceadd);


		// transaction_history.txt�� ���� �߰���.
		ofstream history("transaction_history.txt");
		if(history.is_open()){
			history << "Transaction ID : " << this->transactionID << " Card Number : " << cardNumber->getCardNum() << " Transaction Type : " << this->transType << ", cash" << " Amount : " << balanceadd << "\n";
		}
		history.close();
	}
}

void Transaction::addcheck(ATM* serialNumber, Card* cardNumber, Fee* fee) {
	cout << "Please tell me how many checks. The limit is 10." << endl;
	int howmanychecks;
	cin >> howmanychecks;
	if (howmanychecks > 10) {
		cout << "Sorry." << endl;
	}
	else {
		int balanceadd = 0;
		for (int i = 0; i < howmanychecks; i++) {
			cout << "What value?" << endl;
			int value;
			cin >> value;
			balanceadd += value;
		}

		int feemoney = 0; // ������ å��
		if (cardNumber->getPrimary() == true) {
			// primary�� ���� ��, ���س��Ҵ� fee�� �ҷ��´�.
			feemoney = fee->getdpFeePrim();
			cout << " The fee is " << feemoney << "won.Your card is primary." << endl;
		}
		else {
			// �ƴ� ��, fee�� �ҷ��´�.
			feemoney = fee->getdpFeeNonp();
			cout << " The fee is " << feemoney << "won.Your card is non - primary." << endl;
		}


		cout << " Successfully deposited " << balanceadd << "on card number" << cardNumber->getCardNum() << endl;
		cardNumber->setbalance(cardNumber->getbalance() + balanceadd - feemoney);
		ofstream history("transaction_history.txt");
		if (history.is_open()) {
			history << "Transaction ID : " << this->transactionID << " Card Number : " << cardNumber->getCardNum() << " Transaction Type : " << this->transType<<", check" << " Amount : " << balanceadd << "\n";
		}
		history.close();
	}
}

void Transaction::withdrawal(ATM* serialNumber, Card* cardNumber, Fee* fee) {
	int i = 1;
	while (i < 4) {
		cout << "How much fund to withdraw?" << endl;
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
		serialNumber->set50000won(serialNumber->get50000won() - noteCount);
		amount -= 50000 * noteCount;
		// ���� ���Ž�
		noteCount = amount / 10000;
		if (noteCount > serialNumber->get10000won()) {
			noteCount = serialNumber->get10000won();
		}
		m = noteCount;
		serialNumber->set10000won(serialNumber->get10000won() - noteCount);
		amount -= 10000 * noteCount;
		// 5õ�� ���Ž�
		noteCount = amount / 5000;
		if (noteCount > serialNumber->get5000won()) {
			noteCount = serialNumber->get5000won();
		}
		oc= noteCount;
		serialNumber->set5000won(serialNumber->get5000won() - noteCount);
		amount -= 5000 * noteCount;
		// õ�� ���Ž�
		noteCount = amount / 1000;
		if (noteCount > serialNumber->get1000won()) {
			noteCount = serialNumber->get1000won();
		}
		c = noteCount;
		serialNumber->set1000won(serialNumber->get1000won() - noteCount);
		amount -= 1000 * noteCount;
		if (amount > 0) {
			canwithdrawal = false;
		}

		int feemoney = 0; // ������ å��
		if (cardNumber->getPrimary() == true) {
			// primary�� ���� ��, ���س��Ҵ� fee�� �ҷ��´�.
			feemoney = fee->getwdFeePrim();
			cout << " The fee is " << feemoney << "won.Your card is primary." << endl;
		}
		else {
			// �ƴ� ��, fee�� �ҷ��´�.
			feemoney = fee->getwdFeeNonp();
			cout << " The fee is " << feemoney << "won.Your card is non - primary." << endl;
		}

		if (withdrawamount + feemoney < cardNumber->getbalance()) {
			cout << "Sorry, you don't have enough money in your card." << endl;
		}
		else if (withdrawamount % 1000 != 0) {
			cout << "Please make the unit correctly." << endl;
		}
		else if (withdrawamount > serialNumber->getCashAmount() || canwithdrawal == false) {
			cout << "ATM Cash lack" << endl;
		}
		else {
			cout << "Here is your money. " << withdrawamount << " won." << endl;
			cout << "50000 bill -> " << om << " 10000 bill -> " << m << " 5000 bill -> " << oc << " 1000 bill -> " << c << endl;

			serialNumber->set1000won(serialNumber->get1000won() - c);
			serialNumber->set5000won(serialNumber->get5000won() - oc);
			serialNumber->set10000won(serialNumber->get10000won() - m);
			serialNumber->set50000won(serialNumber->get50000won() - om);
			serialNumber->setCashAmount(serialNumber->getCashAmount() - withdrawamount);
			cardNumber->setbalance(cardNumber->getbalance() - withdrawamount - feemoney);


			ofstream history("transaction_history.txt");
			if (history.is_open()) {
				history << "Transaction ID : " << this->transactionID << " Card Number : " << cardNumber->getCardNum() << " Transaction Type : " << this->transType << " Amount : " << withdrawamount << "\n";
			}
			history.close();
		}
		i++;
		
	}
	
}

Transaction::Transaction(ATM* serialNumber, Account* accountNumberTo, string type, Fee* fee) {

	// Transaction �������

	this->cardNum = cardNumber->getCardNum(); // Transaction�� cardnum�� ����
	this->transType = type;					  // Transtype�� ����
	this->transactionID = (100 * serialNumber->getSerialNum()) + serialNumber->getTransNum();
	// ���Ƿ� �ŷ� id�� ATM�� �ø��� �ѹ��� 100�� ���� ��, TransNum�� �����ش�.
	serialNumber->setTransNum(serialNumber->getTransNum() + 1);
	// �ŷ� ��ȣ�� 1 ���ؼ� ������ �д�.
	cout << "[Constructor]New transaction Created: (" << this->transactionID << ")";

	// cash transfer �Դϴ�.
	cout << "Please tell me how many bills you would like to put in each unit." << endl;
	cout << "KRW 1,000, KRW 5,000,KRW 10,000, KRW 50,000" << endl;
	int c, oc, m, om;
	cin >> c >> oc >> m >> om;
	int billamount = c + oc + m + om;
	int balanceadd = 1000 * c + 5000 * oc + 10000 * m + 50000 * om;



	if (billamount > 50 || fee->getctFeeAny() > balanceadd) {
		cout << " Error amount " << endl;
	}
	else {
		cout << " Successfully transfered " << balanceadd << "on account" << accountNumberTo->getAccountNum() << endl;
		accountNumberTo->setbalance(accountNumberTo->getbalance() + balanceadd - fee->getctFeeAny());

		serialNumber->set1000won(serialNumber->get1000won() + c);
		serialNumber->set5000won(serialNumber->get5000won() + oc);
		serialNumber->set10000won(serialNumber->get10000won() + m);
		serialNumber->set50000won(serialNumber->get50000won() + om);
		serialNumber->setCashAmount(serialNumber->getCashAmount() + balanceadd);

		ofstream history("transaction_history.txt");
		if (history.is_open()) {
			history << "Transaction ID : " << this->transactionID << " Card Number : " << accountNumberTo->getAccountNum() << " Transaction Type : " << this->transType << ", cash" << " Amount : " << balanceadd << "\n";
		}
		history.close();
	}
}

Transaction::Transaction(ATM* serialNumber, Account* accountNumberFrom, Account* accountNumberTo, string type, Fee* fee) {

	// Transaction �������

	this->cardNum = cardNumber->getCardNum(); // Transaction�� cardnum�� ����
	this->transType = type;					  // Transtype�� ����
	this->transactionID = (100 * serialNumber->getSerialNum()) + serialNumber->getTransNum();
	// ���Ƿ� �ŷ� id�� ATM�� �ø��� �ѹ��� 100�� ���� ��, TransNum�� �����ش�.
	serialNumber->setTransNum(serialNumber->getTransNum() + 1);
	// �ŷ� ��ȣ�� 1 ���ؼ� ������ �д�.
	cout << "[Constructor]New transaction Created: (" << this->transactionID << ")";

	// transfer �Դϴ�.
	if (accountNumberFrom->getPrimary() == true && accountNumberTo->getPrimary() == true) {
		cout << "Transfer fee :" << fee->getatFeeBetPrim() << endl;
		if (accountNumberFrom->getbalance() > fee->getatFeeBetPrim()) {
			accountNumberFrom->setbalance(accountNumberFrom->getbalance() - fee->getatFeeBetPrim());
			cout << " how much money? " << endl;
			int money;
			cin >> money;
			if (accountNumberFrom->getbalance() >= money) {
				accountNumberFrom->setbalance(accountNumberFrom->getbalance() - money);
				accountNumberTo->setbalance(accountNumberTo->getbalance() - money);
				ofstream history("transaction_history.txt");
				if (history.is_open()) {
					history << "Transaction ID : " << this->transactionID << "Transfer from" << accountNumberFrom->getAccountNum() << "Transfer to" << accountNumberTo->getAccountNum() << "amount" << money;
				history.close();
			}
			else {
				cout << "Not enough money." << endl;
			}
		}
		else {
			cout << " Not enough money." << endl;
		}
	}
		else if (accountNumberFrom->getPrimary() != accountNumberTo->getPrimary()) {
			cout << "Transfer fee : "<< fee->getatFeeBetPNonp() << endl;
			if (accountNumberFrom->getbalance() > fee->getatFeeBetPNonp()) {
				accountNumberFrom->setbalance(accountNumberFrom->getbalance() - fee->getatFeeBetPNonp());
				cout << " how much money? " << endl;
				int money;
				cin >> money;
				if (accountNumberFrom->getbalance() >= money) {
					accountNumberFrom->setbalance(accountNumberFrom->getbalance() - money);
					accountNumberTo->setbalance(accountNumberTo->getbalance() - money);
					ofstream history("transaction_history.txt");
					if (history.is_open()) {
						history << "Transaction ID : " << this->transactionID << "Transfer from" << accountNumberFrom->getAccountNum() << "Transfer to" << accountNumberTo->getAccountNum() << "amount" << money;
						history.close();
					}
					else {
						cout << "Not enough money." << endl;
					}
				}

				else {
					cout << " Not enough money." << endl;
				}
			}
			else {
				cout << "Transfer fee : " << fee->getafFeeBetNonp() << endl;
				if (accountNumberFrom->getbalance() > fee->getafFeeBetNonp()) {
					accountNumberFrom->setbalance(accountNumberFrom->getbalance() - fee->getafFeeBetNonp());
					cout << " how much money? " << endl;
					int money;
					cin >> money;
					if (accountNumberFrom->getbalance() >= money) {
						accountNumberFrom->setbalance(accountNumberFrom->getbalance() - money);
						accountNumberTo->setbalance(accountNumberTo->getbalance() - money);
						ofstream history("transaction_history.txt");
						if (history.is_open()) {
							history << "Transaction ID : " << this->transactionID << "Transfer from" << accountNumberFrom->getAccountNum() << "Transfer to" << accountNumberTo->getAccountNum() << "amount" << money;
							history.close();
						}
						else {
							cout << "Not enough money." << endl;
						}
					}
					else {
						cout << " Not enough money." << endl;
					}
				}
			}
		}
