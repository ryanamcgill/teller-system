/***********************************************************************
 * Ryan McGill                                                         *
 * RAM0063                                                             *
 * ClientAccount.cpp                                                          *
 ***********************************************************************/
 #include "ClientAccount.h"
 #include <string>
 #include <vector>
 #include <iostream>
 #include <istream>
 #include <fstream>
 #include <sstream>

 /*************************
  * Client implementation *
  *************************/
 Client::Client(std::string nIn, std::string addIn, std::string socialIn, std::string employerIn, int annIncIn) {
 	 setName(nIn);
	 setAddress(addIn);
	 setSocial(socialIn);
	 setEmployer(employerIn);
	 setIncome(annIncIn);
 }

 void Client::setName(std::string nameIn) {
	name = nameIn;
 }
 std::string Client::getName() {
 	 return name;
 }
 void Client::setAddress(std::string addIn) {
 	 address = addIn;
 }
 std::string Client::getAddress() {
 	 return address;
 }
 void Client::setSocial(std::string socialIn) {
 	 social = socialIn;
 }
 std::string Client::getSocial() {
 	 return social;
 }
 void Client::setEmployer(std::string employerIn) {
 	 employer = employerIn;
 }
 std::string Client::getEmployer() {
 	 return employer;
 }
 void Client::setIncome(int incIn) {
 	 annIncome = incIn;
 }
 int Client::getIncome() {
 	 return annIncome;
 }

 void Client::addAccount(Account& accIn) {
 	 array.push_back(accIn);
 }
 bool Client::removeAccount(Account& accIn) {
	 for (int i = 0; i < array.size(); i++) {
		if(accIn.getAccount() == array[i].getAccount()) {
			array.erase(array.begin()+i);
			return true;
		}
	 }
	 return false;
 }
 std::string Client::getAccounts() {
 	 for (int i = 0; i < array.size(); i++) {
	 	 std::cout<<array[i].getName()<<std::endl;
	 }
 }

 std::string Client::toString() {
	 std::string out;
	 out += "Name: " + Client::getName() + "\n";
	 out += "Address: " + Client::getAddress() + "\n";
	 out += "Social: " + Client::getSocial() + "\n";
	 out += "Employer: " + Client::getEmployer() + "\n";
	 out += "Income: " + stringify(Client::getIncome()) + "\n\n";
	 out += "Accounts connected: ";
	 Client::getAccounts();
	 out += "\n\n";
	 return out;

 }
  /*************************
  * Account implementation *
  *************************/
 Account::Account(std::string nameIn, int balIn, int numIn) {
    setBalance(balIn);
	setAccount(numIn);
	setName(nameIn);
	//accClient = NULL;
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
 /*
 void Account::setClient(Client in) {
	accClient = &in;
 }
 
 Client* Account::getClient() {
	return accClient;
 }
 */
 void Account::setName(std::string nameIn) {
    name = nameIn;
 }

 std::string Account::getName() {
	return name;
 }

 std::string Account::toString() {
	 std::string out;
	 out += "Name: " + Account::getName() + "\n";
	 out += "Balance: " + stringify(Account::getBalance()) + "\n";
	 out += "Account Num: " + stringify(Account::getAccount()) + "\n\n";
	 return out;

 }

 std::string stringify(int in) {
 	 std::ostringstream os;
	 os << in;
	 return os.str();
 }

 /*
 bool Account::hasClient() {
	if (accClient == NULL) {
		return false;
	}
	return true;
 }
 */