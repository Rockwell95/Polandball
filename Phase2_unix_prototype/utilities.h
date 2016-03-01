#ifndef UTILITIES_H_
#define UTILITIES_H_
#include "commands.h"
#include <string>

account getAccountByName(std::string s_holdername, std::string s_filename = "current_accounts.txt");
account getAccountByNumber(std::string s_number, std::string s_filename = "current_accounts.txt");
bool contains(std::string sa_values[], std::string value);

// Insert a new account into s_filename.
int writeStandardAccount(account acct, std::string s_filename = "current_accounts.txt");
// Update an existing account into s_filename.
int updateStandardAccount(account acct, std::string s_filename = "current_accounts.txt");

int writeTransactionFile(account acct, std::string s_filename = "johndoe.txt");

const int STANDARD_ACCOUNT = 0;
const int ADMIN_ACCOUNT = 1;

#endif // UTILITIES_H_