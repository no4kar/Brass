#pragma once
// brass.h -- классы банковских счетов
#ifndef BRASS_Н 
#define BRASS_Н

class Acct {
	enum { MAX = 35 };
	char fullName[MAX];
	long acctNum;
	double bal;
protected:
	const char* get_full_name()const { return fullName; }
	long get_acct_num()const { return acctNum; }
	std::ios_base::fmtflags save_format()const;
public:
	Acct(const char* s = "nullbody", long acctNum = -1, double balance = 0.0);
	void deposit(double amt);
	virtual void withdraw(double amt) { bal -= amt; };
	double get_balance()const { return bal; }
	virtual void view_account()const = 0;

	virtual ~Acct() {
	}
};

class Brass :public Acct {
public:
	Brass(const char* s = "nullbody", long acctNum = -1, double balance = 0.0) :
		Acct(s, acctNum, balance) {};
	void withdraw(double amt)override;
	void view_account()const override;
	
	~Brass()override {
	}
};

class BrassPlus :public Acct {
	double maxLoan;
	double rate;
	double owesBank;
public:
	BrassPlus(const char* s = "nullbody", long an = -1, double bal = 0.0,
		double ml = 500, double r = 0.1);
	BrassPlus(const Acct& ba, double ml = 500, double r = 0.1);
	void view_account()const override;
	void withdraw(double amt)override;
	void reset_max(double maxLoan) { this->maxLoan = maxLoan; }
	void reset_rate(double rate) { this->rate = rate; }
	void reset_owes() { owesBank = 0; }

	~BrassPlus()override {
	}
};

#endif