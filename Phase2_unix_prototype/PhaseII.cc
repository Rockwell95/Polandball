// PhaseII.cpp : Defines the entry point for the console application.
//
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "utilities.h"

using namespace std;

int main(void) {
  cout << "Welcome to the automated banking system! Please login\n>";

  string s_input;
  string s_elevation;
  string s_acctname;
  account act_stdaccount;



  // Loop through user commands indefinitely
  while (cin >> s_input) {

	if (s_input.compare("login") == 0) {

	  cout << "Logging in, are you logging in as standard or admin?\n>";
	  cin >> s_elevation;


      if (s_elevation.compare("standard") == 0) {
		cout << "Please enter your name:\n>";
        string s_firstname, s_lastname;
        cin >> s_firstname;
        cin >> s_lastname;
        s_acctname = s_firstname + " " + s_lastname;
        act_stdaccount = getAccountByName(s_acctname);

        if (act_stdaccount.s_number.empty()) {
          cout << "Name not found, terminating...\n";
          s_elevation = s_acctname;
          goto invalid;
        }
        cout << "Welcome, " + act_stdaccount.s_holdername + ".\n>";
        menu(act_stdaccount);
	  }
//.........................................................................................................................................................
      else if (s_elevation.compare("admin") == 0) {
        cout << "Welcome, administrator\n>";
        account act_adminacct;
        act_adminacct.n_level = ADMIN_ACCOUNT;
        menu(act_adminacct);
	  }
	  else {
		goto invalid;
	  }
    }
    else if (s_input.compare("logout") == 0) {
      cout << "You must be logged in to log out.\n";
    }
    else if (s_input.compare("quit") == 0) {
      cout << "Quitting...\n";
      goto terminate;
    }
    else {
      s_elevation = s_input;
      invalid:
	  cout << "Invalid command. \"" + s_elevation + "\" is not known, please try again." << endl;
    }

    cout << "System resetting in 3 seconds\n";
    usleep(3000000);
    system("clear");
    cout << "Welcome to the automated banking system! Please login\n>";
  }

  terminate:
  return 0;

}
