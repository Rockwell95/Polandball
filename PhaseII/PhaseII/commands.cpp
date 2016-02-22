#include "stdafx.h"
#include "utilities.h"
#include <iostream>
using namespace std;
/*!*/ // Indicates an admin level command
void menu(account acct)
{
  string s_command;
  bool b_logged_in = true;
  while (cin >> s_command) {
    if (s_command.compare("withdrawal") == 0) {
      withdrawal(acct);
    }
    else if (s_command.compare("transfer") == 0) {
      transfer(acct);
    }
    else if (s_command.compare("paybill") == 0) {
      paybill(acct);
    }
    else if (s_command.compare("deposit") == 0) {
      deposit(acct);
    }
    /*!*/else if (s_command.compare("create") == 0) {
      create(acct);
    }
    /*!*/else if (s_command.compare("delete") == 0) {
      ac_delete(acct);
    }
    /*!*/else if (s_command.compare("disable") == 0) {
      disable(acct);
    }
    /*!*/else if (s_command.compare("changeplan") == 0) {
      changeplan(acct);
    }
    else if (s_command.compare("logout") == 0) {
      logout(b_logged_in);
      if (b_logged_in)
      {
        return;
      }
    }
    else {
      cout << "Invalid entry, terminating session.\n";
      return;
    }
    cout << "\n>";
  }
}

