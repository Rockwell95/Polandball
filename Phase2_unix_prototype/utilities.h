#ifndef UTILITIES_H_
#define UTILITIES_H_
#include "commands.h"
#include <string>

// Retrieve a user account by their name on file. Takes the full name and the user accounts file (default current_accounts.txt). Returns an account struct containing the user data.
account getAccountByName( std::string s_holdername, std::string s_filename = "current_accounts.txt" );

// Retrieve a user account by their number on file. Takes the full name and the user accounts file (default current_accounts.txt). Returns an account struct containing the user data.
account getAccountByNumber( std::string s_number, std::string s_filename = "current_accounts.txt" );

// Utility tool: Determines if "value" is contained in the array "sa_values". Returns TRUE if "value" is found in the "sa_values" array, FALSE otherwise.
bool contains( std::string sa_values[], std::string value );

// Find and validate user account (used by admins). This function will prompt the admin user for account details and if an account is found, this will return an account struct containing the user data.
account getUserAccount();

// Comparison of account number and input number. Returns TRUE if they match, FALSE if they do not.
bool userValidation( std::string s_accountNumber );

// Insert a new account into s_filename. Takes the user account and a filenamme to save to. Returns an integer, 1 for success 0 for failure.
int writeStandardAccount( account acct, std::string s_filename = "current_accounts.txt" );

// Update an existing account into s_filename. Takes the user account and a filenamme to save to. Returns an integer, 1 for success 0 for failure.
int updateStandardAccount( account acct, std::string s_filename = "current_accounts.txt" );

// Write a new transaction file. Takes the user account and a filenamme to save to. Returns an integer, 1 for success 0 for failure.
int writeTransactionFile( account acct, std::string s_filename = "johndoe.txt" );

// Attempt to cast a string to a double. Throws errors if it can't happen.
double attempt_conversion( std::string s_1 );

// Added for readability
const int STANDARD_ACCOUNT = 0;
const int ADMIN_ACCOUNT = 1;

#endif // UTILITIES_H_
