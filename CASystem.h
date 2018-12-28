/***********************************************************************
 * Ryan McGill                                                         *
 * RAM0063                                                             *
 * CASystem.h                                                            *
 ***********************************************************************/


 #ifndef CASYSTEM_H
 #define CASYSTEM_H
 #include "ClientAccount.h"
 #include <string>
 #include <fstream>
 #include <vector>

 const std::string CLIENT_FILE = "client.txt";
 const std::string ACCOUNT_FILE = "account.txt";

 class CASystem {
	public:
		void display();
		bool initialize();
		bool save();
	private:
		std::ifstream clientInStream;
		std::ifstream accountInStream;
		std::ofstream clientOutStream;
		std::ofstream accountOutStream;
		std::vector<Client> cArray;
		std::vector<Account> aArray;
		bool openfile(std::ifstream& ins, std::string fin);
		void readFiles();
		void updateFiles();
 };

 #endif
