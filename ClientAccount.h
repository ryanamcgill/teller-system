/***********************************************************************
 * Ryan McGill                                                         *
 * RAM0063                                                             *
 * ClientAccount.h                                                     *
 ***********************************************************************/


 #ifndef CLIENTACCOUNT_H
 #define CLIENTACCOUNT_H
 #include <string>
 #include <vector>

 // account has no dependancy on client, client has an aggregation of these
 // friends!
 std::string stringify(int in);

 class Account {
  public:
    //Account(std::string nameIn, int balIn, int numIn, Client& clientIn);
    Account(std::string nameIn, int balIn, int numIn);
    void setBalance(int balIn);
    int getBalance();
    void setAccount(int in);
    int getAccount();
    //void setClient(Client in);
    //Client* getClient();
    void setName(std::string nameIn);
    std::string getName();
	std::string toString();
	//bool hasClient();
  private:
    int balance;
    int accountNumber;
    //Client* accClient;
    std::string name;
 };


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

		std::string toString();

	private:
		std::string name;
		std::string address;
		std::string social;
		std::string employer;
		int annIncome;

		std::vector<Account> array;
 };

 #endif
