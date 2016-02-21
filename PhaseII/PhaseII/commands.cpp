#include "stdafx.h"
#include "utilities.h"
#include <iostream>
using namespace std;
/*!*/ // Indicates an admin level command
void menu(account acct) 
{
  string sCommand;
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
      logout();
    }
    else {
      cout << "Invalid command. \"" + sCommand + "\" is not a known command, terminating session.\n";
      break;
    }
    cout << "\n>";
  }
}

//.......................................................................................................................................................................
void withdrawal(account acct)
{
  string sFirstName, sLastName, sFullName, sAcctNum;
  double dWDAmount;
  if (acct.nLevel == 1) {
    cout << "Withdraw command selected. Please enter the administrator name:\n>";
    cin >> sFirstName;
    cin >> sLastName;
    sFullName = sFirstName + " " + sLastName;
    account wAccount = getAccountInfo(sFullName);
    if (!wAccount.sNumber.empty()) {
      cout << "Name accepted, please enter the account number you wish to withdraw from :\n>";
      cin >> sAcctNum;
      if (sAcctNum.compare(wAccount.sNumber) == 0) {
        cout << "Account number accepted, please enter the amount to withdraw:\n>";
        anotherValue:
        if (cin >> dWDAmount && dWDAmount <= 500 && dWDAmount >= 0.01) {
          wAccount.dBalance -= dWDAmount;
          cout << "Done!";
        }
        else if (cin >> dWDAmount && dWDAmount > 500) {
          cout << "Error, withdraw amount exceeds $500.00, please enter another value:\n>";
          goto anotherValue;
        }
        else if (cin >> dWDAmount && dWDAmount < 0.01) {
          cout << "Error, withdraw amount must be greater than $0.00, please enter another value:\n>";
          goto anotherValue;
        }
        else if (cin >> dWDAmount && dWDAmount > wAccount.dBalance) {
          cout << "Error, not enough funds in account to complete transaction, please enter another value:\n>";
          goto anotherValue;
        }
        else {
          cout << "Error, value entered is not a recognized number, please enter another value:\n>";
          goto anotherValue;
        }
      }
      else {
        cout << "Error, invalid account number, killing withdraw request.";
      }
    }
    else {
      cout << "Error, invalid administrator name, killing withdraw request." << endl;
    }
  }
  else {
    cout << "Withdraw command selected. Please enter the account number you wish to withdraw funds from:\n>";
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
}
//.......................................................................................................................................................................
void transfer(account acct)
{
  string sFirstName, sLastName, sFullName, sFromAcctNum, sToAcctNum;
  double dTAmount;
  account tToAccount;
  if (acct.nLevel == 1) {
    cout << "Transfer mode selected, please enter the administrator name:\n>";
    cin >> sFirstName;
    cin >> sLastName;
    sFullName = sFirstName + " " + sLastName;
    account tFromAccount = getAccountInfo(sFullName);
    
    if (!tFromAccount.sNumber.empty()) {
      cout << "Name accepted, welcome " + sFullName + ". Please enter the number of the account you wish to to transfer from : \n>";
      cin >> sFromAcctNum;
      if (sFromAcctNum.compare(tFromAccount.sNumber) == 0) {
        cout << "From account number accepted, please enter the number of the account you wish to transfer to:\n>";
        cin >> sToAcctNum;
        tToAccount = getAccountByNumber(sToAcctNum);
        cout << "To account number accepted, please enter the amount you wish to transfer from " + tFromAccount.sNumber + " to " + tToAccount.sNumber + ":\n>";
        if (!tToAccount.sHolderName.empty()) {
          anotherTransferValue:
          if (cin >> dTAmount && dTAmount <= 1000 && dTAmount >= 0.01) {
            tFromAccount.dBalance -= dTAmount;
            tToAccount.dBalance += dTAmount;
            cout << "Done!\nNew Balance: ";
            cout << tFromAccount.dBalance;
          }
          else if (cin >> dTAmount && dTAmount > 1000) {
            cout << "Error, withdraw amount exceeds $1000.00, please enter another value:\n>";
            goto anotherTransferValue;
          }
          else if (cin >> dTAmount && dTAmount < 0.01) {
            cout << "Error, withdraw amount must be greater than $0.00, please enter another value:\n>";
            goto anotherTransferValue;
          }
          else if (cin >> dTAmount && dTAmount > tFromAccount.dBalance) {
            cout << "Error, not enough funds in account to complete transaction, please enter another value:\n>";
            goto anotherTransferValue;
          }
          else {
            cout << "Error, value entered is not a recognized number, please enter another value:\n>";
            goto anotherTransferValue;
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
    else {
      cout << "Error, the administrator name you entered is not recognized, terminating transaction...\n";
    }
  }
  else {
    cout << "Transfer mode selected, please enter the number of the account you wish to transfer from:\n>";
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
          cout << "Error, withdraw amount exceeds $1000.00, please enter another value:\n>";
          goto anotherSTransferValue;
        }
        else if (cin >> dTAmount && dTAmount < 0.01) {
          cout << "Error, withdraw amount must be greater than $0.00, please enter another value:\n>";
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
}
//.......................................................................................................................................................................
void paybill(account acct)
{
  string sFirstName, sLastName, sFullName, sAcctNum, sCompany;
  string sValidCompanies[] = { "Bright Light Electric Company", "EC", "Credit Card Company Q", "CQ", "Low Definition TV, Inc", "TV" };
  double dWDAmount;
  if (acct.nLevel == 1) {
    cout << "Pay bill command selected. Please enter the administrator name:\n>";
    cin >> sFirstName;
    cin >> sLastName;
    sFullName = sFirstName + " " + sLastName;
    account wAccount = getAccountInfo(sFullName);
    if (!wAccount.sNumber.empty()) {
      cout << "Name accepted, please enter the account number you wish to withdraw from :\n>";
      cin >> sAcctNum;
      if (sAcctNum.compare(wAccount.sNumber) == 0) {
        cout << "Account number accepted, please enter the amount to withdraw:\n>";
      anotherValue:
        if (cin >> dWDAmount && dWDAmount <= 500 && dWDAmount >= 0.01) {
          wAccount.dBalance -= dWDAmount;
          cout << "Done!";
        }
        else if (cin >> dWDAmount && dWDAmount > 500) {
          cout << "Error, withdraw amount exceeds $500.00, please enter another value:\n>";
          goto anotherValue;
        }
        else if (cin >> dWDAmount && dWDAmount < 0.01) {
          cout << "Error, withdraw amount must be greater than $0.00, please enter another value:\n>";
          goto anotherValue;
        }
        else if (cin >> dWDAmount && dWDAmount > wAccount.dBalance) {
          cout << "Error, not enough funds in account to complete transaction, please enter another value:\n>";
          goto anotherValue;
        }
        else {
          cout << "Error, value entered is not a recognized number, please enter another value:\n>";
          goto anotherValue;
        }
      }
      else {
        cout << "Error, invalid account number, killing withdraw request.";
      }
    }
    else {
      cout << "Error, invalid administrator name, killing withdraw request." << endl;
    }
  }
  else {
    cout << "Withdraw command selected. Please enter the account number you wish to withdraw funds from:\n>";
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
}
//.......................................................................................................................................................................
void deposit(account acct)
{

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
void logout()
{

}