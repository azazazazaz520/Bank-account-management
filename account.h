#ifndef __ACCOUNT_H__
#define __ACCOUNT_H__
#include "date.h"
#include <string>
#include "Accumulator.h"
#include "AccountRecord.h"
#include <map>
class Account {
private:
	std::string id;
	double balance;      //���
	static double total;        //�����˻����ܽ��
protected:
	Account(const Date &date, const std::string &id);
	void record(const Date &date, double amount, const std::string& desc);
	void error(const std::string& msg)const;
	static std::multimap<Date, AccountRecord> recordMap;
public:
	
	double getBalance()const { return balance; }
	const std::string getId(const std::string& id)const { return id; }
	static double getTotal() { return total; }
	static void query(const Date& date1,const Date& date2);         //��ѯһ������֮�����Ŀ
	//�����ֽ�dateΪ���ڣ�amountΪ��descΪ����˵��
	virtual void deposit(const Date& date, double amount, const std::string& desc) = 0;
	//ȡ��
	virtual void withdraw(const Date& date, double amount, const std::string& desc) = 0;
	//���㣨������Ϣ����ѵȣ���ÿ�½���һ�Σ�dateΪ��������
	virtual void settle(const Date& date) = 0;
	//��ʾ�˻���Ϣ
	virtual void show() const;

};

/**************************************************************************************************/

class SavingsAccount : public Account {
private:
	Accumulator Acc;       //�ۼ���
	double rate;         //������ 
public:
	
	SavingsAccount(const Date& date, const std::string& id, double rate);
	double getRate() const { return rate; }
	virtual void deposit(const Date& date, double amount, const std::string& desc);  //���
	virtual void withdraw(const Date& date, double amount, const std::string& desc);    //ȡ��
	virtual void settle(const Date& date);          //������Ϣ,ÿ��1��1�յ���


};


/**************************************************************************************************/




class CreditAccount :public Account {
private:
	Accumulator Acc;       //�ۼ���
	double credit;         //���ö��
	double rate;		   //Ƿ��������
	double fee;				//���ÿ������
	double getDebt() const {	//���Ƿ���
		double balance = getBalance();
		return (balance < 0 ? balance : 0);
	}
	
	
public:
	CreditAccount(const Date &date, const std::string& id,double credit,double rate,double fee);
	double getCredit()const { return credit; }
	double gatRate() const { return rate; }
	double getFee() const { return fee; }
	double getAvailableCredit()const {                //��ȡ�������ö��
		if (getBalance() < 0)
		{
			return credit + getBalance();
		}
		else {
			return credit;
		}
	}
	virtual void deposit(const Date& date, double amount, const std::string& desc);
	virtual void withdraw(const Date& date, double amount, const std::string& desc);
	virtual void settle(const Date &date);
	virtual void show()const;

};

#endif
