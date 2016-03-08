/*
*
*/
#ifndef ACCOUNT_MANAGER_H
#define ACCOUNT_MANAGER_H

#include <string>
#include <vector>
#include "account.h"

class AccountManager{
	std::string transactions_log;
	std::vector<Account> accounts_in_file;
	std::string session_type;
	Account* current_account;


public:
	AccountManager();

	void Login();
	void Withdrawal();
	void Transfer();
	void Paybill();
	void Deposit();
	void CreateAccount();
	void DeleteAccount();
	void EnableAccount();
	void DisableAccount();
	void ChangePlan();
	void Logout();
};

#endif
