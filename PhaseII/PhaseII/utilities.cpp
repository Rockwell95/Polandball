#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>
#include "utilities.h"

using namespace std;
account getAccountInfo(string ssHolderName) {
  string sAccountLine;
  ifstream accountsFile;
  accountsFile.open("current_accounts.txt");
  account acct;
  while (getline(accountsFile, sAccountLine)) {
    // cout << (sAccountLine.substr(6, (acct.sHolderName.length()))) + "==" << endl;
    // cout << acct.sHolderName + "==" << endl;

    if ((ssHolderName).compare(sAccountLine.substr(6,
      (ssHolderName.length()))) == 0) {
      acct.sHolderName = ssHolderName;
      // cout << acct.sHolderName << endl;
      acct.nLevel = 0;
      // cout << acct.nLevel << endl;
      acct.sNumber = sAccountLine.substr(0, 5);
      // cout << acct.sNumber << endl;
      acct.cStatus = sAccountLine.at(27);
      // cout << acct.cStatus << endl;
      acct.dBalance = stod(sAccountLine.substr(29, 36));
      // cout << acct.dBalance << endl;
    }
  }
  return acct;
}