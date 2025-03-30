class Date {
private:
	int year;
	int month;
	int day;
	int totalDays;     //当前日期到公元元年的天数
public:
	//Date();
	Date(int year, int month, int day);
	bool isLeapyear() const
	{
		return year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
	}
	int getMaxDay() const;
	void show() const;
	int getYear() const { return year; }
	int getMonth() const { return month; }
	int getDay() const { return day; }
	int distance(const Date & date) const
	{
		return totalDays - date.totalDays;
	}
};
