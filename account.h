#ifndef __ACCOUNT_H__
#define __ACCOUNT_H__
#include "date.h"
#include <string>
#include "Accumulator.h"
class Account {
private:
	std::string id;
	double balance;      //���
	static double total;        //�����˻����ܽ��
protected:
	Account(const Date &date, const std::string &id);
	void record(const Date &date, double amount, const std::string& desc);
	void error(const std::string& msg)const;
	
public:
	void show() const;
	double getBalance()const { return balance; }
	const std::string getId(const std::string& id)const { return id; }
	static double getTotal() { return total; }
};

/**************************************************************************************************/

class SavingsAccount : public Account {
private:
	Accumulator Acc;       //�ۼ���
	double rate;         //������ 
public:
	
	SavingsAccount(const Date& date, const std::string& id, double rate);
	double getRate() const { return rate; }
	void deposit(const Date& date, double amount, const std::string& desc);  //���
	void withdraw(const Date& date, double amount, const std::string& desc);    //ȡ��
	void settle(const Date& date);          //������Ϣ


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
	CreditAccount(const Date &date, const std::string& id,double credit,double fee, double rate);
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
	void deposit(const Date& date, double amount, const std::string& desc);
	void withdraw(const Date& date, double amount, const std::string& desc);
	void settle(const Date &date);
	void show()const;

};

#endif
