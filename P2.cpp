 #include <string>
 #include <vector>
 #include <fstream>
 #include <cstring>
 #include <cstdlib>
 #include <iterator>
 #include <iostream>
 #include <sstream>
 #include <istream>
 #include <fstream>

 using namespace std;

 // account has no dependancy on client, client has an aggregation of these
 // friends!
 string stringify(int in);

 const string CLIENT_FILE = "client.txt";
 const string ACCOUNT_FILE = "account.txt";
 const string STAFF_FILE = "staff.txt";

 class Account {
  public:
    //Account(string nameIn, int balIn, int numIn, Client& clientIn);
    Account(string nameIn, int balIn, int numIn);
    void setBalance(int balIn);
    int getBalance();
    void setAccount(int in);
    int getAccount();
    //void setClient(Client in);
    //Client* getClient();
    void setName(string nameIn);
    string getName();
	string toString();
	//bool hasClient();
  private:
    int balance;
    int accountNumber;
    //Client* accClient;
    string name;
 };

 class Staff {
	public:
		Staff(string nameIn, bool type, string pIn);
		string getUsername();
		bool getAccess();
		string getPassword();
		string toString();
		void changePassword(string in) {password = in;};
		void changeUser(string in) {username = in;};
	private:
		string username;
		bool access;
		string password;
 };

 class Client {
	public:
		Client(string nIn, string addIn, string socialIn, string employerIn, int annIncIn);
		//Client(string nIn, string addIn, string socialIn, string employerIn, int annIncIn, vector<Account>& accIn);

		void setName(string nameIn);
		string getName();
		void setAddress(string addIn);
		string getAddress();
		void setSocial(string socialIn);
		string getSocial();
		void setEmployer(string employerIn);
		string getEmployer();
		void setIncome(int incIn);
		int getIncome();

		void addAccount(Account accIn);
		bool removeAccount(Account accIn);
		string getAccounts();

		string toString();

	private:
		string name;
		string address;
		string social;
		string employer;
		int annIncome;

		vector<Account> array;
 };

 //needs work
 class CASystem {
	public:
		void display();
		bool initialize();
		bool save();
		bool login(string user, string pass);
		bool getStaffAccess(string user);
	private:
		ifstream clientInStream;
		ifstream accountInStream;
		ifstream staffInStream;
		ofstream clientOutStream;
		ofstream accountOutStream;
		ofstream staffOutStream;
		vector<Client> cArray;
		vector<Account> aArray;
		vector<Staff> sArray;
		bool openfile(ifstream& ins, string fin);
		void readFiles();
		void updateFiles();

 };

 class Menu {
	public:
		void runner();
	private:
		void startup(bool access);
		void accountManagement();
		void staffManagement();
 };



 /*** Main Code ***/

 int main() {
	Menu theMenu;
	theMenu.runner();
 }




  /****************************************************
  *                   Client implementation           *
  ****************************************************/
 Client::Client(string nIn, string addIn, string socialIn, string employerIn, int annIncIn) {
 	 setName(nIn);
	 setAddress(addIn);
	 setSocial(socialIn);
	 setEmployer(employerIn);
	 setIncome(annIncIn);
 }

 void Client::setName(string nameIn) {
	name = nameIn;
 }
 string Client::getName() {
 	 return name;
 }
 void Client::setAddress(string addIn) {
 	 address = addIn;
 }
 string Client::getAddress() {
 	 return address;
 }
 void Client::setSocial(string socialIn) {
 	 social = socialIn;
 }
 string Client::getSocial() {
 	 return social;
 }
 void Client::setEmployer(string employerIn) {
 	 employer = employerIn;
 }
 string Client::getEmployer() {
 	 return employer;
 }
 void Client::setIncome(int incIn) {
 	 annIncome = incIn;
 }
 int Client::getIncome() {
 	 return annIncome;
 }

 void Client::addAccount(Account accIn) {
 	 array.push_back(accIn);
 }
 bool Client::removeAccount(Account accIn) {
	 for (int i = 0; i < array.size(); i++) {
		if(accIn.getAccount() == array[i].getAccount()) {
			array.erase(array.begin()+i);
			return true;
		}
	 }
	 return false;
 }
 string Client::getAccounts() {
 	 for (int i = 0; i < array.size(); i++) {
	 	 cout << array[i].getName()<<": Number "<< array[i].getAccount() << endl;
	 }
 }

 string Client::toString() {
	 string out;
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
  /****************************************************
  *               Account implementation              *
  ****************************************************/
 Account::Account(string nameIn, int balIn, int numIn) {
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
 void Account::setName(string nameIn) {
    name = nameIn;
 }

 string Account::getName() {
	return name;
 }

 string Account::toString() {
	 string out;
	 out += "Name: " + Account::getName() + "\n";
	 out += "Balance: " + stringify(Account::getBalance()) + "\n";
	 out += "Account Num: " + stringify(Account::getAccount()) + "\n\n";
	 return out;

 }

 string stringify(int in) {
 	 ostringstream os;
	 os << in;
	 return os.str();
 }

 /******************************************************
  *                 CASystem implementation            *
  ******************************************************/
  bool CASystem::initialize() {
	 bool file_open = (openfile(clientInStream, CLIENT_FILE) && openfile(accountInStream, ACCOUNT_FILE) && openfile(staffInStream, STAFF_FILE));
	 // if files didn't open, exit!
	 if (!file_open) {
	 	 return false;
	 }
	 readFiles();
	 return true;

 }
 bool CASystem::save() {}

 // will open a file!
 bool CASystem::openfile(ifstream& ins, string fin) {
	ins.open((char*)fin.c_str());
	if (ins.fail()) {
		return false;
	}
	return true;
 }

 // reads files after opening!
 void CASystem::readFiles() {
	 //vector<int> tempAccountNumbers; //holds account numbers and prepares
	 // accounts
	 while (!accountInStream.eof()) {
	 	 string nameIn, balanceIn, accountNumIn;
		 int balIn, accIn;
		 // begin data grab
		 getline(accountInStream, accountNumIn); //acc num in
		 getline(accountInStream, balanceIn); //balance in
		 getline(accountInStream, nameIn); //name in

		 //convert str to int
		 balIn = atoi(balanceIn.c_str());
		 accIn = atoi(accountNumIn.c_str());

		 aArray.push_back(Account(nameIn, balIn, accIn));
	 }
	 aArray.erase(aArray.end());
	 accountInStream.close(); //close stream


 	 // clients
	 
	 while (!clientInStream.eof()) {
	 	 string nameIn, addressIn, socialIn, employerIn, incomeStr, accounts;
		 int incomeIn;
		 // begin data grab
		 getline(clientInStream, nameIn, '\n'); //name
		 getline(clientInStream, addressIn, '\n'); //address
		 getline(clientInStream, socialIn, '\n'); //social
		 getline(clientInStream, employerIn, '\n'); //employer
		 getline(clientInStream, incomeStr, '\n'); //income
		 getline(clientInStream, accounts, '\n'); //accounts
		 //convert str to int
		 incomeIn = atoi(incomeStr.c_str());
		 //create a client
		 //cout << "yay";


		 Client nextIn(nameIn, addressIn, socialIn, employerIn, incomeIn);
		 //seperate accounts into tokens!
		 vector<int> accNums;
		 vector<Account> accActual;
		 stringstream parse(accounts);
		 string num;
		 while(getline(parse,num,' ')) {
		 	 accNums.push_back(atoi(num.c_str())); //NOW ALL OF THEM ARE NUMS
		 }

		 for (int i = 0; i < accNums.size(); i++) {
		 	 //search for the account!
			 for (int n = 0; n < aArray.size(); n++) {
			 	 if (aArray[n].getAccount() == accNums[i]) {
				 	 //account numbers match!
					 nextIn.addAccount(Account(aArray[n].getName(), aArray[n].getBalance(), aArray[n].getAccount()));
				 }
			 }
		 }

		  
		 cArray.push_back(nextIn);
	 }
	 clientInStream.close(); //close the file

	 while (!staffInStream.eof()) {
	 	 string nameIn, passIn, typeIn;
		 //int pass;
		 bool type;
		 // begin data grab
		 getline(staffInStream, nameIn); //acc num in
		 getline(staffInStream, passIn); //balance in
		 getline(staffInStream, typeIn); //name in

		 //convert str to int
		 //pass = atoi(passIn.c_str());
		 type = atoi(typeIn.c_str()); //0 for admin, 1 for branch

		 sArray.push_back(Staff(nameIn, type, passIn));
	 }
	 sArray.erase(sArray.end());
	 staffInStream.close(); //close stream

 }

 void CASystem::updateFiles() {}
 void CASystem::display() {
	//print clients and then accounts!
	for (int i = 0; i < cArray.size(); i++) {
		cout << cArray[i].toString() << endl << "ACCOUNTS ATTACHED: \n" << cArray[i].getAccounts() << endl;
	}
	
	for (int i = 0; i < sArray.size(); i++) {
		cout << sArray[i].toString() << endl << endl;
	}
 }

 bool CASystem::login(string user, string pass) {
	 //cout << "\nArray size: " << sArray.size() << endl << endl;
	 user.erase(user.find_last_not_of(" \n\r\t")+1);
	 pass.erase(pass.find_last_not_of(" \n\r\t")+1);
	 string checkUser, checkPass;
 	 for (vector<Staff>::iterator i = sArray.begin(); i != sArray.end(); ++i) {
		 checkUser = i-> getUsername();
		 checkPass = i-> getPassword();
		 checkUser.erase(checkUser.find_last_not_of(" \n\r\t")+1);
		 checkPass.erase(checkPass.find_last_not_of(" \n\r\t")+1);
		 //cout << "\n\nComparing: " << user << " to " << checkUser << endl << endl;
	 	 if (user.compare(checkUser) == 0) {
			 //cout << "\n\nYOU MADE IT HERE\n\n";
		 	 //check password
			 //cout << sArray[i].getPassword();
			 if (pass.compare(checkPass) == 0) {
			 	 return true;
			 }
			 return false;
		 }
	 }
	 return false;
 }

 bool CASystem::getStaffAccess(string user) {
	 user.erase(user.find_last_not_of(" \n\r\t")+1);
 	 for (int i = 0; i < sArray.size(); i++) {
	 	 if (user.compare(sArray[i].getUsername()) == 0) {
		 	 return sArray[i].getAccess();
		 }
	 }
	 return false;
 }

 /******************************************************
  *                 Staff implementation                *
  ******************************************************/
 Staff::Staff(string nameIn, bool type, string pIn) {
 	 username = nameIn;
	 access = type;
	 password = pIn;
 }

 string Staff::getUsername() {
 	 return username;
 }

 string Staff::getPassword() {
 	 return password;
 }

 bool Staff::getAccess() {
 	 return access;
 }

 

 string Staff::toString() {
	string out;
	out = "Username: " + username + "\n";
	out += "Access: ";
	if (getAccess()) {
		out += "Branch manager\n";
	} else {
		out += "Admin\n";
	}
	out += "Password: " + password + "\n";
	return out;
 }

  /******************************************************
  *                 Menu implementation                 *
  ******************************************************/

 void Menu::runner() {
	string out = "\t===========================================================\n";
	      out += "\t|       Welcome to the Auburn Branch of Tiger Bank!       |\n";
		  out += "\t===========================================================\n";
		  out += "1)  Login\n";
		  out += "2)  Quit\n";
	string prompt = "\tPlease choose an option: ";
	cout << out << prompt;
	bool validInput = false;
	string answer;
	while (!validInput) {
		//cin.ignore();
		getline(cin, answer);
		if (answer.compare("1") == 0 || answer.compare("2") == 0) {
			validInput = true;
		} else {
			cout << "Invalid input, please try again.\n";
			cout << prompt;
		}
	}
	int inputNum = atoi(answer.c_str());
	if (inputNum == 2) {
		exit(0);
	}
	//load all files!
	CASystem sysrunner;
	sysrunner.initialize();
	string logOut = "\t===========================================================\n";
	      logOut += "\t|            Login to Access the Teller System            |\n";
		  logOut += "\t===========================================================\n";
	cout << logOut << "Username: ";
	string user, pass;
	getline(cin, user, '\n');
	cout << "Password: ";
	getline(cin, pass, '\n');
    //cout << "\nEntered user: " << user << "\nEntered Pass: " << pass << endl << endl;
	validInput = sysrunner.login(user,pass);
	//cout << pass << " " << user;
	while (!validInput) {
    //cout << "Is this even working?";
		if (!sysrunner.login(user, pass)) {
			cout << "The username or password is incorrect. Try again!\nUsername: ";
			getline(cin, user, '\n');
			cout << "Password: ";
			getline(cin, pass, '\n');
			//cout << pass << " " << user;
		} else {
			validInput = true;
		}
	}
	bool acc = sysrunner.getStaffAccess(user);
	startup(acc);


	//now we are in business!
	//sysrunner.display();
  }


 void Menu::startup(bool access) {
	if (!access) {
		cout << "Admin access:";
	} else {
		cout << "Branch access";
	}
 }
 void Menu::accountManagement() {

 }
 void Menu::staffManagement() {

 }
