/***********************************************************************
 * Ryan McGill                                                         *
 * RAM0063                                                             *
 * Client.cpp                                                          *
 ***********************************************************************/
 #include "Client.h"
 #include "Account.h"
 #include <string>
 #include <vector>
 #include <iostream>


 Client::Client(std::string nIn, std::string addIn, std::string socialIn, std::string employerIn, int annIncIn) {
 	 setName(nIn);
	 setAddress(addIn);
	 setSocial(socialIn);
	 setEmployer(employerIn);
	 setIncome(annIncIn);
 }
/*
 Client::Client(std::string nIn, std::string addIn, std::string socialIn, std::string employerIn, int annIncIn, std::vector<Account>& accIn) {
 	 setName(nIn);
	 setAddress(addIn);
	 setSocial(socialIn);
	 setEmployer(employerIn);
	 setIncome(annIncIn);
	 array = accIn;
 }
*/
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
