/*
authors: Khirthana Subramanian - 100453865
         Jaina Patel - 100523188
				 James Morrison - 100524362

This class contains functions to compute transactions on accounts
*/

#include "utilities.h"
#include "account_manager.h"
#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include <cstdlib>
#include <ctime>
using namespace std;

void AccountManager::Login(){
//start of Session
	session_type= Utilities::Prompt("Please Enter the Kind of Session (standard/admin):", "standard|admin");

	//if session is standard then, prompts account name; if invalid input then prompts again
	if(session_type=="standard"){
		bool input_valid=false;
		while(input_valid==false){
			account_name = Utilities::Prompt("Please Enter the Name of the Account Holder: ","[A-z\\s]{1,20}");

			current_account = Utilities::GetAccountFromName(account_name,accounts_in_file);

			if (this->current_account == nullptr){
				Utilities::Prompt("Invalid Account Name.");
			}else{
				//if account name is valid then prompts next transaction
			Utilities::Prompt("Valid Account Name.");
				input_valid=true;

				transaction=Utilities::Prompt("Enter next transaction: ",transaction_acceptions);//appropriate function will be called to compute transaction request
				TransactionCall(transaction);
			}
		}
	}
}

void AccountManager::Withdrawal(){
//withdraw amount from account

	if(session_type=="admin"){

	  bool input_valid=false;
		while(input_valid==false){
			account_name = Utilities::Prompt("Please Enter the Name of the Account Holder: ","[A-z\\s]{1,20}");

			current_account = Utilities::GetAccountFromName(account_name,accounts_in_file);

			if (this->current_account == nullptr){
				Utilities::Prompt("Invalid Account Name.");
			}else{
				//if account name is valid then prompts next transaction
						Utilities::Prompt("Valid Account Name.");
				input_valid=true;
			}
		}
	}

//prompts account number; if invalid prompts again
	bool input_number_valid=false;
	while(input_number_valid==false){
		account_number = (Utilities::Prompt("Please Enter the Account Number: ","\\d{5}"));

		if (account_number != this->current_account->GetAccountNumber()){
					Utilities::Prompt("Input Account Number is invalid.");
		}else{
			input_number_valid=true;
		}
	}

double withdrawal_amount=0;
while(withdrawal_amount<=0){
	withdrawal_amount= stod(Utilities::Prompt("Please Enter the Withdrawal Amount: ","\\d{5}\\.\\d{2}|\\d{1}\\.\\d{2}|\\.\\d{2}"));
	Utilities::Prompt("Amount should be more than 0$");
}

double current_balance = this->current_account->GetBalance();

if(this->current_account->GetAccountStatus()=="A"){
	//transaction fee is charged
	if(this->current_account->GetAccountType()=="S"){
		current_account->SetBalance(current_balance-0.05);
	}else{
		current_account->SetBalance(current_balance-0.10);
	}
	if(session_type=="standard"){
	withdrawal_limit=withdrawal_limit+withdrawal_amount;
}
		if(session_type=="admin"||withdrawal_limit<500){
			if (current_balance > withdrawal_amount){
				current_account->SetBalance(current_balance-withdrawal_amount);
				Utilities::Prompt("Transaction successful.");

				Utilities::Prompt("Transaction fee deducted.");

				//adds withdrawal transaction information in transactions_log list
				this->transactions_log.append("01 "+this->current_account->GetAccountName()+" "+(this->current_account->GetAccountNumber())+" "+to_string(withdrawal_amount)+" "+this->current_account->GetAccountType()+"\n");

				transaction=Utilities::Prompt("Enter next transaction: ",transaction_acceptions);
				TransactionCall(transaction);
			}
	}else{
		Utilities::Prompt("Withdrawal unsuccessful.");
		transaction=Utilities::Prompt("Enter next transaction: ",transaction_acceptions);
		TransactionCall(transaction);

		if(session_type=="standard"){
		withdrawal_limit=withdrawal_limit-withdrawal_amount;
	}

		//transaction fee is reimboursed as transaction is denied
		if(this->current_account->GetAccountType()=="S"){
			current_account->SetBalance(current_balance+0.05);
		}else{
			current_account->SetBalance(current_balance+0.10);
		}
			Utilities::Prompt("Transaction fee not deducted.");
	}
}else{
Utilities::Prompt("Transaction unsuccessful. Account is disabled.");
transaction=Utilities::Prompt("Enter next transaction: ",transaction_acceptions);
TransactionCall(transaction);
}
}

