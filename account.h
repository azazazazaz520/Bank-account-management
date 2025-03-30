#ifndef __ACCOUNT_H__
#define __ACCOUNT_H__
#include "date.h"
#include <string>
#include "Accumulator.h"
class Account {
private:
	std::string id;
	double balance;      //余额
	static double total;        //所有账户的总金额
protected:
	Account(const Date &date, const std::string &id);
	void record(const Date &date, double amount, const std::string& desc);
	void error(const std::string& msg)const;
	
public:
	void show() const;
	double getBalance()const { return balance; }
	const std::string getId(const std::string& id)const { return id; }
	static double getTotal() { return total; }
};

/**************************************************************************************************/

class SavingsAccount : public Account {
private:
	Accumulator Acc;       //累加器
	double rate;         //年利率 
public:
	
	SavingsAccount(const Date& date, const std::string& id, double rate);
	double getRate() const { return rate; }
	void deposit(const Date& date, double amount, const std::string& desc);  //存款
	void withdraw(const Date& date, double amount, const std::string& desc);    //取款
	void settle(const Date& date);          //结算利息


};


/**************************************************************************************************/




class CreditAccount :public Account {
private:
	Accumulator Acc;       //累加器
	double credit;         //信用额度
	double rate;		   //欠款日利率
	double fee;				//信用卡的年费
	double getDebt() const {	//获得欠款额
		double balance = getBalance();
		return (balance < 0 ? balance : 0);
	}
public:
	CreditAccount(const Date &date, const std::string& id,double credit,double fee, double rate);
	double getCredit()const { return credit; }
	double gatRate() const { return rate; }
	double getFee() const { return fee; }
	double getAvailableCredit()const {                //获取可用信用额度
		if (getBalance() < 0)
		{
			return credit + getBalance();
		}
		else {
			return credit;
		}
	}
	void deposit(const Date& date, double amount, const std::string& desc);
	void withdraw(const Date& date, double amount, const std::string& desc);
	void settle(const Date &date);
	void show()const;

};

#endif
