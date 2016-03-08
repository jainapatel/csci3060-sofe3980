/*
*
*/
#include "account.h"
#include "utilities.h"
#include "account_manager.h"
#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

AccountManager::AccountManager() : transactions_log(""), session_type(""), current_account(0) {
}

void AccountManager::Login(){
	//an example usage of the utility functions
	this->session_type = Utilities::Prompt("Please Enter the Kind of Session: ","standard|admin");

	this->accounts_in_file = Utilities::LoadAccountInformation("Accountsfile.txt");

	if(this->session_type=="standard"){
		std::string account_name = Utilities::Prompt("Please Enter the Name of the Account Holder: ","\\u\\l+ \\u\\l+");
		this->current_account = Utilities::GetAccountFromName(account_name,accounts_in_file);

		if (this->current_account == nullptr){
			Utilities::Prompt("Invalid Account Name.");
		}
	}
}

void AccountManager::Withdrawal(){
	if(this->session_type=="admin"){
		std::string account_name =  Utilities::Prompt("Please Enter the Name of the Account Holder: ","\\u\\l+ \\u\\l+");
		this->current_account = Utilities::GetAccountFromName(account_name,this->accounts_in_file);
		if (this->current_account == nullptr){
			Utilities::Prompt("Invalid Account Name.");
		}
	}


	std::string account_number = Utilities::Prompt("Please Enter the Account Number: ","\\d{0,5}");
	if (account_number != this->current_account->GetAccountNumber()){
		return;
	}

	double withdrawal_amount= std::stod(Utilities::Prompt("Please Enter the Withdrawl Ammount: ","\\d{0,5}")); //needs changing reg to upper amount limit
	double current_balance = this->current_account->GetBalance();
	if ( current_balance > withdrawal_amount){
		current_account->SetBalance(current_balance-withdrawal_amount);
		Utilities::Prompt("Transaction successful.");
	}
	else{
		Utilities::Prompt("Insufficient funds.");
	}


	//if successful withdrawal; add withdrawal transaction information in transactions_log list
	this->transactions_log.append("01 "+this->current_account->GetAccountName()+" "+this->current_account->GetAccountNumber()+" "+std::to_string(withdrawal_amount)+" "+this->current_account->GetAccountType()+"\n");
}

void AccountManager::Transfer(){
	if(this->session_type=="admin"){
		std::string account_name = Utilities::Prompt("Please Enter the Name of the Account Holder: ","\\u\\l+ \\u\\l+");
		this->current_account = Utilities::GetAccountFromName(account_name,this->accounts_in_file);
		if (this->current_account == nullptr){
			Utilities::Prompt("Invalid Account Name.");
		}
	}

	std::string account_number = Utilities::Prompt("Please Enter the Account Number: ","\\d{0,5}");
	std::string account_number_to = "";
	double transfer_amount = 0;

	//transfer amount to account2 from account1


	//if successful transfer; add transfer transaction information in transactions_log list
	this->transactions_log.append("01 "+this->current_account->GetAccountName()+" "+this->current_account->GetAccountNumber()+" "+std::to_string(transfer_amount)+" "+this->current_account->GetAccountType()+"\n");
	this->transactions_log.append("04 "+this->current_account->GetAccountName()+" "+this->current_account->GetAccountNumber()+" "+std::to_string(transfer_amount)+" "+this->current_account->GetAccountType()+"\n");

}

void AccountManager::Paybill(){
	if(this->session_type=="admin"){
		std::string account_name =  Utilities::Prompt("Please Enter the Name of the Account Holder: ","\\u\\l+ \\u\\l+");
		this->current_account = Utilities::GetAccountFromName(account_name,this->accounts_in_file);
		if (this->current_account == nullptr){
			Utilities::Prompt("Invalid Account Name.");
		}
	}

	std::string account_number = Utilities::Prompt("Please Enter the Account Number: ","\\d{0,5}");
	std::string company_paidto = "";
	double amount_to_pay = 0;

	//paybill amount to company


	//if successful paybill; add paybill transaction information in transactions_log list
	this->transactions_log.append("03 "+this->current_account->GetAccountName()+" "+this->current_account->GetAccountNumber()+" "+std::to_string(amount_to_pay)+" "+this->current_account->GetAccountType()+"\n");

}

void AccountManager::Deposit(){
	if(this->session_type=="admin"){
		std::string account_name =  Utilities::Prompt("Please Enter the Name of the Account Holder: ","\\u\\l+ \\u\\l+");
		this->current_account = Utilities::GetAccountFromName(account_name,this->accounts_in_file);
		if (this->current_account == nullptr){
			Utilities::Prompt("Invalid Account Name.");
		}
	}

	double account_number = std::stod(Utilities::Prompt("Please Enter the Account Number: ","\\d{0,5}"));
	double amount_deposit = 0;

	//deposit amount


	//if successful deposit; add deposit transaction information in transactions_log list
	this->transactions_log.append("04 "+this->current_account->GetAccountName()+" "+this->current_account->GetAccountNumber()+" "+std::to_string(amount_deposit)+" "+this->current_account->GetAccountType()+"\n");
}