void AccountManager::Transfer(){
//transfer amount to account2 from account1

	if(session_type=="admin"){

		bool input_valid=false;
		while(input_valid==false){
			account_name = Utilities::Prompt("Please Enter the Name of the Account Holder: ","[A-z\\s]{1,20}");

			current_account = Utilities::GetAccountFromName(account_name,accounts_in_file);

			if (this->current_account == nullptr){
					Utilities::Prompt("Invalid Account Name.");
			}else{
				//if account name is valid then prompts next transaction
				Utilities::Prompt("Valid Account Name.");
				input_valid=true;
			}
		}
	}
		//prompts account number; if invalid prompts again
		bool input_number_valid=false;
		while(input_number_valid==false){
			account_number = (Utilities::Prompt("Please Enter the Account Number: ","\\d{5}"));

			if (account_number != this->current_account->GetAccountNumber()){
				Utilities::Prompt("Input Account Number is invalid.");
			}else{
				input_number_valid=true;
			}
		}

		Account* transfer_account;
		//prompts account transferred to; verify if account number is valid in current accounts list; if invalid prompts again
		bool input_number_to_valid=false;
		while(input_number_to_valid==false){
			string account_number_to = "";
			account_number_to = (Utilities::Prompt("Please Enter the account transferred to: ","\\d{5}"));

			transfer_account = Utilities::GetAccountFromNumber(account_number_to,accounts_in_file);
			if (transfer_account == nullptr){
				Utilities::Prompt("Input Account Number transferred to is invalid.");
			}else{
				input_number_to_valid=true;
			}
		}

	double transfer_amount = 0;

	while(transfer_amount<=0){
	transfer_amount= stod(Utilities::Prompt("Please Enter the Transfer Amount: ","\\d{5}\\.\\d{2}|\\d{1}\\.\\d{2}|\\.\\d{2}"));
	Utilities::Prompt("Amount should be more than 0$");
	}

	double current_balance = this->current_account->GetBalance();
if(this->current_account->GetAccountStatus()=="A"){
	//transaction fee is charged
	if(this->current_account->GetAccountType()=="S"){
		current_account->SetBalance(current_balance-0.05);
	}else{
		current_account->SetBalance(current_balance-0.10);
	}
if(session_type=="standard"){
	transfer_limit=transfer_limit+transfer_amount;
}
		if(session_type=="admin"||transfer_limit<1000){
			if ((current_balance > transfer_amount)&&((transfer_account->GetBalance())<99999.99)){
				//transfer amount to account2 from account1 (update account balance)
				current_account->SetBalance(current_balance-transfer_amount);
				Utilities::Prompt("Transaction successful.");

				Utilities::Prompt("Transaction fee deducted.");

				//adds transfer transaction information in transactions_log list
				this->transactions_log.append("01 "+this->current_account->GetAccountName()+" "+(this->current_account->GetAccountNumber())+" "+to_string(transfer_amount)+" "+this->current_account->GetAccountType()+"\n");
				this->transactions_log.append("04 "+transfer_account->GetAccountName()+" "+(transfer_account->GetAccountNumber())+" "+to_string(transfer_amount)+" "+transfer_account->GetAccountType()+"\n");

				transaction=Utilities::Prompt("Enter next transaction: ",transaction_acceptions);
				TransactionCall(transaction);
			}
	}else{
		Utilities::Prompt("Transfer unsuccessful.");
		transaction=Utilities::Prompt("Enter next transaction: ",transaction_acceptions);
		TransactionCall(transaction);
		if(session_type=="standard"){
			transfer_limit=transfer_limit-transfer_amount;
		};
		//transaction fee is reimboursed as transaction is denied
		if(this->current_account->GetAccountType()=="S"){
			current_account->SetBalance(current_balance+0.05);
		}else{
			current_account->SetBalance(current_balance+0.10);
		}
			Utilities::Prompt("Transaction fee not deducted.");
	}
}else{
Utilities::Prompt("Transaction unsuccessful. Account is disabled.");
transaction=Utilities::Prompt("Enter next transaction: ",transaction_acceptions);
TransactionCall(transaction);
}
}

