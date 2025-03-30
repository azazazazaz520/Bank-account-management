#ifndef DATE_H
#define DATE_H
class Date {
private:
	int year;
	int month;
	int day;
	int totalDays;     //��ǰ���ڵ���ԪԪ�������
public:
	Date(int year, int month, int day);
	bool isLeapyear() const            //�ж�����
	{
		return year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
	}
	int getMaxDay() const;
	void show() const;
	int getYear() const { return year; }         //��ȡ��
	int getMonth() const { return month; }    //��ȡ��
	int getDay() const { return day; }     //��ȡ��
	int distance(const Date & date) const
	{
		return totalDays - date.totalDays;
	}
};
#endif // DATE_H
