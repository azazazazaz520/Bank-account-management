#include "account.h"
#include <iostream>
#include <cmath>
#include <string>
using namespace std;
double SavingsAccount::total = 0;
SavingsAccount::SavingsAccount(const Date& date, const std::string& id, double rate):lastDate(date), id(id), rate(rate), balance(0), accumulation(0)
{
	date.show();
	cout << "\t#" << id << " created" << endl;
}
void SavingsAccount::error(const std::string& msg) const {
	cout << "Error(#" << id << "): " << msg << endl;
}

void SavingsAccount::deposit(const Date& date,double amount, const std::string& desc)
{
	record(date, amount,desc);
}
void SavingsAccount::withdraw(const Date& date, double amount, const std::string& desc)
{
	if (amount > getBalance())
	{
		error("not enough money");
	}
	else
	{
		record(date, -amount,desc);
	}
}
void SavingsAccount::record(const Date& date, double amount,const std::string &desc)
{
	accumulation = accumulate(date);
	lastDate = date;
	amount = floor(amount * 100 + 0.5) / 100;         //保留小数点后两位
	balance += amount;
	total += amount;
	this->lastDate.show();
	cout << "\t#" << id << "\t" << amount << "\t" << balance << "\t" << desc << endl;
}
double SavingsAccount::accumulate(const Date & date) const 
{
	return accumulation + balance * date.distance(lastDate);
}
string SavingsAccount::getId() const
{
	return id;
}
double SavingsAccount::getBalance() const
{
	return balance;
}
double SavingsAccount::getRate() const
{
	return rate;
}
void SavingsAccount::show() const
{
	cout << id << "\tBalance: " << balance;
}
void SavingsAccount::settle(const Date& date)
{
	double money = accumulate(date) * rate / date.distance(Date(date.getYear()-1,1,1));
	/*if (money != 0)*/
	/*{*/
		record(date, money,"interest");
	/*}*/
	accumulation = 0;
}