void AccountManager::Paybill(){
//paybill amount from account to company

	if(session_type=="admin"){

		bool input_valid=false;
		while(input_valid==false){
			account_name = Utilities::Prompt("Please Enter the Name of the Account Holder: ","[A-z\\s]{1,20}");

			current_account = Utilities::GetAccountFromName(account_name,accounts_in_file);

			if (this->current_account == nullptr){
				Utilities::Prompt("Invalid Account Name.");
			}else{
				//if account name is valid then prompts next transaction
				Utilities::Prompt("Valid Account Name.");
				input_valid=true;
			}
		}
	}

	//prompts account number; if invalid prompts again
		bool input_number_valid=false;
		while(input_number_valid==false){
			account_number =(Utilities::Prompt("Please Enter the Account Number: ","\\d{5}"));

			if (account_number != this->current_account->GetAccountNumber()){
				Utilities::Prompt("Input Account Number is invalid.");
			}else{
				input_number_valid=true;
			}
		}

	string company_paidto = "";
	company_paidto=Utilities::Prompt("Please Enter the Company initial paid to: ","[A-z]{2}");

	double amount_to_pay = 0;
	while(amount_to_pay<=0){
			amount_to_pay=stod(Utilities::Prompt("Please Enter the Amount to pay ","\\d{5}\\.\\d{2}|\\d{1}\\.\\d{2}|\\.\\d{2}"));
			Utilities::Prompt("Amount should be more than 0$");
	}

	double current_balance = this->current_account->GetBalance();

	if(this->current_account->GetAccountStatus()=="A"){
		//transaction fee is charged
		if(this->current_account->GetAccountType()=="S"){
			current_account->SetBalance(current_balance-0.05);
		}else{
			current_account->SetBalance(current_balance-0.10);
		}
		if(session_type=="standard"){
		paybill_limit=paybill_limit+amount_to_pay;
		}
		if(session_type=="admin"||paybill_limit<2000){
			if (current_balance > amount_to_pay){
				//paybill amount to company (update account balance)
				current_account->SetBalance(current_balance-amount_to_pay);
				Utilities::Prompt("Transaction successful.");

				Utilities::Prompt("Transaction fee deducted.");

				//adds paybill transaction information in transactions_log list
				this->transactions_log.append("03 "+this->current_account->GetAccountName()+" "+(this->current_account->GetAccountNumber())+" "+to_string(amount_to_pay)+" "+this->current_account->GetAccountType()+"\n");

				transaction=Utilities::Prompt("Enter next transaction: ",transaction_acceptions);
				TransactionCall(transaction);
			}
		}else{
			Utilities::Prompt("Paybill unsuccessful.");
			transaction=Utilities::Prompt("Enter next transaction: ",transaction_acceptions);
			TransactionCall(transaction);

			if(session_type=="standard"){
			paybill_limit=paybill_limit-amount_to_pay;
			}

			//transaction fee is reimboursed as transaction is denied
			if(this->current_account->GetAccountType()=="S"){
				current_account->SetBalance(current_balance+0.05);
			}else{
				current_account->SetBalance(current_balance+0.10);
			}
				Utilities::Prompt("Transaction fee not deducted.");
		}
}else{
	Utilities::Prompt("Transaction unsuccessful. Account is already disabled.");
	transaction=Utilities::Prompt("Enter next transaction: ",transaction_acceptions);
	TransactionCall(transaction);
	}
}

