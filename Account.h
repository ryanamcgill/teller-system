/***********************************************************************
 * Ryan McGill                                                         *
 * RAM0063                                                             *
 * Account.h                                                            *
 ***********************************************************************/


 #ifndef ACCOUNT_H
 #define ACCOUNT_H
 #include "Client.h"
 #include <string>
 #include <vector>

 class Client;

 class Account {
	public:
		//Account(std::string nameIn, int balIn, int numIn, Client& clientIn);
		Account(std::string nameIn, int balIn, int numIn);
		void setBalance(int balIn);
		int getBalance();
		void setAccount(int in);
		int getAccount();
		void setClient(Client& in);
		Client getClient();
		void setName(std::string nameIn);
		std::string getName();
	private:
		int balance;
		int accountNumber;
		Client accClient;
		std::string name;
 };

 #endif
