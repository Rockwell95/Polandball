/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
|  File: phaseii.cc                                                                                                 |
|  Authors: Dominick Mancini, Scott Mclean, Janahan Nirmalan                                                        |
|                                                                                                                   |
|  Description: This program emulates a the front-end of a banking system.                                          |
|               A User will be asked to login upon execution of this program                                        |
|               Login information consists of                                                                       |
|                  - Type of login (Standard or Admin)                                                              |
|                  - Account Holder Name                                                                            |
|                                                                                                                   |
|               The account holder name will be verified to make sure the account exists                            |
|               in the system. If the account holder name is not found in the system the user                       |
|               will be notified that the account does not exist in the system, and will have                       |
|               to try logging in again.                                                                            |
|                                                                                                                   |
|               If Admin Type is selected the Account Name will be verified to ensure the account                   |
|               is of type admin, if the account entered is not of type admin the user will be notified             |
|               and will be redirected to the login screen.                                                         |
|                                                                                                                   |
|               Upon successful login for standard and admin, the user will be greeted with their name and          |
|               will then be presented with the main menu to complete transactions that take place at the bank      |
|                                                                                                                   |
*////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "utilities.h"

using namespace std;

int main( void ) {

  // ----------Major Variables------------
  string s_input;
  string s_elevation;
  string s_acctname;
  account act_stdaccount;
  string s_firstname, s_lastname; 
  // ----------End Major Variables--------

  while ( true ) {
    s_input = "";
    s_elevation = "";
    s_acctname = "";
    act_stdaccount.s_holdername = "";
    act_stdaccount.s_number = "";
    s_firstname = "";
    s_lastname = "";
    // ----------LOGIN----------------------
    while ( true ) {
      cout << "Welcome to the automated banking system! Please login" << endl;
      cin >> s_input;
      if ( s_input.compare( "quit" ) == 0 ) {
        exit( 0 );
      }
      else if ( s_input.compare( "logout" ) == 0 ) {
        cout << "You must be logged in to log out." << endl;      
      }
      else if ( s_input.compare( "login" ) != 0 ) {
        cout << "Need help? Type \"login\" to login." << endl;
        cout << "Command not recognized: " + s_input << endl;
      }
      else {
        break;
      } 
    }
    // ----------END OF LOGIN---------------

    // ----------ADMIN OR STANDARD PROMPT----------
    while ( true ) {
      cout << "Would you like to log in as a \"standard\" or \"admin\" user?" << endl;
      cin >> s_elevation;
      if ( s_elevation.compare( "quit" ) == 0 ) {
        exit( 0 );
      }
      else if ( s_elevation.compare( "standard" ) != 0 &&
          s_elevation.compare( "admin" ) != 0) {
        cout << "Command not recognized. Please type either \"admin\" or \"standard\"" << endl;
      }
      else if ( s_elevation.compare( "quit" ) == 0 ) {
        exit( 0 );
      }
      else {
        break;
      }
    }
    // ----------END OF ADMIN OR STANDARD PROMPT---

    // ----------ADMIN ACCOUNT---------------------
    if ( s_elevation.compare( "admin" ) == 0 ) {
      cout << "Welcome, administrator" << endl;
      account act_adminacct;
      act_adminacct.n_level = ADMIN_ACCOUNT;
      menu(act_adminacct);
    }
    // ----------END OF ADMIN ACCOUNT--------------

    // ----------STANDARD ACCOUNT------------------
    if ( s_elevation.compare( "standard" ) == 0 ) {
      cout << "Please enter your name:" << endl;   
      cin >> s_firstname;
      cin >> s_lastname;
      s_acctname = s_firstname + " " + s_lastname;
      act_stdaccount = getAccountByName( s_acctname );
      if ( act_stdaccount.s_number.empty() ) {
        cout << "Name not found, terminating." << endl;
        exit( 0 ); 
      }
      cout << "Welcome, " + act_stdaccount.s_holdername + "." << endl;
      menu( act_stdaccount );
    }
    // ----------END OF STANDARD ACCOUNT-----------
  } 
  exit( 0 );
}