void AccountManager::Deposit(){
//deposit amount into account

	if(session_type=="admin"){

		bool input_valid=false;
		while(input_valid==false){
			account_name = Utilities::Prompt("Please Enter the Name of the Account Holder: ","[A-z\\s]{1,20}");

			current_account = Utilities::GetAccountFromName(account_name,accounts_in_file);

			if (this->current_account == nullptr){
				Utilities::Prompt("Invalid Account Name.");
			}else{
				//if account name is valid then prompts next transaction
				Utilities::Prompt("Valid Account Name.");
				input_valid=true;
			}
		}
	}

	//prompts account number; if invalid prompts again
		bool input_number_valid=false;
		while(input_number_valid==false){
			account_number = (Utilities::Prompt("Please Enter the Account Number: ","\\d{5}"));

			if (account_number != this->current_account->GetAccountNumber()){
				Utilities::Prompt("Input Account Number is invalid.");
			}else{
				input_number_valid=true;
			}
		}

	double amount_deposit = 0;
	while(amount_deposit<=0){
		amount_deposit=stod(Utilities::Prompt("Please Enter the Amount to deposit: ","\\d{5}\\.\\d{2}|\\d{1}\\.\\d{2}|\\.\\d{2}"));
		Utilities::Prompt("Amount should be more than 0$");
	}


	double current_balance = this->current_account->GetBalance();

	if(this->current_account->GetAccountStatus()=="A"){
		//transaction fee is charged
		if(this->current_account->GetAccountType()=="S"){
			current_account->SetBalance(current_balance-0.05);
		}else{
			current_account->SetBalance(current_balance-0.10);
		}

		if (current_balance <99999.99){
			//deposit amount (update account balance)
			current_account->SetBalance(current_balance+amount_deposit);
			Utilities::Prompt("Transaction successful.");

			Utilities::Prompt("Transaction fee deducted.");

			//adds deposit transaction information in transactions_log list
			this->transactions_log.append("04 "+this->current_account->GetAccountName()+" "+(this->current_account->GetAccountNumber())+" "+to_string(amount_deposit)+" "+this->current_account->GetAccountType()+"\n");

			transaction=Utilities::Prompt("Enter next transaction: ",transaction_acceptions);
			TransactionCall(transaction);

		}else{
			Utilities::Prompt("Insufficient funds.");
			transaction=Utilities::Prompt("Enter next transaction: ",transaction_acceptions);
			TransactionCall(transaction);}

			//transaction fee is reimboursed as transaction is denied
			if(this->current_account->GetAccountType()=="S"){
				current_account->SetBalance(current_balance+0.05);
			}else{
				current_account->SetBalance(current_balance+0.10);
			}

			Utilities::Prompt("Transaction fee not deducted.");
	}else{
		Utilities::Prompt("Transaction unsuccessful. Account is already disabled.");
		transaction=Utilities::Prompt("Enter next transaction: ",transaction_acceptions);
		TransactionCall(transaction);
		}
}


void AccountManager::CreateAccount(){
//create new account with unique account number

	if(session_type=="admin"){
		account_name = Utilities::Prompt("Please Enter the Name of the Account Holder: ","[A-z\\s]{1,20}");

		//initial balance
		double account_balance = 0;
		account_balance=stod(Utilities::Prompt("Please Enter the intial Account Balance: ","\\d{5}\\.\\d{2}|\\d{1}\\.\\d{2}|\\.\\d{2}"));

		//create account with unique Account Number; go through account numbers in accounts & select unique account number
		Account* account_verify;
		bool account_number_valid=false;
		string new_account_number;
		while(account_number_valid==false){
		srand(time(NULL));
		int random_number=(rand()%10000)+1;
		new_account_number=to_string(random_number);
		if(new_account_number.size()<5)
		{
			switch (new_account_number.size()) {
				  case 1:
						new_account_number="0000"+new_account_number;
						break;
				  case 2:
						new_account_number="000"+new_account_number;
						break;
				  case 3:
				    new_account_number="00"+new_account_number;
				    break;
				  case 4:
				    new_account_number="0"+new_account_number;
						break;
  			}
		}
	account_verify = Utilities::GetAccountFromNumber(new_account_number,accounts_in_file);

		if (account_verify == nullptr){
			account_number_valid=true;
		}
	}
		Utilities::Prompt("Transaction successful. Account created");

		//adds account information in transactions_log list
		this->transactions_log.append("05 "+account_name+" "+(new_account_number)+" "+to_string(account_balance)+" "+"N"+"\n");

		transaction=Utilities::Prompt("Enter next transaction: ",transaction_acceptions);
		TransactionCall(transaction);
	}else{
		Utilities::Prompt("Transaction unsuccessful. Priviledge transactions are accepted in admin login session");
		transaction=Utilities::Prompt("Enter next transaction: ",transaction_acceptions);
		TransactionCall(transaction);
	}
}

