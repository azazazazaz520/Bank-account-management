#ifndef __ACCUMULATOR_H__
#define __ACCUMULATOR_H__

#include <iostream>
#include "date.h"
class Accumulator {
private:
	Date lastdate;
	double value;          //当前数值
	double sum;            //当前的和
public:
	Accumulator(const Date &date, double value):lastdate(date),value(value),sum(0){}
	double getSum(const Date &date) const {
		return sum + value * (date - lastdate);
	}
	void change(const Date &date, double value)
	{
		sum = getSum(date);
		lastdate = date;
		this->value = value;
	}
	void reset(const Date &date, double value)
	{
		lastdate = date;
		this->value = value;
		sum = 0;
	}
};
#endif