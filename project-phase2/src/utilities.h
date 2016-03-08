/*
authors: Khirthana Subramanian - 100453865
         Jaina Patel - 100523188
				 James Morrison - 100524362
*/

#include <stdio.h>
#include "account.h"
#include <fstream>
#include <regex>
#include <list>
#include <iostream>
#include <string>


#ifndef UTILITIES_H
#define UTILITIES_H

class Utilities{
public:
	static std::string Prompt(std::string output, std::string reg = "", std::list<std::string> acceptions = {});
	static std::list<Account> LoadAccountInformation(std::string accounts_file);
	static Account *GetAccountFromName(std::string name, std::list<Account> accounts);
	static Account *GetAccountFromNumber(std::string number, std::list<Account> accounts);
};

#endif
