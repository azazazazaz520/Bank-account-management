#pragma once
#include "account.h"
#include "date.h"
#include <iostream>
class AccountRecord
{
private:
	Date date;
	//const Account *account;
	double amount;
	double balance;
	std::string desc;

public:
	//AccountRecord(const Date& date, double amount, double balance, const std::string& desc):date(date),
		///amount(amount),balance(balance),desc(desc)
	//{	}
};

