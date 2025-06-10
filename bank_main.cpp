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
		std::cerr << "无法打开文件" << std::endl;               //错误处理
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

        try {
            if (command == "a") {
                // 添加账户逻辑
                char type;
                std::string id;
                iss >> type >> id;
                if (type == 's') {
                    double rate;
                    iss >> rate;
                    accounts.resize(accounts.getSize() + 1);
                    accounts[accounts.getSize() - 1] = new SavingsAccount(date, id, rate);
                }
                else {
                    double credit, rate, fee;
                    iss >> credit >> rate >> fee;
                    accounts.resize(accounts.getSize() + 1);
                    accounts[accounts.getSize() - 1] = new CreditAccount(date, id, credit, rate, fee);
                }
            }
            else if (command == "d") {
                // 存款逻辑
                int index;
                double amount;
                std::string desc;
                iss >> index >> amount;
                std::getline(iss >> std::ws, desc); // 读取剩余描述
                accounts[index]->deposit(date, amount, desc);
            }
            else if (command == "w") {
                // 取款逻辑
                int index;
                double amount;
                std::string desc;
                iss >> index >> amount;
                std::getline(iss >> std::ws, desc);
                accounts[index]->withdraw(date, amount, desc);
            }
            else if (command == "c") {
                // 更改日期逻辑
                int day;
                iss >> day;
                if (day < date.getDay() || day > date.getMaxDay()) {
                    throw std::runtime_error("Invalid day");
                }
                date = Date(date.getYear(), date.getMonth(), day);
            }
            else if (command == "n") {
                // 下个月逻辑
                if (date.getMonth() == 12) {
                    date = Date(date.getYear() + 1, 1, 1);
                }
                else {
                    date = Date(date.getYear(), date.getMonth() + 1, 1);
                }
                for (int i = 0; i < accounts.getSize(); i++) {
                    accounts[i]->settle(date);
                }
            }
        }
        catch (const AccountException& e) {
            std::cerr << "Account Error (" << e.getAccount()->getId() << "): " << e.what() << std::endl;
        }
        catch (const std::out_of_range& e) {
            std::cerr << "Index Error: " << e.what() << std::endl;
        }
        catch (const std::runtime_error& e) {
            std::cerr << "Date Error: " << e.what() << std::endl;
        }
        catch (...) {
            std::cerr << "Unknown Error" << std::endl;
        }
    }
    file.close();

   
    std::ofstream outfile("commands.txt", std::ios::app);
    char cmd;
    cout << "操作语法：" << endl;
	cout << "a:" << "  +s(储蓄)/ c (信用卡) + 账户序号 + 年利率(储蓄) / (信用卡账户) 可透支额度 + 欠款日利率 +  年费" << endl;
    cout << "(a)add account (d)deposit (w)withdraw (s)show (c)change day (n)next month (q)query (e)exit" << endl;
    do {
        date.show();
        std::cout << "\tTotal: " << Account::getTotal() << "\tcommand> ";
        std::cin >> cmd;

        try {
            switch (cmd) {
            case 'a': {	//添加账户add
                std::cin >> type >> id;
                if (type == 's') {	//储蓄账户
                    std::cin >> rate;
                    accounts.resize(accounts.getSize() + 1);
                    accounts[accounts.getSize() - 1] = new SavingsAccount(date, id, rate);
                }
                else {	//信用卡账户
                    std::cin >> credit >> rate >> fee;
                    accounts.resize(accounts.getSize() + 1);
                    accounts[accounts.getSize() - 1] = new CreditAccount(date, id, credit, rate, fee);
                }
                outfile << "a " << type << " " << id << " " << rate << std::endl;
                break;
			}
            case 'd': {
                int index;
                double amount;
                std::string desc;
                std::cin >> index >> amount;
                std::getline(std::cin >> std::ws, desc);
                accounts[index]->deposit(date, amount, desc);
                outfile << "d " << index << " " << amount << " " << desc << std::endl;
                break;
            }
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
            case 'e':
                break;
            default:
                std::cerr << "Invalid command" << std::endl;
            }
        }
        catch (const AccountException& e) {
            std::cerr << "Account Error (" << e.getAccount()->getId() << "): " << e.what() << std::endl;
        }
        catch (const std::out_of_range& e) {
            std::cerr << "Index Error: " << e.what() << std::endl;
        }
        catch (const std::runtime_error& e) {
            std::cerr << "Date Error: " << e.what() << std::endl;
        }
        catch (...) {
            std::cerr << "Unknown Error" << std::endl;
        }
	} while (cmd != 'e');

	
	for (int i = 0; i < accounts.getSize(); i++)
		delete accounts[i];

	

	
	return 0;

}