void AccountManager::DeleteAccount(){
//delete account from system

	if(session_type=="admin"){

		bool input_valid=false;
		while(input_valid==false){
			account_name = Utilities::Prompt("Please Enter the Name of the Account Holder: ","[A-z\\s]{1,20}");
			current_account = Utilities::GetAccountFromName(account_name,accounts_in_file);

			if (this->current_account == nullptr){
				 Utilities::Prompt("Invalid Account Name.");
			}else{
				//if account name is valid then prompts next transaction
				 Utilities::Prompt("Valid Account Name.");
				input_valid=true;
			}
		}

		//prompts account number; if invalid prompts again
		bool input_number_valid=false;
		while(input_number_valid==false){
			account_number = (Utilities::Prompt("Please Enter the Account Number: ","\\d{5}"));

			if (account_number != this->current_account->GetAccountNumber()){
				 Utilities::Prompt("Input Account Number is invalid.");
			}else{
				input_number_valid=true;
			}
		}

	//delete account from accounts list
	for (auto it = accounts_in_file.begin(); it != accounts_in_file.end();) {
		if (it->GetAccountNumber() == current_account->GetAccountNumber()) {
			accounts_in_file.erase(it);
			break;
		} else {
			++it;
		}
	}

	Utilities::Prompt("Transaction successful. Account deleted");

	//if account deleted; add deleted account information in transactions_log list
	this->transactions_log.append("06 "+this->current_account->GetAccountName()+" "+(this->current_account->GetAccountNumber())+" "+"      "+this->current_account->GetAccountType()+"\n");

	transaction=Utilities::Prompt("Enter next transaction: ",transaction_acceptions);
	TransactionCall(transaction);
}else{
		Utilities::Prompt("Transaction unsuccessful. Priviledge transactions are accepted in admin login session");
		transaction=Utilities::Prompt("Enter next transaction: ",transaction_acceptions);
		TransactionCall(transaction);
	}
	}



void AccountManager::EnableAccount(){
//enabe account; account status from D to A

	if(session_type=="admin"){

	  bool input_valid=false;
		while(input_valid==false){
			account_name = Utilities::Prompt("Please Enter the Name of the Account Holder: ","[A-z\\s]{1,20}");

			current_account = Utilities::GetAccountFromName(account_name,accounts_in_file);

			if (this->current_account == nullptr){
				 Utilities::Prompt("Invalid Account Name.");
			}else{
				//if account name is valid then prompts next transaction
				 Utilities::Prompt("Valid Account Name.");
				input_valid=true;
			}
		}

		//prompts account number; if invalid prompts again
		bool input_number_valid=false;
		while(input_number_valid==false){
			account_number = (Utilities::Prompt("Please Enter the Account Number: ","\\d{5}"));

			if (account_number != this->current_account->GetAccountNumber()){
				Utilities::Prompt("Input Account Number is invalid.");
			}else{
				input_number_valid=true;
			}
		}

		if(this->current_account->GetAccountStatus()=="D"){
				//enabe account; account status from D to A in accounts list
				current_account->SetAccountStatus("A");
			}else{
				Utilities::Prompt("Transaction unsuccessful. Account is already active.");
				transaction=Utilities::Prompt("Enter next transaction: ",transaction_acceptions);
				TransactionCall(transaction);
			}

			Utilities::Prompt("Transaction successful. Account Enabled");

		//if account enabled; add enabed account information in transactions_log list
		this->transactions_log.append("09 "+this->current_account->GetAccountName()+" "+(this->current_account->GetAccountNumber())+" "+to_string(this->current_account->GetBalance())+" "+this->current_account->GetAccountStatus()+"\n");

		transaction=Utilities::Prompt("Enter next transaction: ",transaction_acceptions);
		TransactionCall(transaction);
	}else{
			Utilities::Prompt("Transaction unsuccessful. Priviledge transactions are accepted in admin login session");
			transaction=Utilities::Prompt("Enter next transaction: ",transaction_acceptions);
			TransactionCall(transaction);
		}
	}


