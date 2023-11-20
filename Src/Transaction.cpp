#include "Transaction.h"

Transaction::Transaction(ATM* serialNumber, Card* cardNumber, string type) {
	this->cardNum = cardNumber->getCardNum();
	this->transType = type;
	this->transactionID = (10 * serialNumber->getTransNum()) + serialNumber->getSerialNum();
	serialNumber->setTransNum(serialNumber->getTransNum() + 1);
	cout << "[Constructor]New transaction Created: (" << this->transactionID << ")";
	if (type == "deposit") {
		this->deposit(serialNumber,cardNumber);
	}
	else if (type == "withdrawal") {
		this->withdrawal(serialNumber,cardNumber);
	}
}

Transaction::~Transaction() {
	cout << "Transaction Destructor called" << endl;
}

void Transaction::deposit(ATM* serialNumber, Card* cardNumber) {
	cout << "Cash or Check?" << endl;
	string cashorcheck;
	cin >> cashorcheck;
	if (cardNumber->getPrimary() == true) {
		cout << " Your card is primary. " << endl;
	}
	else {
		cout << " Please put 1000 won. Your card is non-primary." << endl;

	}
	if (cashorcheck == "Cash" || cashorcheck == "cash") {
		this->addcash(serialNumber, cardNumber);
	}
	else if (cashorcheck == "Check" || cashorcheck == "check") {
		this->addcheck(serialNumber, cardNumber);
	}
}

void Transaction::addcash(ATM* serialNumber, Card* cardNumber) {
	cout << "Please tell me how many bills you would like to put in each unit." << endl;
	cout << "KRW 1,000, KRW 5,000,KRW 10,000, KRW 50,000" << endl;
	int c, oc, m, om;
	cin >> c >> oc >> m >> om;
	int billamount = c + oc + m + om;
	int balanceadd = 1000 * c + 5000 * oc + 10000 * m + 50000 * om;
	if (billamount > 50) {
		cout << " Error amount " << endl;
	}
	else {
		cout << " Successfully deposited " << balanceadd << "on card number" << cardNumber->getCardNum() << endl;
		cardNumber->setbalance(cardNumber->getbalance() + balanceadd);
		serialNumber->setCashAmount(serialNumber->getCashAmount() + balanceadd);
		ofstream history("transaction_history.txt");
		if(history.is_open()){
			history << "Transaction ID : " << this->transactionID << " Card Number : " << cardNumber->getCardNum() << " Transaction Type : " << this->transType << ", cash" << " Amount : " << balanceadd << "\n";
		}
		history.close();
	}
}

void Transaction::addcheck(ATM* serialNumber, Card* cardNumber) {
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
		cout << " Successfully deposited " << balanceadd << "on card number" << cardNumber->getCardNum() << endl;
		cardNumber->setbalance(cardNumber->getbalance() + balanceadd);
		ofstream history("transaction_history.txt");
		if (history.is_open()) {
			history << "Transaction ID : " << this->transactionID << " Card Number : " << cardNumber->getCardNum() << " Transaction Type : " << this->transType<<", check" << " Amount : " << balanceadd << "\n";
		}
		history.close();
	}
}

void Transaction::withdrawal(ATM* serialNumber, Card* cardNumber) {
	int i = 1;
	while (i < 4) {
		cout << "How much fund to withdraw?" << endl;
		int withdrawamount = 0;
		cin >> withdrawamount;
		if (cardNumber->getPrimary() == true) {
			cout << " Your card is primary. " << endl;
			if (withdrawamount+1000 < cardNumber->getbalance()) {
				cout << "Sorry, you don't have enough money in your card." << endl;
			}
			else if (withdrawamount % 1000 != 0) {
				cout << "Please make the unit correctly." << endl;
			}
			else if (withdrawamount > serialNumber->getCashAmount()) {
				cout << "ATM Cash lack" << endl;
			}
			else {
				cout << "Here is your money. " << withdrawamount << " won." << endl;

				serialNumber->setCashAmount(serialNumber->getCashAmount() - withdrawamount);
				cardNumber->setbalance(cardNumber->getbalance() - withdrawamount-1000);
				ofstream history("transaction_history.txt");
				if (history.is_open()) {
					history << "Transaction ID : " << this->transactionID << " Card Number : " << cardNumber->getCardNum() << " Transaction Type : " << this->transType << " Amount : " << withdrawamount << "\n";
				}
				history.close();
			}
		}
		else {
			cout << " Please put 1000 won. Your card is non-primary." << endl;
			if (withdrawamount+2000 < cardNumber->getbalance()) {
				cout << "Sorry, you don't have enough money in your card." << endl;
			}
			else if (withdrawamount % 1000 != 0) {
				cout << "Please make the unit correctly." << endl;
			}
			else if (withdrawamount > serialNumber->getCashAmount()) {
				cout << "ATM Cash lack" << endl;
			}
			else {
				cout << "Here is your money. " << withdrawamount << " won." << endl;

				serialNumber->setCashAmount(serialNumber->getCashAmount() - withdrawamount);
				cardNumber->setbalance(cardNumber->getbalance() - withdrawamount-2000);
				ofstream history("transaction_history.txt");
				if (history.is_open()) {
					history << "Transaction ID : " << this->transactionID << " Card Number : " << cardNumber->getCardNum() << " Transaction Type : " << this->transType << " Amount : " << withdrawamount << "\n";
				}
				history.close();
			}

		}
		
	}
	
}

void Transaction::cashtransfer(ATM* serialNumber, Account* accountNumberTo) {
	cout << "Please put 5000 won." << endl;
	cout << "where?" << endl;
	cout << "Please tell me how many bills you would like to put in each unit." << endl;
	cout << "KRW 1,000, KRW 5,000,KRW 10,000, KRW 50,000" << endl;
	int c, oc, m, om;
	cin >> c >> oc >> m >> om;
	int billamount = c + oc + m + om;
	int balanceadd = 1000 * c + 5000 * oc + 10000 * m + 50000 * om;
	if (billamount > 50) {
		cout << " Error amount " << endl;
	}
	else {
		cout << " Successfully transfered " << balanceadd << "on account" << accountNumberTo->getAccountNum() << endl;
		accountNumberTo->setbalance(accountNumberTo->getbalance() + balanceadd);
		serialNumber->setCashAmount(serialNumber->getCashAmount() + balanceadd);
		ofstream history("transaction_history.txt");
		if (history.is_open()) {
			history << "Transaction ID : " << this->transactionID << " Card Number : " << accountNumberTo->getAccountNum() << " Transaction Type : " << this->transType << ", cash" << " Amount : " << balanceadd << "\n";
		}
		history.close();
	}
}

void Transaction::transfer(ATM* serialNumber, Account* accountNumberFrom, Account* accountNumberTo) {

}