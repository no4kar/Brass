#include<iostream>
//#include<string>
#include"string.h"
#include"acct.h"

////////////////////////////////////////////Acct//////////////////////////////

std::ios_base::fmtflags Acct::save_format() const {
	//set format ###.##
	return std::cout.setf(std::ios_base::fixed, std::ios_base::floatfield);
}

Acct::Acct(const char* s, long acctNum, double bal) {
	strncpy_s(fullName, s, MAX - 1);
	fullName[MAX - 1] = '\0';
	this->acctNum = acctNum;
	this->bal = bal;
}

void Acct::deposit(double amt) {
	if (amt < 0) {
		std::cout << "\tNegative contribution is not allowed\n" <<
			"\tAttempt to contribution was canceled\n";
	}
	else {
		bal += amt;
	}
}

////////////////////////////////////////////Brass//////////////////////////////

void Brass::view_account()const {
	auto initialState = Acct::save_format();
	std::cout.setf(std::ios_base::showpoint);
	std::cout.precision(2);
	std::cout << "The Brass client: " << get_full_name() << std::endl;
	std::cout << "Account number: " << get_acct_num() << std::endl;
	std::cout << "Balance: " << get_balance() << std::endl;
	std::cout.setf(initialState);//set source(origin) format
}

void Brass::withdraw(double amt) {
	if (amt < 0) {
		std::cout << "\tThe withdrawal amount must be positive\n" <<
			"\tAttempt to withdraw was canceled\n";
	}
	else if (amt <= get_balance()) {
		Acct::withdraw(amt);
	}
	else {
		std::cout << "\tThe withdrawal amount " << amt <<
			" is greater than your balance\n" <<
			"\tAttempt to withdraw was canceled\n";
	}
}

////////////////////////////////////////////BrassPlus//////////////////////////////

BrassPlus::BrassPlus(const char* s, long acctNum, double bal, double maxLoan, double rate) :
	Acct(s, acctNum, bal) {
	this->maxLoan = maxLoan;
	owesBank = 0.0;
	this->rate = rate;
}

BrassPlus::BrassPlus(const Acct& obj,	double maxLoan, double rate) :
	Acct(obj) {//using not obvious constructor of coping 
	this->maxLoan = maxLoan;
	owesBank = 0.0;
	this->rate = rate;
}

void BrassPlus::view_account()const {
	//set format ###.##
	auto initialState = Acct::save_format(); 
	std::cout.setf(std::ios_base::showpoint);
	std::cout.precision(2);
	std::cout << "The BrassPlus client: " << get_full_name() << std::endl;
	std::cout << "Account number: " << get_acct_num() << std::endl;
	std::cout << "Balance: " << get_balance() << std::endl;
	std::cout << "Maximal loan: $" << maxLoan << std::endl;
	std::cout << "Owes of bank: $" << owesBank << std::endl;
	std::cout << "Percent on loan: " << 100 * rate << "%" << std::endl;
	std::cout.setf(initialState);//set source(origin) format
}

void BrassPlus::withdraw(double amt) {
	//set format ###.##
	std::ios_base::fmtflags initialState =
		std::cout.setf(std::ios_base::fixed, std::ios_base::floatfield);
	std::cout.setf(std::ios_base::showpoint);
	std::cout.precision(2);
	if (amt < get_balance()) {
		Acct::withdraw(amt);
	}
	else if (amt <= get_balance() + maxLoan - owesBank) {
		double advance = amt - get_balance();
		owesBank += advance * (1.0 + rate);
		std::cout << "Advance from bank: $" << advance << std::endl;
		std::cout << "Taxes: $" << advance * rate << std::endl;
		deposit(advance);
		Acct::withdraw(amt);
	}
	else {
		std::cout << "\tLimit of credit was exceeded\n" <<
			"\tAttempt to withdraw was canceled\n";
	}
	std::cout.setf(initialState);//set source(origin) format
}