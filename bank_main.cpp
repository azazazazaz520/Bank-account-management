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
		std::cerr << "�޷����ļ�" << std::endl;               //������
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

        try {
            if (command == "a") {
                // ����˻��߼�
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
                // ����߼�
                int index;
                double amount;
                std::string desc;
                iss >> index >> amount;
                std::getline(iss >> std::ws, desc); // ��ȡʣ������
                accounts[index]->deposit(date, amount, desc);
            }
            else if (command == "w") {
                // ȡ���߼�
                int index;
                double amount;
                std::string desc;
                iss >> index >> amount;
                std::getline(iss >> std::ws, desc);
                accounts[index]->withdraw(date, amount, desc);
            }
            else if (command == "c") {
                // ���������߼�
                int day;
                iss >> day;
                if (day < date.getDay() || day > date.getMaxDay()) {
                    throw std::runtime_error("Invalid day");
                }
                date = Date(date.getYear(), date.getMonth(), day);
            }
            else if (command == "n") {
                // �¸����߼�
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
    cout << "�����﷨��" << endl;
	cout << "a:" << "  +s(����)/ c (���ÿ�) + �˻���� + ������(����) / (���ÿ��˻�) ��͸֧��� + Ƿ�������� +  ���" << endl;
    cout << "(a)add account (d)deposit (w)withdraw (s)show (c)change day (n)next month (q)query (e)exit" << endl;
    do {
        date.show();
        std::cout << "\tTotal: " << Account::getTotal() << "\tcommand> ";
        std::cin >> cmd;

        try {
            switch (cmd) {
            case 'a': {	//����˻�add
                std::cin >> type >> id;
                if (type == 's') {	//�����˻�
                    std::cin >> rate;
                    accounts.resize(accounts.getSize() + 1);
                    accounts[accounts.getSize() - 1] = new SavingsAccount(date, id, rate);
                }
                else {	//���ÿ��˻�
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