void AccountManager::DisableAccount(){
//disable account; account status from A to D

	if(session_type=="admin"){

	  bool input_valid=false;
		while(input_valid==false){
			account_name = Utilities::Prompt("Please Enter the Name of the Account Holder: ","[A-z\\s]{1,20}");

			current_account = Utilities::GetAccountFromName(account_name,accounts_in_file);

			if (this->current_account == nullptr){
								 Utilities::Prompt("Invalid Account Name.");
			}else{
				//if account name is valid then prompts next transaction
			 Utilities::Prompt("Valid Account Name.");
				input_valid=true;
			}
		}

		//prompts account number; if invalid prompts again
		bool input_number_valid=false;
		while(input_number_valid==false){
			account_number = (Utilities::Prompt("Please Enter the Account Number: ","\\d{5}"));

			if (account_number != this->current_account->GetAccountNumber()){
				Utilities::Prompt("Input Account Number is invalid.");
			}else{
				input_number_valid=true;
			}
		}

	if(this->current_account->GetAccountStatus()=="A"){
			//disable account; account status from A to D
			current_account->SetAccountStatus("D");
		}else{
			Utilities::Prompt("Transaction unsuccessful. Account is already disabled.");
			transaction=Utilities::Prompt("Enter next transaction: ",transaction_acceptions);
			TransactionCall(transaction);
		}

		Utilities::Prompt("Transaction successful. Account disabled");

		//if account disabled; add disabled account information in transactions_log list
		this->transactions_log.append("07 "+this->current_account->GetAccountName()+" "+(this->current_account->GetAccountNumber())+" "+to_string(this->current_account->GetBalance())+" "+this->current_account->GetAccountStatus()+"\n");

		transaction=Utilities::Prompt("Enter next transaction: ",transaction_acceptions);
		TransactionCall(transaction);
	}else{
			Utilities::Prompt("Transaction unsuccessful. Priviledge transactions are accepted in admin login session");
			transaction=Utilities::Prompt("Enter next transaction: ");
			TransactionCall(transaction);
		}
	}


void AccountManager::ChangePlan(){
//account plan change; student or non-student (S/N)

	if(session_type=="admin"){

	  bool input_valid=false;
		while(input_valid==false){

			account_name = Utilities::Prompt("Please Enter the Name of the Account Holder: ","[A-z\\s]{1,20}");

			current_account = Utilities::GetAccountFromName(account_name,accounts_in_file);

			if (this->current_account == nullptr){
					 Utilities::Prompt("Invalid Account Name.");
			}else{
				//if account name is valid then prompts next transaction
				 Utilities::Prompt("Valid Account Name.");
				input_valid=true;
			}
		}

		//prompts account number; if invalid prompts again
		bool input_number_valid=false;
		while(input_number_valid==false){
			account_number =(Utilities::Prompt("Please Enter the Account Number: ","\\d{5}"));

			if (account_number != this->current_account->GetAccountNumber()){
				Utilities::Prompt("Input Account Number is invalid.");
			}else{
				input_number_valid=true;
			}
		}

		//account plan is changed depending on their current plan
		if(current_account->GetAccountType()=="S"){
				current_account->SetAccountType("N");
		}else{
			current_account->SetAccountType("S");
		}

		Utilities::Prompt("Transaction successful. Account type changed");

		//if account plan is changed; add account plan information in transactions_log list
		this->transactions_log.append("08 "+this->current_account->GetAccountName()+" "+(this->current_account->GetAccountNumber())+" "+to_string(this->current_account->GetBalance())+" "+this->current_account->GetAccountType()+"\n");

		transaction=Utilities::Prompt("Enter next transaction: ",transaction_acceptions);
		TransactionCall(transaction);
		}else{
			Utilities::Prompt("Transaction unsuccessful. Priviledge transactions are accepted in admin login session");
			transaction=Utilities::Prompt("Enter next transaction: ",transaction_acceptions);
			TransactionCall(transaction);
		}
	}



