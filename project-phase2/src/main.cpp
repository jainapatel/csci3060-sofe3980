/*
authors: Khirthana Subramanian - 100453865
         Jaina Patel - 100523188
				 James Morrison - 100524362
*/

#include "account_manager.h"
#include "utilities.h"
#include <string>
#include <iostream>

using namespace std;

int main(int argc, char **argv) {
	AccountManager account_manager;
    bool logged_in;
	Utilities::Prompt("Banking System\n");

	string input;
	while (input != "quit"){
		Utilities::Prompt("Enter the transaction you want to do this session: ");
		cin >> input;

		if (input == "login") {
			logged_in = account_manager.Login();
		} else if (logged_in) {
			if (input == "withdrawl") {
				account_manager.Withdrawal();
			}
			else if (input == "transfer") {
				account_manager.Transfer();
			}
			else if (input == "paybill") {
				account_manager.Paybill();
			}
			else if (input == "deposit") {
				account_manager.Deposit();
			}
			else if (input == "createAccount") {
				account_manager.CreateAccount();
			}
			else if (input == "deleteAccount") {
				account_manager.DeleteAccount();
			}
			else if (input == "enableAccount") {
				account_manager.EnableAccount();
			}
			else if (input == "disableAccount") {
				account_manager.DisableAccount();
			}
			else if (input == "changePlan") {
				account_manager.ChangePlan();
			}
			else if (input == "logout") {
				logged_in = account_manager.Logout();
			}
		}
		else{
			Utilities::Prompt("You have to login in order to process transactions\n");
		}
	}
	return 0;
}
