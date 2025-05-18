#include "account.h"
#include "Array.h"
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <Windows.h> 
using namespace std;
int main() {
	std::ifstream file("commands.txt", std::ios::app); // ���ļ�
	if (!file.is_open()) {
		std::cerr << "�޷����ļ�" << std::endl;
		return 1;
	}
	std::string line;
	Date date(2008, 11, 1);	//��ʼ����
	Array<Account*> accounts(0);	//�����˻����飬Ԫ�ظ���Ϊ0

	char type;     //�˻�����
	int index, day;  //index�����û������
	Date date1, date2;
	double amount, credit, rate, fee;
	string id, desc;
	Account* account;
	while (std::getline(file, line)) { // ���ж�ȡ����
		
		std::istringstream iss(line);
		std::string command;
		iss >> command; // ��ȡ��һ�����ʣ����

		if (command == "a") {
			iss >> type >> id;
			if (type == 's') {
				iss >> rate;
				account = new SavingsAccount(date, id, rate);
			}
			else {
				iss >> credit >> rate >> fee;
				account = new CreditAccount(date, id, credit, rate, fee);
			}
			accounts.resize(accounts.getSize() + 1);
			accounts[accounts.getSize() - 1] = account;
			continue;
		}
		else if (command == "d") {
			iss >> index >> amount >> desc;
			
			accounts[index]->deposit(date, amount, desc);
			
		}
		else if (command == "w") {
			iss >> index >> amount >> desc;
			
			accounts[index]->withdraw(date, amount, desc);
		}
		else if (command == "s") {
			for (int i = 0; i < accounts.getSize(); i++) {
				cout << "[" << i << "] ";
				accounts[i]->show();
				cout << endl;
			}
		}
		else if (command == "c") {
			iss >> day;
			if (day < date.getDay())
				cout << "You cannot specify a previous day";
			else if (day > date.getMaxDay())
				cout << "Invalid day";
			else
				date = Date(date.getYear(), date.getMonth(), day);
		}
		else if (command == "n") {
			if (date.getMonth() == 12)
				date = Date(date.getYear() + 1, 1, 1);
			else
				date = Date(date.getYear(), date.getMonth() + 1, 1);
			for (int i = 0; i < accounts.getSize(); i++)
				accounts[i]->settle(date);            //�����˻��Ľ���

		}
		else {
			std::cerr << "δ֪����: " << command << std::endl;
		}

	}
	file.close();
	cout << "(a)add account (d)deposit (w)withdraw (s)show (c)change day (n)next month (q)query (e)exit" << endl;
	char cmd;
	std::ofstream outfile("commands.txt", std::ios::app);
	outfile << endl;
	do {
		//��ʾ���ں��ܽ��
		date.show();
		cout << "\tTotal: " << Account::getTotal() << "\tcommand> ";
		
		cin >> cmd;
		switch (cmd) {
		case 'a':	//�����˻�add
			outfile << "a" << " ";
			cin >> type >> id;
			outfile << type << " " << id << " ";
			if (type == 's') {
				cin >> rate;
				outfile << rate << " " << endl;
				account = new SavingsAccount(date, id, rate);
			}
			else {
				cin >> credit >> rate >> fee;
				outfile << credit << " " << rate << " " << fee << " " << endl;
				account = new CreditAccount(date, id, credit, rate, fee);
			}
			accounts.resize(accounts.getSize() + 1);
			accounts[accounts.getSize() - 1] = account;
			break;
		case 'd':	//�����ֽ�deposit
			cin >> index >> amount;
			getline(cin, desc);
			accounts[index]->deposit(date, amount, desc);
			outfile << "d" << " " << index << " " << amount << " " << desc << " " << endl;
			break;
		case 'w':	//ȡ���ֽ�withdraw
			cin >> index >> amount;
			getline(cin, desc);
			accounts[index]->withdraw(date, amount, desc);
			outfile << "w" << " " << index << " " << amount << " " << desc << " " << endl;
			break;
		case 's':	//��ѯ�����˻���Ϣ
			for (int i = 0; i < accounts.getSize(); i++) {
				cout << "[" << i << "] ";
				accounts[i]->show();
				cout << endl;
			}
			break;
		case 'c':	//�ı�����change
			cin >> day;
			if (day < date.getDay())
				cout << "You cannot specify a previous day";
			else if (day > date.getMaxDay())
				cout << "Invalid day";
			else
				date = Date(date.getYear(), date.getMonth(), day);
			outfile << "c" << " " << day << " " << endl;
			break;
		case 'n':   //�����¸���next
			if (date.getMonth() == 12)
				date = Date(date.getYear() + 1, 1, 1);
			else
				date = Date(date.getYear(), date.getMonth() + 1, 1);
			for (int i = 0; i < accounts.getSize(); i++)
				accounts[i]->settle(date);            //�����˻��Ľ���
			outfile << "n " << endl;
			break;
		case 'q':
			date1 = Date::read();

			date2 = Date::read();
			Account::query(date1, date2);

			break;
		}
	} while (cmd != 'e');

	
	for (int i = 0; i < accounts.getSize(); i++)
		delete accounts[i];

	

	
	return 0;

}