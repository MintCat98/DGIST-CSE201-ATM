#include "Transaction.h"

Transaction::Transaction(ATM* serialNumber, Card* cardNumber, string type, Fee* fee) {

	// Transaction 공통사항

	this->cardNum = cardNumber->getCardNum(); // Transaction의 cardnum을 지정
	this->transType = type;					  // Transtype을 지정
	this->transactionID = (100 * serialNumber->getSerialNum()) + serialNumber->getTransNum();
	// 임의로 거래 id를 ATM의 시리얼 넘버에 100을 곱한 후, TransNum을 더해준다.
	serialNumber->setTransNum(serialNumber->getTransNum() + 1);
	// 거래 번호를 1 더해서 저장해 둔다.
	cout << "[Constructor]New transaction Created: (" << this->transactionID << ")";

	// deposit or withdrawal

	if (type == "deposit") {
		this->deposit(serialNumber,cardNumber, fee); // deposit을 type으로 받으면, deposit 실행
	}
	else if (type == "withdrawal") {
		this->withdrawal(serialNumber,cardNumber, fee); // withdrawal이면 withdrawal 실행 
	}
}

Transaction::~Transaction() {
	cout << "Transaction Destructor called" << endl; // Destructor
}

void Transaction::deposit(ATM* serialNumber, Card* cardNumber, Fee* fee) {

	// cash , check를 판명한다. 

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
	// 천원, 오천원 , 만원 ,오만원권 얼마를 넣을지 고른다.
	int c, oc, m, om;
	cin >> c >> oc >> m >> om;
	int billamount = c + oc + m + om;
	int balanceadd = 1000 * c + 5000 * oc + 10000 * m + 50000 * om;


	int feemoney = 0; // 수수료 책정
	if (cardNumber->getPrimary() == true) {
		// primary가 맞을 때, 정해놓았던 fee를 불러온다.
		feemoney = fee->getdpFeePrim();
		cout << " The fee is " << feemoney << "won.Your card is primary." << endl;
	}
	else {
		// 아닐 때, fee를 불러온다.
		feemoney = fee->getdpFeeNonp();
		cout << " The fee is " << feemoney << "won.Your card is non - primary." << endl;
	}




	if (billamount > 50 || balanceadd < feemoney) {
		cout << " Error amount. " << endl; // 수수료보다 작은 값이거나, billamount 초과치를 넘어설 경우 오류 반환.
	}
	else {
		
		cout << " Successfully deposited " << balanceadd << "on card number" << cardNumber->getCardNum() << endl;
		// card의 account 부분의 balance를 교체한다. 이는 기존 잔액에서 추가 잔액을 더하고, 수수료를 뺀 값이다.
		cardNumber->setbalance(cardNumber->getbalance() + balanceadd - feemoney);
		
		// 각 지폐별로 증가시킴.
		serialNumber->set1000won(serialNumber->get1000won() + c);
		serialNumber->set5000won(serialNumber->get5000won() + oc);
		serialNumber->set10000won(serialNumber->get10000won() + m);
		serialNumber->set50000won(serialNumber->get50000won() + om);
		serialNumber->setCashAmount(serialNumber->getCashAmount() + balanceadd);


		// transaction_history.txt에 점차 추가함.
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

		int feemoney = 0; // 수수료 책정
		if (cardNumber->getPrimary() == true) {
			// primary가 맞을 때, 정해놓았던 fee를 불러온다.
			feemoney = fee->getdpFeePrim();
			cout << " The fee is " << feemoney << "won.Your card is primary." << endl;
		}
		else {
			// 아닐 때, fee를 불러온다.
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
		// 5만원 제거식
		int noteCount = amount / 50000;
		if (noteCount > serialNumber->get50000won()) {
			noteCount = serialNumber->get50000won();
		}
		om = noteCount;
		serialNumber->set50000won(serialNumber->get50000won() - noteCount);
		amount -= 50000 * noteCount;
		// 만원 제거식
		noteCount = amount / 10000;
		if (noteCount > serialNumber->get10000won()) {
			noteCount = serialNumber->get10000won();
		}
		m = noteCount;
		serialNumber->set10000won(serialNumber->get10000won() - noteCount);
		amount -= 10000 * noteCount;
		// 5천원 제거식
		noteCount = amount / 5000;
		if (noteCount > serialNumber->get5000won()) {
			noteCount = serialNumber->get5000won();
		}
		oc= noteCount;
		serialNumber->set5000won(serialNumber->get5000won() - noteCount);
		amount -= 5000 * noteCount;
		// 천원 제거식
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

		int feemoney = 0; // 수수료 책정
		if (cardNumber->getPrimary() == true) {
			// primary가 맞을 때, 정해놓았던 fee를 불러온다.
			feemoney = fee->getwdFeePrim();
			cout << " The fee is " << feemoney << "won.Your card is primary." << endl;
		}
		else {
			// 아닐 때, fee를 불러온다.
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

	// Transaction 공통사항

	this->cardNum = cardNumber->getCardNum(); // Transaction의 cardnum을 지정
	this->transType = type;					  // Transtype을 지정
	this->transactionID = (100 * serialNumber->getSerialNum()) + serialNumber->getTransNum();
	// 임의로 거래 id를 ATM의 시리얼 넘버에 100을 곱한 후, TransNum을 더해준다.
	serialNumber->setTransNum(serialNumber->getTransNum() + 1);
	// 거래 번호를 1 더해서 저장해 둔다.
	cout << "[Constructor]New transaction Created: (" << this->transactionID << ")";

	// cash transfer 입니다.
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

	// Transaction 공통사항

	this->cardNum = cardNumber->getCardNum(); // Transaction의 cardnum을 지정
	this->transType = type;					  // Transtype을 지정
	this->transactionID = (100 * serialNumber->getSerialNum()) + serialNumber->getTransNum();
	// 임의로 거래 id를 ATM의 시리얼 넘버에 100을 곱한 후, TransNum을 더해준다.
	serialNumber->setTransNum(serialNumber->getTransNum() + 1);
	// 거래 번호를 1 더해서 저장해 둔다.
	cout << "[Constructor]New transaction Created: (" << this->transactionID << ")";

	// transfer 입니다.
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
