/*
authors: Khirthana Subramanian - 100453865
         Jaina Patel - 100523188
				 James Morrison - 100524362
*/

#include "account_manager.h"
#include <string>
#include <iostream>

using namespace std;

int main(int argc, char **argv) {
	AccountManager account_manager;

	cout << "Banking System" << endl;
	cout << "Enter the transaction you want to do this session:" << endl;

	string input;
	cin >> input;

	if (input == "login") {
		account_manager.Login();
	} else {
		printf("You have to login in order to process transactions\n");
	}

	return 0;
}
