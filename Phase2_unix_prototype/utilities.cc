#include <iostream>
#include <string>
#include <fstream>
#include "utilities.h"

using namespace std;

/*
  getAccountByName is a function that takes an account holder name, and a filename as an argument.
  This function is used to retrieve information from an account by the name of the account holder.
  The account holder name is searched for in the accounts textfile, once found it will grab the
  line that the account holder name was found and store all the information on that line into
  an account object.
*/
account getAccountByName(string s_holdername, string s_filename) {
  string s_account_line;
  ifstream ifs_accounts_file;
  ifs_accounts_file.open(s_filename);
  account acct;
  while (getline(ifs_accounts_file, s_account_line)) {
    if ((s_holdername).compare(s_account_line.substr(6,
      (s_holdername.length()))) == 0) {
      acct.s_holdername = s_holdername;
      // cout << acct.s_holdername << endl;
      acct.n_level = STANDARD_ACCOUNT;
      // cout << acct.n_level << endl;
      acct.s_number = s_account_line.substr(0, 5);
      // cout << acct.s_number << endl;
      acct.c_status = s_account_line.at(27);
      // cout << acct.c_status << endl;
      acct.d_balance = stod(s_account_line.substr(29, 36));
      // cout << acct.d_balance << endl;
    }
  }
  return acct;
}

/*
  getAccountByNumber is a function that takes an account number, and a filename as an argument.
  This function is used to retrieve information from an account by the account number of the account holder.
  The account number is searched for in the accounts textfile, once found it will grab the
  line that the account number was found and store all the information on that line into
  an account object.
*/
account getAccountByNumber(string s_number, string s_filename) {
  string s_account_line;
  ifstream ifs_accounts_file;
  ifs_accounts_file.open(s_filename);
  account acct;
  while (getline(ifs_accounts_file, s_account_line)) {
    // cout << (s_account_line.substr(6, (acct.s_holdername.length()))) + "==" << endl;
    // cout << acct.s_holdername + "==" << endl;

    if (s_number.compare(s_account_line.substr(0, s_number.length())) == 0) {
      acct.s_holdername = s_account_line.substr(6, 20);
      // cout << acct.s_holdername << endl;
      acct.n_level = STANDARD_ACCOUNT;
      // cout << acct.n_level << endl;
      acct.s_number = s_account_line.substr(0, 5);
      // cout << acct.s_number << endl;
      acct.c_status = s_account_line.at(27);
      // cout << acct.c_status << endl;
      acct.d_balance = stod(s_account_line.substr(29, 36));
      // cout << acct.d_balance << endl;
    }
  }
  return acct;
}

/*
  This function is used to compare 2 strings and will return true if the strings match.
*/
bool contains(string sa_values[], string value) {
  bool found = false;
  for (int i = 0; i < sizeof(sa_values); i++) {
    if (sa_values[i].compare(value) == 0)
    {
      found = true;
      break;
    }
  }
  return found;
}

/*
  prompt() is a functions that takes a boolean for whether a name is wanted, another boolean that
  determines whether the account number is required, a pointer to an accout, and a strong containing
  the specified command name. The function will get user input for a name and number (if either are
  requested by the function caller) and will store them in a struct that it returns to the caller.
  This struct can then be used in whatever way necessary. In the even a name is requested, but not found,
  or a number is requested but not found, a flag is set, marking the struct as "invalid", thus telling the
  caller that the values in the structs are incomplete, and should be rejected.
*/
prompt_struct prompt(bool name, bool acct_num, account *acct, string command) {
  string s_firstname, s_lastname, s_fullname, s_acctnum;
  prompt_struct ps;
  if(name) {
    cout << "Please enter the administrator name:\n>";
    cin >> s_firstname;
    cin >> s_lastname;
    s_fullname = s_firstname + " " + s_lastname;
    ps.prompt_name = s_fullname;
    *acct = getAccountByName(s_fullname);
  }
  else{
    s_fullname = acct->s_holdername;
  }
  if(acct_num) {
    if (!acct->s_number.empty()) {
      cout << "Name accepted. Please enter the account number you wish to " + command + " from :\n>";
      cin >> s_acctnum;
      ps.prompt_number = s_acctnum;
      cout << ps.prompt_number << endl;
      ps.is_valid = true;
    }
    else {
      cout << "Error, invalid administrator name, killing " + command + "." << endl;
      ps.is_valid = false;
    }
  }
  return ps;
}

int writeStandardAccount(account acct, string s_filename) {
  // ofstream ofs_outstream;
  // ofs_outstream.open(s_filename);

  cout << "New account created (stub)";
  return 0;
}

int updateStandardAccount(account acct, string s_filename) {
  cout << "Account Updated (stub)";
  return 0;
}

int writeTransactionFile(account acct, std::string s_filename) {
  cout << "Transaction File written (stub)";
  return 0;
}
