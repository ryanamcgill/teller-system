 /***********************************************************************
 * Ryan McGill                                                         *
 * RAM0063                                                             *
 * Project2.cpp                                                        *
 *                                                                     *
 * How to Compile: 1) Download 'Project2.zip' and extract the files to *
 *                    a directory where you will be working.           *
 *                 2) Open up a bash script.                           *
 *                 3) Change directories to the folder where Project2.cpp
 *                    is located using the 'cd' command in the prompt. *
 *                 4) Compile the program into an executable by keying *
					g++ -o Project2 Project2.cpp					   *
 *                    at the prompt line.                              *
 *                 5) Execute the file by keying                       *
 *                      ./Project2                                     *
 *                    at the prompt line.                              *
 *																	   *
 *	The file reading in and out was derived from the class textbook
    (Absolute C++) as well as with guidance from a student who helped 
	me with stringstream operations. Pause_now and mygetch were used from
	the slides.														   *
 ***********************************************************************/ 
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
 #include <stdio.h>
 #include <termios.h>
 #include <unistd.h>
 #include <ctype.h>



 using namespace std;


 const string CLIENT_FILE = "client.txt";
 const string ACCOUNT_FILE = "account.txt";
 const string STAFF_FILE = "staff.txt";


 //struct definitions
 struct Account {
	string name;
	int balance; 
	int number;
 };
 //typedef Account *accPtr;


 struct Client {
	string name;
	string address; 
	string social; 
	string employer;
	int annualIncome;
	vector<Account> linkedAccounts;
 };
 //typedef Client *clientPtr;

 struct Staff {
	string name;
	bool access;
	string pass;
 };
 //typedef Staff *staffPtr;

 class CASystem {
	public:
		void display();
		bool initialize();
		bool login(string user, string pass);
		bool getAccess();
		void editCurrent();
		int findStaff(string in);
		int findClient(string in);
		int findAccount(int in);
	    void addBranch();
		void deleteBranch();
		void displayMembers();
		void saveUser();
		void editClient();
		void addClient();
		void addAccount();
		void saveAll();
		void manageAccount();
		//bool getStaffAccess(string user);
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
		Staff current;
 };

 class Menu {
	public:
		void startup();
	private:
		void accountManagement(CASystem& runnerIn);
		//void Menu::mainMenu(bool access) {
		void staffManagement();
 };

 //misc functions
 void clean(string &in);
 string stringify(int in);
 int mygetch(void);
 void pause_now(void);

 /******************************************************
 *                      Main implementation            *
 ******************************************************/
 int main() {
	Menu atmTeller;
	atmTeller.startup();
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

  /******************************************************
  * Student helped me with string stream and how to use
    it effectively!                                    *
  ******************************************************/
	 while (accountInStream.peek() != std::ifstream::traits_type::eof()) {
		 Account temp;
	 	 string nameIn, balanceIn, accountNumIn, line;
		 int balIn, accIn;

		 stringstream parser;
		 getline(accountInStream, line); //gets line!
		 parser.str(line); //puts into string stream

		 getline(parser, accountNumIn, '*'); //gets name up to *
		 getline(parser, balanceIn, '*');
		 getline(parser, nameIn);
		 //cout << balanceIn << " is the balance while " << nameIn << " is the name\n";
		 clean(accountNumIn);
		 clean(balanceIn);
		 clean(nameIn);

		 //convert str to int
		 balIn = atoi(balanceIn.c_str());
		 accIn = atoi(accountNumIn.c_str());
		 temp.name = nameIn;
		 temp.balance = balIn;
		 temp.number = accIn;
		 aArray.push_back(temp); 
	 }
	 //aArray.erase(aArray.end());
	 accountInStream.close(); //close stream
 	 // clients
	 
	 while (clientInStream.peek() != std::ifstream::traits_type::eof()) {
	 	 string nameIn, addressIn, socialIn, employerIn, incomeStr, accounts, line;
		 int incomeIn;
		 // begin data grab
		 stringstream parser;
		 getline(clientInStream, line); //gets line!
		 parser.str(line); //puts into string stream

		 getline(parser, nameIn, '*'); //gets name up to *
		 getline(parser, addressIn, '*');
		 getline(parser, socialIn, '*');
		 getline(parser, employerIn, '*');
		 getline(parser, incomeStr, '*');
		 getline(parser, accounts);

		 //convert str to int
		 incomeIn = atoi(incomeStr.c_str());
		 //create a client
		 //cout << "yay";
		 clean(nameIn);
		 clean(addressIn);
		 clean(socialIn);
		 clean(employerIn);
		 //clean(incomeStr);

		 Client nextIn;
		 nextIn.name = nameIn;
		 nextIn.address = addressIn; 
		 nextIn.social = socialIn; 
		 nextIn.employer = employerIn;
		 nextIn.annualIncome = incomeIn;
		 //cout << nextIn.name << " " << nextIn.address;
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
			 	 if (aArray[n].number == accNums[i]) {
				 	 //account numbers match!
					 nextIn.linkedAccounts.push_back(aArray[n]);
				 }
			 }
		 }

		  
		 cArray.push_back(nextIn);
	 }
	 clientInStream.close(); //close the file

	 while (staffInStream.peek() != std::ifstream::traits_type::eof()) {
	 	 string nameIn, passIn, typeIn, line;
		 //int pass;
		 bool type;
		 // begin data grab
		 stringstream parser;
		 getline(staffInStream, line); //gets line!
		 parser.str(line); //puts into string stream
		 getline(parser, nameIn, '*'); //gets name up to *
		 
		 getline(parser, passIn, '*');
		 getline(parser, typeIn);
		 //parser.ignore(50,'?');
		 //parser >> typeIn;
		 

		 //convert str to int
		 //pass = atoi(passIn.c_str());
		 type = atoi(typeIn.c_str()); //0 for admin, 1 for branch
		 Staff nextIn;
		 nextIn.name = nameIn;
	     nextIn.access = type;
	     nextIn.pass = passIn;
		 //cout << nextIn.name << " and " << nextIn.access << " and " << nextIn.pass;
		 sArray.push_back(nextIn);
	 }
	 //sArray.erase(sArray.end());
	 staffInStream.close(); //close stream
	 //display();
 }

 void CASystem::updateFiles() {}

 void CASystem::display() {
    cout << "Staff names: \n";
	for (int i = 0; i < sArray.size(); i++) {
		cout << sArray[i].name << " with pass " << sArray[i].pass << endl;
	}
	cout << "Client names: \n";
	for (int i = 0; i < cArray.size(); i++) {
		cout << cArray[i].name << " with address " << cArray[i].address << endl;
	}
	cout << "Account names: \n";
	for (int i = 0; i < cArray.size(); i++) {
		cout << aArray[i].name << " with number " << aArray[i].number << endl;
	}
 }

 bool CASystem::login(string user, string pass) {
	 clean(user);
	 clean(pass);
	 string checkUser, checkPass;
 	 for (int i = 0; i < sArray.size(); i++) {
		 checkUser = sArray[i].name;
		 checkPass = sArray[i].pass;
		 clean(checkUser);
		 clean(checkPass);
		 //cout << "\n\nComparing: " << user << " to " << checkUser << endl << endl;
	 	 if (user.compare(checkUser) == 0) {
			 //cout << "\n\nYOU MADE IT HERE\n\n";
		 	 //check password
			 //cout << sArray[i].getPassword();
			 if (pass.compare(checkPass) == 0) {
				 current.name = checkUser;
				 //cout << "DINGDINGDING DING HERE IT IS!!!!!!!!!!!!" << current.name;
				 current.pass = checkPass;
				 current.access = sArray[i].access;
			 	 return true;
			 }
			 return false;
		 }
	 }
	 return false;
 }

 bool CASystem::getAccess() {
	 return current.access; 
 }

 void CASystem::editCurrent() {
 	 //first ensure that the password isn't the same
	 cout << "New Password: ";
	 string passIn;
	 getline(cin, passIn);
	 clean(passIn);
	 //check it against current
	 while (current.pass.compare(passIn) == 0) {
		cout << "Error - Your new password must be different from the old one!\n";
		cout << "New Password: ";
		getline(cin, passIn);
		clean(passIn);
	 }
	 //great now change the password of current
	 int index = findStaff(current.name);
	 if (index > -1) {
	 	 sArray[index].pass = passIn;
		 cout << "Password changed successfully!\n";
	 }
	 //saveUser();
	 //display();
 }

 int CASystem::findStaff(string in) {
 	 for (int i = 0; i < sArray.size(); i++) {
		 //cout << sArray[i].name << " from array as length " << sArray[i].name.length() << " is being compared to " << current.name << " of length " << current.name.length() << endl;
	 	 if (sArray[i].name.compare(in) == 0) {
		 	 return i;
			 //cout <<endl << i<<endl;
		 }
	 }
	 return -1;
 }

 int CASystem::findClient(string in) {
	 for (int i = 0; i < cArray.size(); i++) {
		 //cout << sArray[i].name << " from array as length " << sArray[i].name.length() << " is being compared to " << current.name << " of length " << current.name.length() << endl;
	 	 if (cArray[i].name.compare(in) == 0) {
		 	 return i;
			 //cout <<endl << i<<endl;
		 }
	 }
	 return -1;
 }

 int CASystem::findAccount(int in) {
	 for (int i = 0; i < aArray.size(); i++) {
		 //cout << sArray[i].name << " from array as length " << sArray[i].name.length() << " is being compared to " << current.name << " of length " << current.name.length() << endl;
	 	 if (aArray[i].number == in) {
		 	 return i;
			 //cout <<endl << i<<endl;
		 }
	 }
	 return -1;
 }

 void CASystem::addBranch() {
	 cout << "Add a user - Username: ";
	 string userIn, passIn, roleIn, ain;
	 getline(cin, userIn);
	 clean(userIn);
	 while (findStaff(userIn) != -1) {//make sure it is a fresh one!
		cout << "User already exists! Try again.\nUsername: ";
		getline(cin, userIn);
		clean(userIn);
	 }
	 cout << "Password: ";
	 getline(cin, passIn);
	 clean(passIn);
	 cout << "Role (1 - Administrator; 2 - Branch Staff): ";
	 getline(cin, roleIn);
	 clean(roleIn);
	 while (roleIn.compare("1") != 0 && roleIn.compare("2") != 0) {
	 	 cout << "Invalid input, please try again.\nRole: ";
		 getline(cin, roleIn);
		 clean(roleIn);
	 }
	 cout << "1)  Confirm\n2)  Cancel\n";
	 cout << "Please choose an option: ";
	 getline(cin, ain);
	 clean(ain);
	 while (ain.compare("1") != 0 && ain.compare("2") != 0) {
		cout << "Invalid input, please try again.\nPlease choose an option: ";
		getline(cin, userIn);
		clean(userIn);
	 }
	 if (ain.compare("2") == 0) {
	 	 return;
	 }
	 Staff nextIn;
	 nextIn.name = userIn;
	 nextIn.pass = passIn;
	 if (roleIn.compare("1") == 0) {
	 	 //administrator
		 nextIn.access = false; //represents admin
	 } else {
	 	 nextIn.access = true;
	 }

	 sArray.push_back(nextIn);

	 cout << "A new branch staff member is added!\nUsername: " << nextIn.name << "   Role: ";
	 if (nextIn.access) {
	 	 cout << "Branch Manager\n";
	 } else {
	 	 cout << "System Administrator\n";
	 }
	 //cout << "\nPress any key to continue...";
	 pause_now();
 }

 void CASystem::deleteBranch() {
	 cout << "Delete a user - Username: ";
	 string userIn, ain;
	 getline(cin, userIn);
	 clean(userIn);
	 cout << "1)  Confirm\n2)  Cancel\n";
	 cout << "Please choose an option: ";
	 getline(cin, ain);
	 clean(ain);
	 while (ain.compare("1") != 0 && ain.compare("2") != 0) {
		cout << "Invalid input, please try again.\nPlease choose an option: ";
		getline(cin, userIn);
		clean(userIn);
	 } 
	 if (ain.compare("2") == 0) {
	 	 return;
	 } else {
		if (findStaff(userIn) == -1) {//make sure it is a fresh one!
			cout << "Warning - User " << userIn << " is not in the system. No user is deleted!\n";
		} else {
			//delete the user
			int index = findStaff(userIn);
			sArray.erase(sArray.begin() + index);
			cout << "User " << userIn << " was deleted!\n";
		}
	 }
	 pause_now();
 }

 void CASystem::displayMembers() {
	 cout << "There are " << sArray.size() << " users in the system.\n";
	 int count = 1;
	 for (int i = 0; i < sArray.size(); i++) {
		 cout << count++ << ".\tUser: " << sArray[i].name << "\n\tRole: ";
		 if (sArray[i].access) {
	 		cout << "Branch Manager\n";
		 } else {
	 		cout << "System Administrator\n";
		 }
	 }
	 pause_now();
 }

 void CASystem::saveUser() {
	 staffOutStream.open((char*)STAFF_FILE.c_str());
	 for (int i = 0; i < sArray.size(); i++) {
       staffOutStream << sArray[i].name << '*' << sArray[i].pass << '*' << sArray[i].access << std::endl;
     }
     staffOutStream.close();
 }

 void CASystem::editClient() {
	 cout << "Choose a client: ";
	 string nameIn, ain;
	 getline(cin, nameIn);
	 clean(nameIn);
	 if (findClient(nameIn) == -1) {
	 	 cout << "Warning - Client " << nameIn << " is not in the system. No client is edited!\n";
	 } else {
		 int index = findClient(nameIn);
		 Client here = cArray[index];
	 	 cout << "Display " << here.name << "\'s information:\n";
		 cout << "\tAddress: " << here.address << "\n\tSSN: " << here.social << "\n\tEmployer: " << here.employer << "\n\tAnnual income: $" << here.annualIncome << "\n";
		 cout << "Client " << here.name << "\'s information will be updated...\n";
		 cout << "1)  Confirm\n2)  Cancel\n";
		 cout << "Please choose an option: ";
		 getline(cin, ain);
		 clean(ain);
		 while (ain.compare("1") != 0 && ain.compare("2") != 0) {
			 cout << "Invalid input, please try again.\nPlease choose an option: ";
			 getline(cin, ain);
			 clean(ain);
		 } 
		 if (ain.compare("1") == 0) {
			 string add, ssn, emp, annInc;
			 cout << "Address: ";
			 getline(cin,add);
			 clean(add);
			 cout << "SSN: ";
			 getline(cin,ssn);
			 clean(ssn);
			 cout << "Employer: ";
			 getline(cin, emp);
			 clean(emp);
			 cout << "Annual income: ";
			 getline(cin,annInc);
			 clean(annInc);
			 cArray[index].address = add;
			 cArray[index].social = ssn;
			 cArray[index].employer = emp;
			 cArray[index].annualIncome = atoi(annInc.c_str());
			 cout << "Client " << here.name << "\'s information was updated!\n";

		 }
	 }
	 pause_now();
 }

 void CASystem::addClient() {
	 cout << "A new client will be added.\nClient name: ";
	 string name, add, ssn, emp, annInc;
			 getline(cin,name);
			 clean(name);
			 cout << "Address: ";
			 getline(cin,add);
			 clean(add);
			 cout << "SSN: ";
			 getline(cin,ssn);
			 clean(ssn);
			 cout << "Employer: ";
			 getline(cin, emp);
			 clean(emp);
			 cout << "Annual income: ";
			 getline(cin,annInc);
			 clean(annInc);
			 Client next;
			 next.name = name;
			 next.address = add;
			 next.social = ssn;
			 next.employer = emp;
			 next.annualIncome = atoi(annInc.c_str());
			 cArray.push_back(next);
			 cout << "A new client was added!\n";
	 pause_now();
 }

 void CASystem::addAccount() {
	 cout << "Choose a client: ";
	 string clientName, accNum, type, balIn;
	 getline(cin, clientName);
	 clean(clientName);
	 while (findClient(clientName) == -1) {
			 cout << "Error - The client is not in the system!\nChoose a client: ";
			 getline(cin, clientName);
			 clean(clientName);
     } 
	 cout << "A new account will be created for " << clientName << "...\nAccount Number: ";
	 getline(cin, accNum);
	 clean(accNum);
	 cout << "Account Type: ";
	 getline(cin, type);
	 clean(type);
	 cout << "Balance: ";
	 getline(cin, balIn);
	 clean(balIn);
	 Account next;
	 next.name = type;
	 next.balance = atoi(balIn.c_str());
	 next.number = atoi(accNum.c_str());
	 cArray[findClient(clientName)].linkedAccounts.push_back(next);
	 cout << "A new account was created for " << clientName << "!\n";
	 aArray.push_back(next);
	 pause_now();
 }

 void CASystem::manageAccount() {
	 cout << "Which account will be managed? ";
	 string accIn, ain;
	 int acc;
	 getline(cin, accIn);
	 clean(accIn);
	 acc = atoi(accIn.c_str());
	 while (findAccount(acc) == -1) {
	 	 //account doesnt exist
		 cout << "Error - Account " << acc << " is not in the system!\n1) Manage an account\n2) Cancel\n";
		 cout << "Choose an option: ";
		 getline(cin, ain);
		 clean(ain);
		 while (ain.compare("1") !=0 && ain.compare("2") != 0) {
		 	 cout << "Invalid input. Please try again.\nChoose an option: ";
			 getline(cin, ain);
			 clean(ain);
		 }
		 if (ain.compare("1") == 0) {
			 getline(cin, accIn);
			 clean(accIn);
			 acc = atoi(accIn.c_str());
		 } else {
			 return;
		 }
	 }
	 //now there is a legit acount
	 //find which client it is tied to!
	 int cindex = -1;
	 int lindex = -1;
	 for (int i = 0; i < cArray.size(); i++) {
	 	 for (int n = 0; n < cArray[i].linkedAccounts.size(); n++) {
			 if (cArray[i].linkedAccounts[n].number == acc) {
			 	  cindex = i;
				  lindex = n;
			 }
		 }
	 }
	 cout << "Manage account " << acc << " for " << cArray[cindex].name << " ...\n";
	 cout << "1)  Deposit\n2)  Withdraw\n3)  Cancel\nPlease choose an option: ";
	 string din;
	 getline(cin, din);
	 clean(din);
	 bool keepgoing = true;
	 do {
		while (din.compare("1") != 0 && din.compare("2") != 0 && din.compare("3")) {
			cout << "Invalid input. Please try agdin.\nChoose an option: ";
			getline(cin, din);
			clean(din);
		}
		if (din.compare("1") == 0) {
			//Deposit
			cout << "Deposit Amount: ";
			string amIn;
			getline(cin, amIn);
			clean(amIn);
			cArray[cindex].linkedAccounts[lindex].balance += atoi(amIn.c_str());
			cout << "Balance of account " << cArray[cindex].linkedAccounts[lindex].number << " for " << cArray[cindex].name << " is: " << cArray[cindex].linkedAccounts[lindex].balance << endl;
			cout << "Manage account " << acc << " for " << cArray[cindex].name << " ...\n";
		    cout << "1)  Deposit\n2)  Withdraw\n3)  Cancel\nPlease choose an option: ";
			getline(cin, din);
			clean(din);
		} else if (din.compare("2") == 0) {
			//withdraw
			cout << "Withdraw Amount: ";
			string amIn;
			getline(cin, amIn);
			clean(amIn);
			cArray[cindex].linkedAccounts[lindex].balance -= atoi(amIn.c_str());
			cout << "Balance of account " << cArray[cindex].linkedAccounts[lindex].number << " for " << cArray[cindex].name << " is: " << cArray[cindex].linkedAccounts[lindex].balance << endl;
			cout << "Manage account " << acc << " for " << cArray[cindex].name << " ...\n";
			cout << "1)  Deposit\n2)  Withdraw\n3)  Cancel\nPlease choose an option: ";
			getline(cin, din);
			clean(din);
		} else {
			keepgoing = false;
		}
	 } while (keepgoing);
 }

 void CASystem::saveAll() {
	 clientOutStream.open((char*)CLIENT_FILE.c_str());
	 for (int i = 0; i < cArray.size(); i++) {
       clientOutStream << cArray[i].name << '*' << cArray[i].address << '*' << cArray[i].social << '*' << cArray[i].employer << '*' << cArray[i].annualIncome;
	   clientOutStream << '*';
	   for (int n = 0; n < cArray[i].linkedAccounts.size(); n++) {
	   	   clientOutStream << cArray[i].linkedAccounts[n].number << ' ';
	   }
	   clientOutStream << std::endl;
     }
     clientOutStream.close();

	 accountOutStream.open((char*)ACCOUNT_FILE.c_str());
	 for (int i = 0; i < aArray.size(); i++) {
		 accountOutStream << aArray[i].number << '*' << aArray[i].balance << '*' << aArray[i].name << std::endl;
     }
     accountOutStream.close();
 }

 /******************************************************
  *                 Menu implementation                 *
  ******************************************************/




 void Menu::startup() {
	string out = "\n\t===========================================================\n";
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

	//create a sysrunner
	CASystem runner;
	runner.initialize();

	string logOut = "\n\t===========================================================\n";
	      logOut += "\t|            Login to Access the Teller System            |\n";
		  logOut += "\t===========================================================\n";
	cout << logOut << "Username: ";
	string user, pass;
	getline(cin, user, '\n');
	cout << "Password: ";
	getline(cin, pass, '\n');
    validInput = runner.login(user,pass);
	//cout << pass << " " << user;
	while (!validInput) {
    //cout << "Is this even working?";
		if (!runner.login(user, pass)) {
			cout << "The username or password is incorrect. Try again!\nUsername: ";
			getline(cin, user, '\n');
			cout << "Password: ";
			getline(cin, pass, '\n');
			//cout << pass << " " << user;
		} else {
			validInput = true;
		}
	}
	

	if(!runner.getAccess()) {
		string sysadmin = "\n\t===========================================================\n";
	        sysadmin += "\t|      Teller Terminal System - System Administration     |\n";
		    sysadmin += "\t===========================================================\n";
		    sysadmin += "1)  Client and Account Management\n";
		    sysadmin += "2)  Add a branch staff member\n";
			sysadmin += "3)  Delete a branch staff member\n";
		    sysadmin += "4)  Display branch staff\n";
			sysadmin += "5)  Change password\n";
		    sysadmin += "6)  Exit\n";
		cout << sysadmin << prompt;
		bool wantsExit = false;
		string response;
		while (!wantsExit) {
			//cout << sysadmin << prompt;
			//get input 
			getline(cin, response);
			clean(response);
			if (response.compare("1") == 0) {
				//login and account management
				accountManagement(runner);
				cout << sysadmin << prompt;
			} else if (response.compare("2") == 0) {
				//addbranch
				runner.addBranch();
				cout << sysadmin << prompt;
			} else if (response.compare("3") == 0) {
				//deletebranch
				runner.deleteBranch();
				cout << sysadmin << prompt;
			} else if (response.compare("4") == 0) {
				//display branch staff
				runner.displayMembers();
				cout << sysadmin << prompt;
			} else if (response.compare("5") == 0) {
		        //password! 
				runner.editCurrent();
				cout << sysadmin << prompt;
			} else if (response.compare("6") == 0) {
				wantsExit = true;
			} else {
				cout << "Invalid input, please try again.\n";
				cout << prompt;
		    }
	    }
	} else {
		string branchstaff = "\n\t===========================================================\n";
	        branchstaff += "\t|           Teller Terminal System - Branch Staff         |\n";
		    branchstaff += "\t===========================================================\n";
		    branchstaff += "1)  Client and Account Management\n";
			branchstaff += "2)  Change password\n";
		    branchstaff += "3)  Exit\n";
		cout << branchstaff << prompt;
		bool wantsExit = false;
		string response;
		while (!wantsExit) {
			//get input 
			//cout << branchstaff << prompt;
			getline(cin, response);
			clean(response);
			if (response.compare("1") == 0) {
				//login and account management
				accountManagement(runner);
				cout << branchstaff << prompt;
			} else if (response.compare("2") == 0) {
		    //change password
				runner.editCurrent();
				cout << branchstaff << prompt;
			} else if (response.compare("3") == 0) {
				wantsExit = true;
			} else {
				cout << "Invalid input, please try again.\n";
				cout << prompt;
		    }
	    }
	}
	runner.saveUser();
 }
 //void Menu::mainMenu(bool access) {
 


 void Menu::accountManagement(CASystem& runnerIn) {
	 //count 
	 string acctm = "\n\t===========================================================\n";
	        acctm += "\t| Teller Terminal System - Client and Account Management  |\n";
		    acctm += "\t===========================================================\n";
		    acctm += "1)  Add a client\n";
			acctm += "2)  Add an account\n";
		    acctm += "3)  Edit Client Information\n";
			acctm += "4)  Manage an account\n";
			acctm += "5)  Save Client and Account Information\n";
		    acctm += "6)  Exit\n";
	 string prompt = "Please choose an option: ";
	 cout << acctm << prompt;
	 bool wantsExit = false;
	 string response;
	 while (!wantsExit) {
		 //cout << sysadmin << prompt;
		 //get input 
		 getline(cin, response);
		 clean(response);
		 if (response.compare("1") == 0) {
			 //add client
			 runnerIn.addClient();
			 cout << acctm << prompt;
		 } else if (response.compare("2") == 0) {
			 //add account
			 runnerIn.addAccount();
			 cout << acctm << prompt;
		 } else if (response.compare("3") == 0) {
			 //edit client
			 runnerIn.editClient();
			 cout << acctm << prompt;
		 } else if (response.compare("4") == 0) {
			 //manage account
			 runnerIn.manageAccount();
			 cout << acctm << prompt;
		 } else if (response.compare("5") == 0) {
		     //save client and account informatoiun
			 runnerIn.saveAll();
			 cout << acctm << prompt;
		 } else if (response.compare("6") == 0) {
			 wantsExit = true;
		 } else {
			 cout << "Invalid input, please try again.\n";
			 cout << prompt;
		 }
	 }
 }

 



 /******************************************************
 *                      MISC implementation            *
 ******************************************************/
 void clean(string &in) {
 	 in.erase(in.find_last_not_of(" \n\r\t")+1);

 }

 string stringify(int in) {
 	 ostringstream os;
	 os << in;
	 return os.str();
 }

 /*****************************************************
 * Functions borrowed from pressanykey.cpp on Canvas *
 *****************************************************/
void pause_now(void) {
  char ch;
  cout << "Press any key to continue...\n";
  ch = mygetch();
  if (ch == 0 || ch == 224) mygetch();
}

int mygetch (void)
{
  int ch;
  struct termios oldt, newt;

  tcgetattr ( STDIN_FILENO, &oldt );
  newt = oldt;
  newt.c_lflag &= ~( ICANON | ECHO );
  tcsetattr ( STDIN_FILENO, TCSANOW, &newt );
  ch = getchar();
  tcsetattr ( STDIN_FILENO, TCSANOW, &oldt );

  return ch;
}