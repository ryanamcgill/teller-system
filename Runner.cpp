/***********************************************************************
 * Ryan McGill                                                         *
 * RAM0063                                                             *
 * Runner.cpp                                                          *
 ***********************************************************************/
 #include "CASystem.h"
 #include <iostream>
 using namespace std;

 int main() {
	CASystem sysrunner;
	if (sysrunner.initialize()) {
		cout << "Opening successful." << endl;
	} else {
		cout << "Opening unsuccessful." << endl;
	}
	sysrunner.display();
 }


