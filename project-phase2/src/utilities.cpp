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
#include <vector>
#include <iostream>
#include <string>

std::string Utilities::Prompt(std::string output, std::string reg){
	/* Generic prompt for all console output
	 * output: represents what should be displayed on screen
	 * re: regular expression representing acceptable generic answers (for names etc)
	 */
	 
	bool valid_input=false;

	if (reg != "") {
		while(valid_input==false){//if input is invalid then prompts again
			std::cout << output << std::endl;

			std::string input;
			std::cin >> input;
			try {
			  std::regex re(reg);
			  std::smatch match;
			  if (regex_search(input, match, re) && match.size() > 1) {
				return match.str(1);
			  }
			} catch (std::regex_error& e) {
			}
			std::cout << "Invalid input." << std::endl;
		}
	} else { //if all we want to do is output to console (ie info)
		std::cout << output << std::endl;
		return "";
	}

}

std::vector<Account> Utilities::LoadAccountInformation(std::string accounts_file){
	//(5 elements in a line:1-account number, 2-account name, 3-account status,4-account balance, 5-account type)

	//read through accounts file to Get information about account holder
	std::string line;
	std::vector<Account> accounts;
	std::fstream infile;
	infile.open(accounts_file);
	while (getline(infile, line)){
		//Account account (line.substr(0,4),line.substr(6,25),line.substr(27,27),line.substr(29,36),line.substr(38,41));
		//accounts.push_front(account);
	}
	infile.close();

	//return accounts;
	return accounts;
}

Account *Utilities::GetAccountFromName(std::string name, std::vector<Account> accounts){
	//Gets account associated with input name
	bool found = false;
	std::vector<Account>::iterator it = accounts.begin();
	for(int i=0; i<accounts.size(); i++){
		if (it->GetAccountName() == name){
			return &*it;
		}
		++it;
	}
	return nullptr;
}

Account *Utilities::GetAccountFromNumber(std::string number, std::vector<Account> accounts){
	//Gets account associated with input account number
	bool found = false;
	std::vector<Account>::iterator it = accounts.begin();
	for(int i=0; i<accounts.size(); i++){
		if (it->GetAccountNumber() == number){
			return &*it;
		}
		++it;
	}

	return nullptr;
}
