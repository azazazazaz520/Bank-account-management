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
	std::ifstream file("commands.txt", std::ios::app); // 打开文件
	if (!file.is_open()) {
		std::cerr << "无法打开文件" << std::endl;
		return 1;
	}
	std::string line;
	Date date(2008, 11, 1);	//起始日期
	Array<Account*> accounts(0);	//创建账户数组，元素个数为0

	char type;     //账户类型
	int index, day;  //index储存用户的序号
	Date date1, date2;
	double amount, credit, rate, fee;
	string id, desc;
	Account* account;
	while (std::getline(file, line)) { // 逐行读取命令
		
		std::istringstream iss(line);
		std::string command;
		iss >> command; // 提取第一个单词（命令）

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
				accounts[i]->settle(date);            //所有账户的结算

		}
		else {
			std::cerr << "未知命令: " << command << std::endl;
		}

	}
	file.close();
	cout << "(a)add account (d)deposit (w)withdraw (s)show (c)change day (n)next month (q)query (e)exit" << endl;
	char cmd;
	std::ofstream outfile("commands.txt", std::ios::app);
	outfile << endl;
	do {
		//显示日期和总金额
		date.show();
		cout << "\tTotal: " << Account::getTotal() << "\tcommand> ";
		
		cin >> cmd;
		switch (cmd) {
		case 'a':	//增加账户add
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
		case 'd':	//存入现金deposit
			cin >> index >> amount;
			getline(cin, desc);
			accounts[index]->deposit(date, amount, desc);
			outfile << "d" << " " << index << " " << amount << " " << desc << " " << endl;
			break;
		case 'w':	//取出现金withdraw
			cin >> index >> amount;
			getline(cin, desc);
			accounts[index]->withdraw(date, amount, desc);
			outfile << "w" << " " << index << " " << amount << " " << desc << " " << endl;
			break;
		case 's':	//查询各个账户信息
			for (int i = 0; i < accounts.getSize(); i++) {
				cout << "[" << i << "] ";
				accounts[i]->show();
				cout << endl;
			}
			break;
		case 'c':	//改变日期change
			cin >> day;
			if (day < date.getDay())
				cout << "You cannot specify a previous day";
			else if (day > date.getMaxDay())
				cout << "Invalid day";
			else
				date = Date(date.getYear(), date.getMonth(), day);
			outfile << "c" << " " << day << " " << endl;
			break;
		case 'n':   //进入下个月next
			if (date.getMonth() == 12)
				date = Date(date.getYear() + 1, 1, 1);
			else
				date = Date(date.getYear(), date.getMonth() + 1, 1);
			for (int i = 0; i < accounts.getSize(); i++)
				accounts[i]->settle(date);            //所有账户的结算
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