void AccountManager::Logout(){
	//end session
	withdrawal_limit=0;
	transfer_limit=0;
	paybill_limit=0;

	//adds logout information in transactions_log list
	this->transactions_log.append("00 "+this->current_account->GetAccountName()+" "+(this->current_account->GetAccountNumber())+" "+"      "+this->current_account->GetAccountType()+"\n");

	//output transaction file log
	fstream outfile;
	outfile.open(transaction_file_name);
	outfile << this->transactions_log << endl;
	outfile.close();

	Utilities::Prompt("Logout successful.");
	transaction=Utilities::Prompt("Enter next transaction: ",{"login|Login"});
	Utilities::Prompt("Login successful.");
	Login();

}

//calls appropriate funstion to proceed transaction, if invalid transaction input then prompts to input next transaction again
void AccountManager::TransactionCall(string transaction_request){

	bool transaction_valid=false;

	while(transaction_valid==false){

		if(transaction_request=="withdrawal"||transaction_request=="Withdrawal"){
			 Withdrawal();
			 transaction_valid=true;
		}else if(transaction_request=="transfer"||transaction_request=="Transfer"){
			 Transfer();
			 transaction_valid=true;
		}else	if(transaction_request=="paybill"||transaction_request=="Paybill"){
			 Paybill();
			 transaction_valid=true;
		}else if(transaction_request=="deposit"||transaction_request=="Deposit"){
			Deposit();
			transaction_valid=true;
		}else if(transaction_request=="create"||transaction_request=="Create"){
			CreateAccount();
			transaction_valid=true;
		}else if(transaction_request=="delete"||transaction_request=="Delete"){
			DeleteAccount();
			transaction_valid=true;
		}else if(transaction_request=="enable"||transaction_request=="Enable"){
			EnableAccount();
			transaction_valid=true;
		}else if(transaction_request=="disable"||transaction_request=="Disable"){
			DisableAccount();
			transaction_valid=true;
		}else if(transaction_request=="changeplan"||transaction_request=="Changeplan"){
			ChangePlan();
			transaction_valid=true;
		}else if(transaction_request=="logout"||transaction_request=="Logout"){
				Logout();
				transaction_valid=true;
		}else{
			Utilities::Prompt("Transaction invalid. Transaction options:withdrawal,transfer,paybill,deposit,create,delete,enable,disable,changeplan,logout.");
			transaction=Utilities::Prompt("Enter next transaction: ");
			TransactionCall(transaction);
		}
	}
}

int AccountManager::main(int argc, char *argv[]){
	string accounts_file_name;

	//reads command line arguments and stores file names
	if (argc == 3) {
		 accounts_file_name=argv[1];
		  transaction_file_name=argv[2];
	 } else {
		 Utilities::Prompt("Usage: banksystem <accounts file> <transation file>");
		 return -1;
	 }


	//loads accounts information from current accounts file
	this->accounts_in_file = Utilities::LoadAccountInformation(accounts_file_name);

	//prompts to enter transaction and if input is different than login, prompts again to login
		transaction=Utilities::Prompt("Enter transaction to begin: ",{"login|Login"});
		Utilities::Prompt("Login successful.");
		Login();



	return 0;
}
