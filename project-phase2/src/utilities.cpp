/*
authors: Khirthana Subramanian - 100453865
         Jaina Patel - 100523188
				 James Morrison - 100524362

This class is meant to contain simplified and modular usages of common functions
 */

#include <stdio.h>
#include "account.h"
#include "utilities.h"
#include <fstream>
#include <regex>
#include <list>
#include <iostream>
#include <string>


using namespace std;

string Utilities::Prompt(string output, string reg, list<string> acceptions) {
	/* Generic prompt for all console output
	 * output: represents what should be displayed on screen
	 * acceptions: list of strings that are acceptable specific inputs from user (like standard/admin)
	 * re: regular expression representing acceptable generic answers (for names etc)
	 */

	bool valid_input=false;

	if (acceptions.size() != 0 or reg != "") {
		while(!valid_input){//if input is invalid then prompts again
			cout << output << endl;

			string input;
			cin >> input;

			//if there are list of possible input acceptions then, it compares the input with options
			//if input is among accepted inputs then input return
			if(acceptions.size()!=0){
				cout<<"acceptions !=0";

				for (auto it = acceptions.begin(); it != acceptions.end();) {
					if (*it == input) {
						return input;
					} else {
						++it;
					}
				}
			}else{//check if input matches given pattern; if it matches, input return
				if(regex_match (input, regex(reg))) {
					return input;
				}
				cout << "Invalid input." << endl;
			}
		}
	} else { //if all we want to do is output to console (ie info)
		cout << output << endl;
		return "";
	}

}

list<Account> Utilities::LoadAccountInformation(string accounts_file){
	//(5 elements in a line:1-account number, 2-account name, 3-account status,4-account balance, 5-account type)

	//read through accounts file to get information about account holder
	string line;
	list<Account> accounts = {};
	fstream infile;
	infile.open(accounts_file);
	while (getline(infile, line)){
		Account account (line.substr(0,4),line.substr(6,25),line.substr(27,27),line.substr(29,36),line.substr(38,41));
		accounts.push_front(account);
	}
	infile.close();

	return accounts;

}

Account *Utilities::GetAccountFromName(string name, list<Account> accounts){
	//gets account associated with input name
	bool found = false;
	list<Account>::iterator it = accounts.begin();
	for(int i=0; i<accounts.size(); i++){
		if (it->GetAccountName() == name){
			return &*it;
		}
		++it;
	}
	return nullptr;
}

Account *Utilities::GetAccountFromNumber(string number, list<Account> accounts){
	//gets account associated with input account number
	bool found = false;
	list<Account>::iterator it = accounts.begin();
	for(int i=0; i<accounts.size(); i++){
		if (it->GetAccountNumber() == number){
			return &*it;
		}
		++it;
	}

	return nullptr;
}
