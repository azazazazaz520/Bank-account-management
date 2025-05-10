#ifndef __ACCUMULATOR_H__
#define __ACCUMULATOR_H__

#include <iostream>
#include "date.h"
class Accumulator {
private:
	Date lastdate;
	double value;          //��ǰ��ֵ
	double sum;            //��ǰ�ĺ�
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