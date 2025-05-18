#ifndef __ACCOUNT_H__
#define __ACCOUNT_H__
#include "date.h"
#include <string>
#include "Accumulator.h"
#include "AccountRecord.h"
#include <map>
class Account {
private:
	std::string id;
	double balance;      //余额
	static double total;        //所有账户的总金额
protected:
	Account(const Date &date, const std::string &id);
	void record(const Date &date, double amount, const std::string& desc);
	void error(const std::string& msg)const;
	static std::multimap<Date, AccountRecord> recordMap;
public:
	
	double getBalance()const { return balance; }
	const std::string getId(const std::string& id)const { return id; }
	static double getTotal() { return total; }
	static void query(const Date& date1,const Date& date2);         //查询一段日期之间的账目
	//存入现金，date为日期，amount为金额，desc为款项说明
	virtual void deposit(const Date& date, double amount, const std::string& desc) = 0;
	//取出
	virtual void withdraw(const Date& date, double amount, const std::string& desc) = 0;
	//结算（计算利息、年费等），每月结算一次，date为结算日期
	virtual void settle(const Date& date) = 0;
	//显示账户信息
	virtual void show() const;

};

/**************************************************************************************************/

class SavingsAccount : public Account {
private:
	Accumulator Acc;       //累加器
	double rate;         //年利率 
public:
	
	SavingsAccount(const Date& date, const std::string& id, double rate);
	double getRate() const { return rate; }
	virtual void deposit(const Date& date, double amount, const std::string& desc);  //存款
	virtual void withdraw(const Date& date, double amount, const std::string& desc);    //取款
	virtual void settle(const Date& date);          //结算利息,每年1月1日调用


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
	CreditAccount(const Date &date, const std::string& id,double credit,double rate,double fee);
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
	virtual void deposit(const Date& date, double amount, const std::string& desc);
	virtual void withdraw(const Date& date, double amount, const std::string& desc);
	virtual void settle(const Date &date);
	virtual void show()const;

};

#endif
