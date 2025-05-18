#ifndef DATE_H
#define DATE_H
#include <regex>

class Date {
private:
	int year;
	int month;
	int day;
	int totalDays;     //当前日期到公元元年的天数
public:
	Date(){

	}
	Date(int year, int month, int day);
	bool isLeapyear() const            //判断闰年
	{
		return year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
	}
	int getMaxDay() const;       //输出当前月有多少天
	void show() const;          //输出当前日期
	int getYear() const { return year; }         //获取年
	int getMonth() const { return month; }    //获取月
	int getDay() const { return day; }     //获取天
	int operator - (const Date& date) const {
		return totalDays - date.totalDays;
	}
	bool operator < (const Date& date) const {
		if (year != date.year) return year < date.year;
		if (month != date.month) return month < date.month;
		return day < date.day;
		
	}
	static Date read();
};
#endif // DATE_H
