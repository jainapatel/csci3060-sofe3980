/*
authors: Khirthana Subramanian - 100453865
         Jaina Patel - 100523188
		 James Morrison - 100524362

This class contains functions to retrieve and store account information
*/

#include <stdio.h>
#include "account.h"
#include <iostream>
#include <string>
#include <fstream>

Account::Account(std::string number, std::string name, std::string status, std::string  balance , std::string type){
	this->account_name = name;
	this->account_number = number;
	this->account_type = type;
	this->account_status = status;
	this->account_balance= stod(balance);
}

//leave first letter lowercase for all methods, better naming conventions this way, AND it messes up account_manager
double Account::GetBalance(){
	//read through the accounts file & store the current balance of account holder
	return this->account_balance;
}

std::string Account::GetAccountType(){
	//read through the accounts file & store the account type of account holder (S/NS)
	return this->account_type;
}

std::string Account::GetAccountStatus(){
	//read through the accounts file & store the status of account holder (A/D)
	return this->account_status;
}

std::string Account::GetAccountName(){
	return this->account_name;
}

std::string Account::GetAccountNumber(){
	return this->account_number;
}

void Account::SetBalance(double balance){
	//read through the accounts file & store the current balance of account holder
	this->account_balance = balance;
}

void Account::SetAccountType(std::string type){
	//read through the accounts file & store the account type of account holder (S/NS)
	this->account_type = type;
}

void Account::SetAccountStatus(std::string status){
	//read through the accounts file & store the status of account holder (A/D)
	this->account_status = status;
}
