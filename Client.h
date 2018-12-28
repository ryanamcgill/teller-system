/***********************************************************************
 * Ryan McGill                                                         *
 * RAM0063                                                             *
 * Client.h                                                            *
 ***********************************************************************/


 #ifndef CLIENT_H
 #define CLIENT_H
 #include "Account.h"
 #include <string>
 #include <vector>

 class Account;

 class Client {
	public:
		Client(std::string nIn, std::string addIn, std::string socialIn, std::string employerIn, int annIncIn);
		//Client(std::string nIn, std::string addIn, std::string socialIn, std::string employerIn, int annIncIn, std::vector<Account>& accIn);

		void setName(std::string nameIn);
		std::string getName();
		void setAddress(std::string addIn);
		std::string getAddress();
		void setSocial(std::string socialIn);
		std::string getSocial();
		void setEmployer(std::string employerIn);
		std::string getEmployer();
		void setIncome(int incIn);
		int getIncome();

		void addAccount(Account& accIn);
		bool removeAccount(Account& accIn);
		std::string getAccounts();

	private:
		std::string name;
		std::string address;
		std::string social;
		std::string employer;
		int annIncome;

		std::vector<Account> array;
 };

 #endif
