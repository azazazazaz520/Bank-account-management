#pragma once
#include "account.h"
#include "date.h"
#include <iostream>
class AccountRecord
{
public:
	Date date;
	//const Account *account;
	double amount;
	double balance;
	std::string desc;


	AccountRecord(Date date, double amount, double balance, const std::string& desc)
		:date(date), amount(amount), balance(balance), desc(desc)
	{
		}
};

