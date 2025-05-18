#include "account.h"
#include <iostream>
#include <cmath>
#include <string>
using namespace std;
double Account::total = 0;
std::multimap<Date, AccountRecord> Account::recordMap;
Account::Account(const Date &date,const string &id):id(id),balance(0)
{
	date.show();
	cout << "\t#" << id << " created" << endl;
}
void Account::error(const std::string& msg) const {
	std::cout << "Error(#" << id << "): " << msg << endl;
}
void Account::record(const Date& date, double amount, const std::string& desc)
{
	amount = floor(amount * 100 + 0.5) / 100;         //保留小数点后两位
	balance += amount;
	total += amount;
	date.show();
	std::cout << "\t#" << id << "\t" << amount << "\t" << balance << "\t" << desc << endl;
	AccountRecord value(date, amount, balance, desc);
	recordMap.insert({date, value});
}

void Account::show() const
{
	std::cout << id << "\tBalance: " << balance;
}

void Account::query(const Date& date1,const Date& date2)  
{  
   if (date1 < date2)  
   {  
       auto find_start = recordMap.lower_bound(date1);  
       auto find_end = recordMap.upper_bound(date2);  
       for (auto& it = find_start; it != find_end; ++it)  
       {  
           AccountRecord ac = it->second;    
           ac.date.show(); // Example usage  
           std::cout << "\t" << ac.amount << "\t" << ac.balance << "\t" << ac.desc << std::endl;  
       }  
   }  
}

/***********************************************************************************************************/
SavingsAccount::SavingsAccount(const Date& date, const std::string& id, double rate)
	:Account(date,id),rate(rate),Acc(date,0)
{

}

void SavingsAccount::deposit(const Date& date, double amount, const std::string& desc)
{
	record(date, amount, desc);
	Acc.change(date, getBalance());

}

void SavingsAccount::withdraw(const Date& date, double amount, const std::string& desc)
{
	if (amount > getBalance())
	{
		error("not enough money");
	}
	else
	{
		record(date, -amount, desc);
		Acc.change(date, getBalance());

	}
}

void SavingsAccount::settle(const Date & date)
{
	if (date.getMonth() == 1) {	//每年的一月计算一次利息
		double interest = Acc.getSum(date) * rate
			/ (date - Date(date.getYear() - 1, 1, 1));
		if (interest != 0)
			record(date, interest, "interest");
		Acc.reset(date, getBalance());
	}

	


}

/******************************************************************************************************/
CreditAccount::CreditAccount(const Date& date, const std::string& id, double credit, double rate,double fee)
	:Account(date,id),Acc(date,0),
credit(credit),fee(fee),rate(rate)
{
	
}

void CreditAccount::deposit(const Date& date, double amount, const std::string& desc)	//存款
{
	record(date, amount, desc);
	Acc.change(date, getDebt());
}

void CreditAccount::withdraw(const Date& date, double amount, const std::string& desc)
{
	if (amount - getBalance() > credit)
	{
		error("not enough credit");
	}
	else
	{
		record(date, -amount, desc);
		Acc.change(date, getDebt());
	}
}

void CreditAccount::settle(const Date& date)             //结算利息
{
	double interest = Acc.getSum(date) * rate;
	if (interest != 0)
		record(date, interest, "interest");
	if (date.getMonth() == 1)            //该交年费了
		record(date, -fee, "annual fee");
	Acc.reset(date, getDebt());
}

void CreditAccount::show()const
{
	Account::show();
	cout << "\tAvailable credit:" << getAvailableCredit();
}