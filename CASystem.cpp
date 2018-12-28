/***********************************************************************
 * Ryan McGill                                                         *
 * RAM0063                                                             *
 * CASystem.cpp                                                        *
 *
 *
 * www.fluentcpp.com/2017/04/21/how-to-split-a-string-in-c used for 
 * seperating strings into tokens!
 ***********************************************************************/
 #include "CASystem.h"
 #include <string>
 #include <cstring>
 #include <cstdlib>
 #include <vector>
 #include <iterator>
 #include <iostream>
 #include <sstream> //for parsing


 
 bool CASystem::initialize() {
	 bool file_open = (openfile(clientInStream, CLIENT_FILE) && openfile(accountInStream, ACCOUNT_FILE));
	 // if files didn't open, exit!
	 if (!file_open) {
	 	 return false;
	 } 
	 readFiles();
	 return true;

 }
 bool CASystem::save() {}

 // will open a file!
 bool CASystem::openfile(std::ifstream& ins, std::string fin) {
	ins.open((char*)fin.c_str());
	if (ins.fail()) {
		return false;
	}
	return true;
 }

 // reads files after opening!
 void CASystem::readFiles() {
	 std::vector<int> tempAccountNumbers; //holds account numbers and prepares	
	 // accounts
	 while (!accountInStream.eof()) {
	 	 std::string nameIn, balanceIn, accountNumIn;
		 int balIn, accIn;
		 // begin data grab
		 std::getline(accountInStream, accountNumIn); //acc num in
		 std::getline(accountInStream, balanceIn); //balance in
		 std::getline(accountInStream, nameIn); //name in
		 
		 //convert str to int
		 balIn = atoi(balanceIn.c_str());
		 accIn = atoi(accountNumIn.c_str());
		 
		 aArray.push_back(Account(nameIn, balIn, accIn));
	 }
	 accountInStream.close(); //close stream

	 /*
 	 // clients
	 while (!clientInStream.eof()) {
	 	 std::string nameIn, addressIn, socialIn, employerIn, incomeStr, accounts;
		 int incomeIn;
		 // begin data grab
		 std::getline(clientInStream, nameIn, '\n'); //name
		 std::getline(clientInStream, addressIn, '\n'); //address
		 std::getline(clientInStream, socialIn, '\n'); //social
		 std::getline(clientInStream, employerIn, '\n'); //employer
		 std::getline(clientInStream, incomeStr, '\n'); //income
		 std::getline(clientInStream, accounts, '\n'); //accounts
		 //convert str to int
		 incomeIn = atoi(incomeStr.c_str());
		 //create a client
		 Client next(nameIn, addressIn, socialIn, employerIn, incomeIn);

		 //seperate accounts into tokens!
		 /***********************************************************
		  * This part of the code was inspired by the code found on *
		  * www.fluentcpp.com/2017/04/21/how-to-split-a-string-in-c *
		  ***********************************************************/
		  /*
		 std::vector<std::string> parse;
		 std::string del = " ";
		 size_t pos = 0;
		 while ((pos = accounts.find(del)) != std::string::npos) {
		 	 parse.push_back(accounts.substr(0, pos));
			 accounts.erase(0, pos + del.length());
		 }
		 for (int i = 0; i  < parse.size(); i++) {
		 	 std::cout << parse[i];
		 }
		 /*
		 //int s = parse.size();
		 for (int i = 0; i < parse.size(); i++) {
			int accNum = atoi(parse[i].c_str());
			//token is now an account number
			//find the account associated with the token
			for(int n = 0; n < aArray.size(); n++) {
				if (aArray[n].getAccount() == accNum) {
					//its a match!
					next.addAccount(aArray[n]);
					std::cout << "YOU MADE IT THIS FAR!";
				}
			}
		 }

		 cArray.push_back(next);
	 }*/
	 clientInStream.close(); //close the file
 }

 void CASystem::updateFiles() {}
 void CASystem::display() {
	//print clients and then accounts!
	for (int i = 0; i < cArray.size(); i++) {
		std::cout << cArray[i].toString() << std::endl << std::endl;
	}
 }