void AccountManager::CreateAccount(){
	if(this->session_type=="admin"){
		std::string account_name =  Utilities::Prompt("Please Enter the Name of the Account Holder: ","\\u\\l+ \\u\\l+");

		//initial balance
		double account_balance = 0;

		//create account with unique Please Enter the Account Number:

		//if account created; add account information in transactions_log list
		this->transactions_log.append("05 "+this->current_account->GetAccountName()+" "+this->current_account->GetAccountNumber()+" "+std::to_string(this->current_account->GetBalance())+" "+this->current_account->GetAccountType()+"\n");
	}
	else{
		Utilities::Prompt("insufficient privilages.");
	}
}

void AccountManager::DeleteAccount(){
	if(this->session_type=="admin"){
		std::string account_name =  Utilities::Prompt("Please Enter the Name of the Account Holder: ","\\u\\l+ \\u\\l+");
		std::string account_number = Utilities::Prompt("Please Enter the Account Number: ","\\d{0,5}");
		//delete account from system

		//if account deleted; add deleted account information in transactions_log list
		this->transactions_log.append("06 "+this->current_account->GetAccountName()+" "+this->current_account->GetAccountNumber()+" "+"      "+this->current_account->GetAccountType()+"\n");
	}
	else{
		Utilities::Prompt("insufficient privilages.");
	}
}

void AccountManager::EnableAccount(){ // theoretically complete
	if(this->session_type=="admin"){
		std::string account_name =  Utilities::Prompt("Please Enter the Name of the Account Holder: ","\\u\\l+ \\u\\l+");
		std::string account_number = Utilities::Prompt("Please Enter the Account Number: ","\\d{0,5}");

		//enable account; account status from D to A
		this->current_account = Utilities::GetAccountFromNumber(account_number,this->accounts_in_file);
		if (this->current_account == nullptr){
			Utilities::Prompt("Invalid Account Number.");
		}

		this->current_account->SetAccountStatus("A"); // Set active

		//if account enabled; add enabed account information in transactions_log list
		this->transactions_log.append("09 "+this->current_account->GetAccountName()+" "+this->current_account->GetAccountNumber()+" "+std::to_string(this->current_account->GetBalance())+" "+this->current_account->GetAccountStatus()+"\n");
	}
	else{
		Utilities::Prompt("insufficient privilages.");
	}
}

void AccountManager::DisableAccount(){ // theoretically complete
	if(this->session_type=="admin"){
		std::string account_name =  Utilities::Prompt("Please Enter the Name of the Account Holder: ","\\u\\l+ \\u\\l+");
		std::string account_number = Utilities::Prompt("Please Enter the Account Number: ","\\d{0,5}");

		//disable account; account status from A to D
		this->current_account = Utilities::GetAccountFromNumber(account_number,this->accounts_in_file);
		if (this->current_account == nullptr){
			Utilities::Prompt("Invalid Account Number.");
		}

		this->current_account->SetAccountStatus("D"); // Set active

		//if account disabled; add disabled account information in transactions_log list
		this->transactions_log.append("07 "+this->current_account->GetAccountName()+" "+this->current_account->GetAccountNumber()+" "+std::to_string(this->current_account->GetBalance())+" "+this->current_account->GetAccountStatus()+"\n");
	}
	else{
		Utilities::Prompt("insufficient privilages.");
	}
}

void AccountManager::ChangePlan(){ // theoretically complete
	if(this->session_type=="admin"){
		std::string account_name =  Utilities::Prompt("Please Enter the Name of the Account Holder: ","\\u\\l+ \\u\\l+");
		std::string account_number = Utilities::Prompt("Please Enter the Account Number: ","\\d{0,5}");
		//changeplan for account; account type should be change (S/NS)

		this->current_account = Utilities::GetAccountFromNumber(account_number,this->accounts_in_file);
		if (this->current_account == nullptr){
			Utilities::Prompt("Invalid Account Number.");
		}

		if (this->current_account->GetAccountStatus() == "S"){
			this->current_account->SetAccountType("NS");
		}
		else{
			this->current_account->SetAccountType("S");
		}

		//if account plan is changed; add account plan information in transactions_log list
		this->transactions_log.append("08 "+this->current_account->GetAccountName()+" "+this->current_account->GetAccountNumber()+" "+std::to_string(this->current_account->GetBalance())+" "+this->current_account->GetAccountType()+"\n");

	}
	else{
		Utilities::Prompt("insufficient privilages.");
	}
}

void AccountManager::Logout(){
	//end session

	//if logout; add logout information in transactions_log list
	this->transactions_log.append("00 "+this->current_account->GetAccountName()+" "+this->current_account->GetAccountNumber()+" "+"      "+this->current_account->GetAccountType()+"\n");

	//output transaction file log
	std::fstream outfile;
	outfile.open("transaction_log.txt");
	outfile << this->transactions_log << std::endl;
	outfile.close();
}