//.......................................................................................................................................................................
void withdrawal(account acct) {
  string s_firstname, s_lastname, s_fullname, s_acctnum;
  double d_wdamount;
  if (acct.n_level == ADMIN_ACCOUNT) {
    cout << "Withdraw command selected. Please enter the administrator name:\n>";
    cin >> s_firstname;
    cin >> s_lastname;
    s_fullname = s_firstname + " " + s_lastname;
    acct = getStandardAccountInfo(s_fullname);
    if (!acct.s_number.empty()) {
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
  cin >> s_acctnum;
  if (s_acctnum.compare(acct.s_number) == 0) {
    cout << "Account number accepted, please enter the amount to withdraw:\n>";
  anotherSValue:
    if (cin >> d_wdamount && d_wdamount <= 500 && d_wdamount >= 0.01) {
      acct.d_balance -= d_wdamount;
      cout << "Done!\nNew Balance: ";
      cout << acct.d_balance;
    }
    else if (cin >> d_wdamount && d_wdamount > 500) {
      cout << "Error, withdraw amount exceeds $500.00, please enter another value:\n>";
      goto anotherSValue;
    }
    else if (cin >> d_wdamount && d_wdamount < 0.01) {
      cout << "Error, withdraw amount must be greater than $0.00, please enter another value:\n>";
      goto anotherSValue;
    }
    else if (cin >> d_wdamount && d_wdamount > acct.d_balance) {
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
  string s_firstname, s_lastname, s_fullname, sFromAcctNum, sToAcctNum;
  double d_trans_amount;
  account tToAccount;
  if (acct.n_level == ADMIN_ACCOUNT) {
    cout << "Transfer mode selected, please enter the administrator name:\n>";
    cin >> s_firstname;
    cin >> s_lastname;
    s_fullname = s_firstname + " " + s_lastname;
    acct = getStandardAccountInfo(s_fullname);
    if (!acct.s_number.empty()) {
      cout << "Name accepted, welcome " + s_fullname + ". Please enter the number of the account you wish to to transfer from : \n>";
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
  if (sFromAcctNum.compare(acct.s_number) == 0) {
    cout << "From account number accepted, please enter the number of the account you wish to transfer to:\n>";
    cin >> sToAcctNum;
    tToAccount = getAccountByNumber(sToAcctNum);
    cout << "To account number accepted, please enter the amount you wish to transfer from " + acct.s_number + " to " + tToAccount.s_number + ":\n>";
    if (!tToAccount.s_holdername.empty()) {
    anotherSTransferValue:
      if (cin >> d_trans_amount && d_trans_amount <= 1000 && d_trans_amount >= 0.01) {
        acct.d_balance -= d_trans_amount;
        tToAccount.d_balance += d_trans_amount;
        cout << "Done!\nNew Balance: ";
        cout << acct.d_balance;
      }
      else if (cin >> d_trans_amount && d_trans_amount > 1000) {
        cout << "Error, transfer amount exceeds $1000.00, please enter another value:\n>";
        goto anotherSTransferValue;
      }
      else if (cin >> d_trans_amount && d_trans_amount < 0.01) {
        cout << "Error, transfer amount must be greater than $0.00, please enter another value:\n>";
        goto anotherSTransferValue;
      }
      else if (cin >> d_trans_amount && d_trans_amount > acct.d_balance) {
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
  string s_firstname, s_lastname, s_fullname, s_acctnum, sCompany;
  string sa_valid_companies[] = { "Bright Light Electric Company", "EC", "Credit Card Company Q", "CQ", "Low Definition TV, Inc", "TV" };
  double d_pay_amount;
  if (acct.n_level == ADMIN_ACCOUNT) {
    cout << "Pay bill command selected. Please enter the administrator name:\n>";
    cin >> s_firstname;
    cin >> s_lastname;
    s_fullname = s_firstname + " " + s_lastname;
    acct = getStandardAccountInfo(s_fullname);
    if (acct.s_holdername.empty()) {
      cout << "The account name is not a recognized account name.\n";
      return;
    }
  }
  else {
    cout << "Pay bill command selected. ";
  }
  if (!acct.s_number.empty()) {
    cout << "Please enter the account number you wish to pay from :\n>";
    cin >> s_acctnum;
    if (s_acctnum.compare(acct.s_number) == 0) {
      cout << "Please enter the company name to pay:\n>";
      cin >> sCompany;
      if (contains(sa_valid_companies, sCompany)) {
        cout << "Please enter an amount to pay:\n>";
        gt_another_spayment_value:
        if (cin >> d_pay_amount && d_pay_amount <= 2000 && d_pay_amount >= 0.01) {
          acct.d_balance -= d_pay_amount;
          cout << "Payment Successful.\nNew Balance: ";
          cout << acct.d_balance;
        }
        else if (cin >> d_pay_amount && d_pay_amount > 2000) {
          cout << "The maximum amount that can be paid to a bill holder is $2000.00 in the current session. The amount entered exceeds $2000.00\n>";
          goto  gt_another_spayment_value;
        }
        else if (cin >> d_pay_amount && d_pay_amount < 0.01) {
          cout << "The minimum amount that can be paid to a bill holder is greater than $0.00 in the current session.\n>";
          goto  gt_another_spayment_value;
        }
        else if (cin >> d_pay_amount && d_pay_amount > acct.d_balance) {
          cout << "The payment exceeds the current account balance. Payment has not been processed.\n>";
          goto  gt_another_spayment_value;
        }
        else {
          cout << "Please enter a valid dollar amount for this bill payment. Example: 500.00.\n>";
          goto  gt_another_spayment_value;
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
  string s_firstname, s_lastname, s_fullname, s_acctnum, sCompany;
  double d_deposit_amount;
  if (acct.n_level == ADMIN_ACCOUNT) {
    cout << "Deposit command selected. Please enter the administrator name:\n>";
    cin >> s_firstname;
    cin >> s_lastname;
    s_fullname = s_firstname + " " + s_lastname;
    acct = getStandardAccountInfo(s_fullname);
    if (acct.s_holdername.empty()) {
      cout << "The account name is not a recognized account name.\n";
      return;
    }
  }
  else {
    cout << "Deposit command selected. ";
  }
  if (!acct.s_number.empty()) {
    cout << "Please enter the account number:\n>";
    cin >> s_acctnum;
    if (s_acctnum.compare(acct.s_number) == 0) {
      cout << "Please enter an amount to deposit: \n";
      gt_another_deposit_value:
      if (cin >> d_deposit_amount && d_deposit_amount >= 0.01) {
        acct.d_balance += d_deposit_amount;
        cout << "Deposit successful.\nNew Balance: ";
        cout << acct.d_balance;
      }
      else {
        cout << "Please enter a valid amount to deposit.Example: 200.00";
        goto  gt_another_deposit_value;
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
  if (acct.n_level != ADMIN_ACCOUNT) {
    cout << "TOKEN";
    return;
  }

  account ac_newaccount;
  cout << "Enter the name for the new account holder: ";
  cin >> ac_newaccount.s_holdername;
  while (ac_newaccount.s_holdername.length() > 20) {
    cout << "The account name is too long. It must be at most 20 characters in length";
    cin >> ac_newaccount.s_holdername;
  }
  cout << "Enter the initial balance for the new account holder: ";
  cin >> ac_newaccount.d_balance;
  while (ac_newaccount.d_balance < 0 || ac_newaccount.d_balance > 99999.99) {
    cout << "The balance must be greater than $0.00 and less than or equal to $99999.99";
    cin >> ac_newaccount.d_balance;
  }


  createAccount(ac_newaccount);


}
//.......................................................................................................................................................................
/*!*/void ac_delete(account acct)
{
  if (acct.n_level != ADMIN_ACCOUNT) {
    cout << "TOKEN";
    return;
  }
  
  string s_holdername, s_number;
  cout << "Enter the name of the account holder: ";
  cin >> s_holdername;
  cout << "Enter the account number of the account holder: ";
  cin >> s_number;

  account acc_account = getAccountByNumber(s_number);
  if (acc_account.s_number == "")
  {
    cout << "Account not found";
    return;
  }
  if (s_holdername.compare(acc_account.s_holdername) == 0) {
    // Match
    deleteAccount(acc_account);
  }
  


}
//.......................................................................................................................................................................
/*!*/void disable(account acct)
{
  if (acct.n_level != ADMIN_ACCOUNT) {
    cout << "TOKEN";
    return;
  }

  string s_holdername, s_number;
  cout << "Enter the name of the account holder: ";
  cin >> s_holdername;
  cout << "Enter the account number of the account holder: ";
  cin >> s_number;

  account acc_account = getAccountByNumber(s_number);
  if (acc_account.s_number == "") {
    cout << "Account not found";
    return;
  }

  if (s_holdername.compare(acc_account.s_holdername) == 0) {
    // Match
    disableAccount(acc_account, "toggle");
  }

}
//.......................................................................................................................................................................
/*!*/void changeplan(account acct)
{
  if (acct.n_level != ADMIN_ACCOUNT) {
    cout << "TOKEN";
    return;
  }

  string s_holdername, s_number;
  cout << "Enter the name of the account holder: ";
  cin >> s_holdername;
  cout << "Enter the account number of the account holder: ";
  cin >> s_number;

  account acc_account = getAccountByNumber(s_number);
  if (acc_account.s_number == "") {
    cout << "Account not found";
    return;
  }

  if (s_holdername.compare(acc_account.s_holdername) == 0) {
    // Match
    disableAccount(acc_account, "toggle");
  }

}
//.......................................................................................................................................................................
void logout(bool b_logged_in)
{
  if (b_logged_in) {
    cout << "Thank you for using the banking system, session ended, you have been successfully logged out.\n";
  }
  else {
    cout << "You must be logged in to log out.\n";
  }
}