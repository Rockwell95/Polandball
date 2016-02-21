#include "stdafx.h"
#include "utilities.h"
#include <iostream>
using namespace std;
/*!*/ // Indicates an admin level command
void menu(account acct) 
{
  string sCommand;
  bool bLoggedIn = true;
  while (cin >> sCommand) {
    if (sCommand.compare("withdrawal") == 0) {
      withdrawal(acct);
    }
    else if (sCommand.compare("transfer") == 0) {
      transfer(acct);
    }
    else if (sCommand.compare("paybill") == 0) {
      paybill(acct);
    }
    else if (sCommand.compare("deposit") == 0) {
      deposit(acct);
    }
    /*!*/else if (sCommand.compare("create") == 0) {
      create(acct);
    }
    /*!*/else if (sCommand.compare("delete") == 0) {
      delte(acct);
    }
    /*!*/else if (sCommand.compare("disable") == 0) {
      disable(acct);
    }
    /*!*/else if (sCommand.compare("changeplan") == 0) {
      changeplan(acct);
    }
    else if (sCommand.compare("logout") == 0) {
      logout(bLoggedIn);
      if (bLoggedIn)
      {
        return;
      }
    }
    else {
      cout << "Invalid command. \"" + sCommand + "\" is not a known command, terminating session.\n";
      return;
    }
    cout << "\n>";
  }
}

