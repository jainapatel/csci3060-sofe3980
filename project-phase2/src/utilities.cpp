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
			std::cout << output;

			std::string input;
			std::cin.ignore(1);
			std::getline(std::cin,input);
			try {
				std::regex re(reg);
				std::smatch match;

				std::regex_search(input, match, re);

				if (match.size() >= 1) {
					return match.str(0);
				}
			} catch (std::regex_error& e) {
			}
			std::cout << "Invalid input." << std::endl;
		}
	} else { //if all we want to do is output to console (ie info)
		std::cout << output;
		return "";
	}

}

std::vector<Account> Utilities::LoadAccountInformation(std::string accounts_file){
	//(5 elements in a line:1-account number, 2-account name, 3-account status,4-account balance, 5-account type)

	//read through accounts file to Get information about account holder
	std::string line;
	std::vector<Account> accounts;
	std::ifstream infile(accounts_file);

	while (getline(infile, line)){
		if (line.size() == 39){
			Account account (line.substr(0,4),line.substr(6,25),line.substr(27,27),line.substr(29,36),line.substr(38,38));
			accounts.push_back(account);
		}
	}
	infile.close();
	//return accounts;
	return accounts;
}

Account *Utilities::GetAccountFromName(std::string name, std::vector<Account> accounts){
	//Gets account associated with input name

	for(auto i = accounts.begin(); i!=accounts.end(); i++){
		Account acc = *i;
		if (acc.GetAccountName().find(name) != std::string::npos){
			return &acc;
		}
	}
	return nullptr;
}

Account *Utilities::GetAccountFromNumber(std::string number, std::vector<Account> accounts){
	//Gets account associated with input account number

	for(auto i = accounts.begin(); i!=accounts.end(); i++){
		Account acc = *i;
		if (std::stod(acc.GetAccountNumber()) == std::stod(number)){
			return &acc;
		}
	}
	return nullptr;
}
