/***********************************************************************
 * Ryan McGill                                                         *
 * RAM0063                                                             *
 * Account.cpp                                                       *
 ***********************************************************************/

 #include "Account.h"
 #include "Client.h"
 #include <string>

/*
 Account::Account(std::string nameIn, int balIn, int numIn, Client& clientIn) {
 	 setBalance(balIn);
	 setAccount(numIn);
	 setClient(clientIn);
	 setName(nameIn);
	 accClient = clientIn;
 }
*/
 Account::Account(std::string nameIn, int balIn, int numIn) {
 	 setBalance(balIn);
	 setAccount(numIn);
	 setName(nameIn);
 }

 void Account::setBalance(int balIn) {
	balance = balIn;
 }

 int Account::getBalance() {
 	 return balance;
 }

 void Account::setAccount(int in){
 	 accountNumber = in;
 }

 int Account::getAccount() {
 	 return accountNumber;
 }

 void Account::setClient(Client& in) {
	accClient = in;
 }

 Client Account::getClient() {
	return accClient;
 }

 void Account::setName(std::string nameIn) {
 	 name = nameIn;
 }

 std::string Account::getName() {
	return name;
 }
