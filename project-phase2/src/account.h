/*
authors: Khirthana Subramanian - 100453865
         Jaina Patel - 100523188
		 James Morrison - 100524362
*/

#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>

class Account{
private:
	std::string account_name;
	std::string account_number;
	double account_balance;
	std::string account_type;
	std::string account_status;

public:
	Account(std::string number, std::string name, std::string status, std::string balance , std::string type);

	double GetBalance();
	std::string GetAccountType();
	std::string GetAccountStatus();
	std::string GetAccountName();
	std::string GetAccountNumber();
	void SetBalance(double balance);
	void SetAccountType(std::string type);
	void SetAccountStatus(std::string status);
};

#endif
