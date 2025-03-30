#ifndef __ACCOUNT_H__
#define __ACCOUNT_H__
#include "date.h"
#include <string>
class SavingsAccount {
private:
	std::string id;              //用户id 
	double balance;      //余额   
	double rate;         //年利率 
	Date lastDate;
	double accumulation;    //存储上次计算利息以后直到最近一次余额变动时余额按日累加的值
	static double total;    //所有用户的总钱数
public:
	//SavingsAccount();
	SavingsAccount(const Date& date, const std::string& id, double rate);
	void error(const std::string& msg) const;
	void record(const Date & date, double amount, const std::string& desc);
	double accumulate(const Date& date) const;     //计算截至指定日期的账户余额按日累积值
	std::string getId() const;
	double getBalance() const;
	double getRate() const;
	static double getTotal() { return total; }
	void show() const;   //显示账户信息
	void deposit(const Date & date, double amount,const std::string &desc);  //存款
	void withdraw(const Date & date, double amount, const std::string& desc);    //取款
	void settle(const Date & date);          //结算利息


};
#endif
