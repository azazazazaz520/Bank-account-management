#ifndef DATE_H
#define DATE_H
class Date {
private:
	int year;
	int month;
	int day;
	int totalDays;     //��ǰ���ڵ���ԪԪ�������
public:
	Date(){

	}
	Date(int year, int month, int day);
	bool isLeapyear() const            //�ж�����
	{
		return year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
	}
	int getMaxDay() const;       //�����ǰ���ж�����
	void show() const;          //�����ǰ����
	int getYear() const { return year; }         //��ȡ��
	int getMonth() const { return month; }    //��ȡ��
	int getDay() const { return day; }     //��ȡ��
	int operator - (const Date& date) const {
		return totalDays - date.totalDays;
	}

	const Date& read();
};
#endif // DATE_H
