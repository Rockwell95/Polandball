// PhaseII.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <Windows.h>
#include "utilities.h"

using namespace std;

int main(void) {
  cout << "Welcome to the automated banking system! Please login\n>";
	
  string sInput;
  string sElevation;
  string acctName;
  account stdAccount;
  


  // Loop through user commands indefinitely
  while (cin >> sInput) {
		
	if (sInput.compare("login") == 0) {
     
	  cout << "Logging in, are you logging in as standard or admin?\n>";
	  cin >> sElevation;
	  
      
      if (sElevation.compare("standard") == 0) {
		cout << "Please enter your name:\n>";
        string sFirstName, sLastName;
        cin >> sFirstName;
        cin >> sLastName;
        acctName = sFirstName + " " + sLastName;
        stdAccount = getAccountInfo(acctName);

        if (stdAccount.sNumber.empty()) {
          cout << "Name not found, terminating...\n";
          sElevation = acctName;
          goto invalid;
        }
        cout << "Welcome, " + stdAccount.sHolderName + ".\n>";
        menu(stdAccount);
	  }
//.........................................................................................................................................................
      else if (sElevation.compare("admin") == 0) {
        cout << "Welcome, administrator\n>";
        account adminAcct;
        adminAcct.nLevel = 1;
        menu(adminAcct);
	  }
	  else {
		goto invalid;
	  }
    }
    else if (sInput.compare("logout") == 0) {
      cout << "You must be logged in to log out.\n";
    }
    else if (sInput.compare("quit") == 0) {
      cout << "Quitting...\n";
      goto terminate;
    }
    else {
      sElevation = sInput;
      invalid:
	  cout << "Invalid command. \"" + sElevation + "\" is not known, please try again." << endl;
    }

    cout << "System resetting in 3 seconds";
    Sleep(3000);
    system("cls");
    cout << "Welcome to the automated banking system! Please login\n>";
  }
  
  terminate:
  system("pause");
  return 0;

}