//.......................................................................................................................................................................
void withdrawal(account acct) {
  string sFirstName, sLastName, sFullName, sAcctNum;
  double dWDAmount;
  if (acct.nLevel == 1) {
    cout << "Withdraw command selected. Please enter the administrator name:\n>";
    cin >> sFirstName;
    cin >> sLastName;
    sFullName = sFirstName + " " + sLastName;
    acct = getAccountInfo(sFullName);
    if (!acct.sNumber.empty()) {
      cout << "Name accepted, please enter the account number you wish to withdraw from :\n>";
    }
    else {
      cout << "Error, invalid administrator name, killing withdraw request." << endl;
      return;
    }
  }
  else {
    cout << "Withdraw command selected. Please enter the account number you wish to withdraw funds from:\n>";
  }
  cin >> sAcctNum;
  if (sAcctNum.compare(acct.sNumber) == 0) {
    cout << "Account number accepted, please enter the amount to withdraw:\n>";
  anotherSValue:
    if (cin >> dWDAmount && dWDAmount <= 500 && dWDAmount >= 0.01) {
      acct.dBalance -= dWDAmount;
      cout << "Done!\nNew Balance: ";
      cout << acct.dBalance;
    }
    else if (cin >> dWDAmount && dWDAmount > 500) {
      cout << "Error, withdraw amount exceeds $500.00, please enter another value:\n>";
      goto anotherSValue;
    }
    else if (cin >> dWDAmount && dWDAmount < 0.01) {
      cout << "Error, withdraw amount must be greater than $0.00, please enter another value:\n>";
      goto anotherSValue;
    }
    else if (cin >> dWDAmount && dWDAmount > acct.dBalance) {
      cout << "Error, not enough funds in account to complete transaction, please enter another value:\n>";
      goto anotherSValue;
    }
    else {
      cout << "Error, value entered is not a recognized number, please enter another value:\n>";
      goto anotherSValue;
    }
  }
  else {
    cout << "Error, invalid account number, killing withdraw request.";
  }
}
//.......................................................................................................................................................................
void transfer(account acct) {
  string sFirstName, sLastName, sFullName, sFromAcctNum, sToAcctNum;
  double dTAmount;
  account tToAccount;
  if (acct.nLevel == 1) {
    cout << "Transfer mode selected, please enter the administrator name:\n>";
    cin >> sFirstName;
    cin >> sLastName;
    sFullName = sFirstName + " " + sLastName;
    acct = getAccountInfo(sFullName);
    if (!acct.sNumber.empty()) {
      cout << "Name accepted, welcome " + sFullName + ". Please enter the number of the account you wish to to transfer from : \n>";
    }
    else {
      cout << "Error, the administrator name you entered is not recognized, terminating transaction...\n";
      return;
    }
  }
  else {
    cout << "Transfer mode selected, please enter the number of the account you wish to transfer from:\n>";
  }
  cin >> sFromAcctNum;
  if (sFromAcctNum.compare(acct.sNumber) == 0) {
    cout << "From account number accepted, please enter the number of the account you wish to transfer to:\n>";
    cin >> sToAcctNum;
    tToAccount = getAccountByNumber(sToAcctNum);
    cout << "To account number accepted, please enter the amount you wish to transfer from " + acct.sNumber + " to " + tToAccount.sNumber + ":\n>";
    if (!tToAccount.sHolderName.empty()) {
    anotherSTransferValue:
      if (cin >> dTAmount && dTAmount <= 1000 && dTAmount >= 0.01) {
        acct.dBalance -= dTAmount;
        tToAccount.dBalance += dTAmount;
        cout << "Done!\nNew Balance: ";
        cout << acct.dBalance;
      }
      else if (cin >> dTAmount && dTAmount > 1000) {
        cout << "Error, transfer amount exceeds $1000.00, please enter another value:\n>";
        goto anotherSTransferValue;
      }
      else if (cin >> dTAmount && dTAmount < 0.01) {
        cout << "Error, transfer amount must be greater than $0.00, please enter another value:\n>";
        goto anotherSTransferValue;
      }
      else if (cin >> dTAmount && dTAmount > acct.dBalance) {
        cout << "Error, not enough funds in account to complete transaction, please enter another value:\n>";
        goto anotherSTransferValue;
      }
      else {
        cout << "Error, value entered is not a recognized number, please enter another value:\n>";
        goto anotherSTransferValue;
      }
    }
    else {
      cout << "Error, the account number you wish to transfer to is not reocignized, ending transaction.\n";
    }
  }
  else {
    cout << "Error, the account number you wish to transfer from is not recognized, ending transaction.\n";
  }
}
//.......................................................................................................................................................................
void paybill(account acct) {
  string sFirstName, sLastName, sFullName, sAcctNum, sCompany;
  string sValidCompanies[] = { "Bright Light Electric Company", "EC", "Credit Card Company Q", "CQ", "Low Definition TV, Inc", "TV" };
  double dPayAmount;
  if (acct.nLevel == 1) {
    cout << "Pay bill command selected. Please enter the administrator name:\n>";
    cin >> sFirstName;
    cin >> sLastName;
    sFullName = sFirstName + " " + sLastName;
    acct = getAccountInfo(sFullName);
    if (acct.sHolderName.empty()) {
      cout << "The account name is not a recognized account name.\n";
      return;
    }
  }
  else {
    cout << "Pay bill command selected. ";
  }
  if (!acct.sNumber.empty()) {
    cout << "Please enter the account number you wish to pay from :\n>";
    cin >> sAcctNum;
    if (sAcctNum.compare(acct.sNumber) == 0) {
      cout << "Please enter the company name to pay:\n>";
      cin >> sCompany;
      if (contains(sValidCompanies, sCompany)) {
        cout << "Please enter an amount to pay:\n>";
        anotherSPaymentValue:
        if (cin >> dPayAmount && dPayAmount <= 2000 && dPayAmount >= 0.01) {
          acct.dBalance -= dPayAmount;
          cout << "Payment Successful.\nNew Balance: ";
          cout << acct.dBalance;
        }
        else if (cin >> dPayAmount && dPayAmount > 2000) {
          cout << "The maximum amount that can be paid to a bill holder is $2000.00 in the current session. The amount entered exceeds $2000.00\n>";
          goto  anotherSPaymentValue;
        }
        else if (cin >> dPayAmount && dPayAmount < 0.01) {
          cout << "The minimum amount that can be paid to a bill holder is greater than $0.00 in the current session.\n>";
          goto  anotherSPaymentValue;
        }
        else if (cin >> dPayAmount && dPayAmount > acct.dBalance) {
          cout << "The payment exceeds the current account balance. Payment has not been processed.\n>";
          goto  anotherSPaymentValue;
        }
        else {
          cout << "Please enter a valid dollar amount for this bill payment. Example: 500.00.\n>";
          goto  anotherSPaymentValue;
        }
      }
      else {
        cout << "The company name is not a recognized company name.\n";
      }
    }
    else {
      cout << "The account number entered is not a recognized account number in the system.\n";
    }
  }
  else {
    cout << "Unrecognized command." << endl;
  }
}
//.......................................................................................................................................................................
void deposit(account acct) {
  string sFirstName, sLastName, sFullName, sAcctNum, sCompany;
  double dDepAmount;
  if (acct.nLevel == 1) {
    cout << "Deposit command selected. Please enter the administrator name:\n>";
    cin >> sFirstName;
    cin >> sLastName;
    sFullName = sFirstName + " " + sLastName;
    acct = getAccountInfo(sFullName);
    if (acct.sHolderName.empty()) {
      cout << "The account name is not a recognized account name.\n";
      return;
    }
  }
  else {
    cout << "Deposit command selected. ";
  }
  if (!acct.sNumber.empty()) {
    cout << "Please enter the account number:\n>";
    cin >> sAcctNum;
    if (sAcctNum.compare(acct.sNumber) == 0) {
      cout << "Please enter an amount to deposit: \n";
      anotherDepValue:
      if (cin >> dDepAmount && dDepAmount >= 0.01) {
        acct.dBalance += dDepAmount;
        cout << "Deposit successful.\nNew Balance: ";
        cout << acct.dBalance;
      }
      else {
        cout << "Please enter a valid amount to deposit.Example: 200.00";
        goto  anotherDepValue;
      }
    }
    else {
      cout << "The account number entered is not a recognized account number." << endl;
    }
  }
  else {
    cout << "The account name is not a recognized account name.\n";
  }
}
//.......................................................................................................................................................................
/*!*/void create(account acct)
{

}
//.......................................................................................................................................................................
/*!*/void delte(account acct)
{

}
//.......................................................................................................................................................................
/*!*/void disable(account acct)
{

}
//.......................................................................................................................................................................
/*!*/void changeplan(account acct)
{

}
//.......................................................................................................................................................................
void logout(bool bLoggedIn)
{
  if (bLoggedIn) {
    cout << "Thank you for using the banking system, session ended, you have been successfully logged out.\n";
  }
  else {
    cout << "You must be logged in to log out.\n";
  }
}