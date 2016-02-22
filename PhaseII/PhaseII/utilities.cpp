#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>
#include "utilities.h"

using namespace std;
account getAccountInfo(string ss_holdername) {
  string s_account_line;
  ifstream ifs_accounts_file;
  ifs_accounts_file.open("current_accounts.txt");
  account acct;
  while (getline(ifs_accounts_file, s_account_line)) {
    // cout << (s_account_line.substr(6, (acct.s_holdername.length()))) + "==" << endl;
    // cout << acct.s_holdername + "==" << endl;

    if ((ss_holdername).compare(s_account_line.substr(6,
      (ss_holdername.length()))) == 0) {
      acct.s_holdername = ss_holdername;
      // cout << acct.s_holdername << endl;
      acct.nLevel = STANDARD_ACCOUNT;
      // cout << acct.nLevel << endl;
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
account getAccountByNumber(string ss_number) {
  string s_account_line;
  ifstream ifs_accounts_file;
  ifs_accounts_file.open("current_accounts.txt");
  account acct;
  while (getline(ifs_accounts_file, s_account_line)) {
    // cout << (s_account_line.substr(6, (acct.s_holdername.length()))) + "==" << endl;
    // cout << acct.s_holdername + "==" << endl;

    if ((ss_number).compare(s_account_line.substr(0,
      (ss_number.length()))) == 0) {
      acct.s_holdername = s_account_line.substr(6, 20);
      // cout << acct.s_holdername << endl;
      acct.nLevel = STANDARD_ACCOUNT;
      // cout << acct.nLevel << endl;
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

bool contains(string sa_values[], string value) {
  bool found = false;
  for (int i = 0; i < sizeof(sa_values); i++) {
    if (sa_values[i].compare(value) == 0)
    {
      found = true;
      break;
    }
    return found;
  }
}