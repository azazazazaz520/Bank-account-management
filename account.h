#ifndef __ACCOUNT_H__
#define __ACCOUNT_H__
#include "date.h"
#include <string>
class SavingsAccount {
private:
	std::string id;              //�û�id 
	double balance;      //���   
	double rate;         //������ 
	Date lastDate;
	double accumulation;    //�洢�ϴμ�����Ϣ�Ժ�ֱ�����һ�����䶯ʱ�����ۼӵ�ֵ
	static double total;    //�����û�����Ǯ��
public:
	//SavingsAccount();
	SavingsAccount(const Date& date, const std::string& id, double rate);
	void error(const std::string& msg) const;
	void record(const Date & date, double amount, const std::string& desc);
	double accumulate(const Date& date) const;     //�������ָ�����ڵ��˻������ۻ�ֵ
	std::string getId() const;
	double getBalance() const;
	double getRate() const;
	static double getTotal() { return total; }
	void show() const;   //��ʾ�˻���Ϣ
	void deposit(const Date & date, double amount,const std::string &desc);  //���
	void withdraw(const Date & date, double amount, const std::string& desc);    //ȡ��
	void settle(const Date & date);          //������Ϣ


};
#endif
