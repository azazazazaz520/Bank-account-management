#include <iostream>
#include "date.h"
#include <cstdlib>
using namespace std;
namespace {
	const int DAYS_BEFORE_MONTH[] = { 0,31,59,90, 120, 151, 181, 212, 243, 273, 304, 334, 365 };
}
Date::Date(int year, int month, int day)
{
	this->year = year;
	this->month = month;
	this->day = day;
	if (day <= 0 || day > getMaxDay())
	{
		cout << "Invalid date: ";
		show();
		cout << endl;
		exit(1);
	}
	else
	{
		int years = year - 1;
		totalDays = years * 365 + years / 4 - years / 100 + years / 400 + DAYS_BEFORE_MONTH[month - 1] + day;
	}
	if (isLeapyear() && month > 2)
	{
		totalDays++;
	}
}
int Date::getMaxDay() const
{
	if (isLeapyear() && month == 2)
	{
		return 29;
	}
	else
	{
		return DAYS_BEFORE_MONTH[month] - DAYS_BEFORE_MONTH[month - 1];
	}
}
void Date::show() const
{
	cout << getYear() << "-" << getMonth() << "-" << getDay();
}
    // 修改后的静态成员函数实现
    Date Date::read()
    {
        string date;
        cin >> date;
        int y = 0, m = 0, d = 0;
        regex date_regex(R"((\d+)/(\d+)/(\d+))");
        smatch match;
        if (std::regex_match(date, match, date_regex)) {
            y = std::stoi(match[1]);
            m = std::stoi(match[2]);
            d = std::stoi(match[3]);
        }
        Date to_date(y, m, d);
        return to_date;
    }

	