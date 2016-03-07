#include "utilities.h"
#include <iostream>
using namespace std;
/*!*/ // Indicates an admin level command

/*
  The menu function acts as the main menu for users at the bank.
  From the main menu a user can access the various transactions that take place at the bank.

  When selecting an option the menu will open up the corressponding function that is needed
  so that the proper transaction can take place.

  Our Transactions include for all users
  Withdrawal, Transfer, Paybill, Deposit, Logout

  For The Admin User
  Enable, Disable, Changeplan, Delete
*/
int menu(account acct) {
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
        return 0;
      }
    }
    else {
      cout << "Invalid entry, terminating session.\n";
      return 0;
    }
    cout << "\n>";
  }
  return 0;
}

/*
  The withdrawal function takes an Account Object as an argument
  The function will be used to withdraw funds from an account that is given.
  This function has 2 modes, an Admin Functionality and a Regular Account Holder Functionality

  The Admin Functionality will first prompt the admin for their full name to verify that the account
  is of type admin. If the admin account is not found the function will redirect the logged in user
  to the main menu. Once admin is verified, the admin will be able to withdraw from an Account
  that they specify by the account number that they request funds from.

  The Regular Account Holder Functionality will verify that they have an account at the bank.
  This is done by prompting the account holder for their account number, the account number will
  then be compared to the account number in the account object. If the account number does not match
  the transaction will be terminated and the user will be sent back to the main menu.

  After proper data validation for both Admin and Regular Account Holder, the program will continue with
  the withdrawal, it will then make sure that the ammount requested for is valid by bank guidelines.
    - Paper Transations Only ($5, $10, $20, $50, $100)
    - No Transactions Greater Than $500 Allowed
    - Daily Limit Not Reached (For Regular Account Holder, $500)
    - Sufficient Funds Exist in Account

*/
int withdrawal(account acct) {
  string s_firstname, s_lastname, s_fullname, s_acctnum;
  double d_wdamount;
  bool want_name;
  prompt_struct pr;
  if (acct.n_level == ADMIN_ACCOUNT) {
    cout << "Withdraw command selected. ";
    want_name = true;
  }
  else {
    cout << "Withdraw command selected. ";
    want_name = false;
  }
  pr = prompt(want_name, true, &acct, "withdraw");
  s_acctnum = pr.prompt_number;
  cout << s_acctnum <<endl;
  cout << pr.prompt_number << endl;
  cout << acct.s_holdername << endl;
  if(!pr.is_valid) {
    return 1;
  }
  if (s_acctnum.compare(acct.s_number) == 0) {
    cout << "Account number accepted, please enter the amount to withdraw:\n>";
  gt_another_svalue:
    if (cin >> d_wdamount && d_wdamount <= 500 && d_wdamount >= 0.01) {
      acct.d_balance -= d_wdamount;
      cout << "Done!\nNew Balance: ";
      cout << acct.d_balance;
    }
    else if (cin >> d_wdamount && d_wdamount > 500) {
      cout << "Error, withdraw amount exceeds $500.00, please enter another value:\n>";
      goto gt_another_svalue;
    }
    else if (cin >> d_wdamount && d_wdamount < 0.01) {
      cout << "Error, withdraw amount must be greater than $0.00, please enter another value:\n>";
      goto gt_another_svalue;
    }
    else if (cin >> d_wdamount && d_wdamount > acct.d_balance) {
      cout << "Error, not enough funds in account to complete transaction, please enter another value:\n>";
      goto gt_another_svalue;
    }
    else {
      cout << "Error, value entered is not a recognized number, please enter another value:\n>";
      goto gt_another_svalue;
    }
  }
  else {
    cout << "Error, invalid account number, killing withdraw request.";
  }
  return 0;
}


/*
  The Transfer function takes an Account Object as an argument
  The function will be used to transfer funds from an account that is given to another account.
  This function has 2 modes, an Admin Functionality and a Regular Account Holder Functionality

  The Admin Functionality will first prompt the admin for their full name to verify that the account
  is of type admin. If the admin account is not found the function will redirect the logged in user
  to the main menu. Once admin is verified, the admin will be able to transfer from an Account
  that they specify by the account number that they transfer funds from.

  The Regular Account Holder Functionality will verify that they have an account at the bank.
  This is done by prompting the account holder for their account number, the account number will
  then be compared to the account number in the account object. If the account number does not match
  the transaction will be terminated and the user will be sent back to the main menu.

  After proper data validation for both Admin and Regular Account Holder, the program will continue with
  the transaction, it will retrieve input for the account that they wish to transfer funds to. The entered
  account number will then be compared to the accounts file to make sure that the account exists with the
  bank. If the account entered does not exist the user will be notified and the transaction will be terminated.

  If the account number is valid, the amount will then be validated to ensure that the transaction will be completed.
  This is done by following the guidelines that the bank has in place for the transfer of funds.
      - Amount to be transffered will have to be greater than $0, and less than or equal to $1000
      - Amount to be transffered if decimal must be of 2 floating point values ($12.50 is allowed, not $12.509, etc)
      - Sufficient amount of funds exist in the account transferring funds from

*/
int transfer(account acct) {
  string s_firstname, s_lastname, s_fullname, sFromAcctNum, sToAcctNum;
  double d_trans_amount;
  account tToAccount;
  prompt_struct pr;
  bool want_name;
  if (acct.n_level == ADMIN_ACCOUNT) {
    cout << "Transfer mode selected, ";
    want_name = true;
    }
  else {
    cout << "Transfer mode selected, ";
    want_name = false;
  }
  pr = prompt(want_name, true, &acct, "transfer");
  sFromAcctNum = pr.prompt_number;
  if(!pr.is_valid)
  {
    return 1;
  }
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
  return 0;
}

/*
  The paybill function takes an account object as an argument.
  This function is used to pay bills that have been charged to a customer.
  The function has 2 modes for Admin Functionality and Regular Account Holder Functionality

  The Admin Functionality will first prompt the admin for their full name to verify that the account
  is of type admin. If the admin account is not found the function will redirect the logged in user
  to the main menu. Once admin is verified, the admin will be able to pay bills from an Account
  that they specify by account number.

  The Regular Account Holder Functionality will verify that they have an account at the bank.
  This is done by prompting the account holder for their account number, the account number will
  then be compared to the account number in the account object. If the account number does not match
  the transaction will be terminated and the user will be sent back to the main menu.

  After validation the account function will then prompt the user for the company that they wish to pay a bill
  to. The company must then be of a valid company that exists according to the requirements for the paybill function
  If the company does not exist, the transaction will be terminated and user will be returned to the main menu.

  If the company is valid, the user is requested for the amount that is to be paid to the company.
  The amount entered will then go through the validation functionality to ensure the transaction will be completed.
  Guidelines for Paybill Are as follows below.
      - Amount to be paid must be greater than $0 and less than or equal to $2000
      - Amount to be paid must be a value that has 2 precision of decimal places ($20.40, not $20.409)
      - Sufficient Amount of funds must exist in the account

*/
int paybill(account acct) {
  string s_firstname, s_lastname, s_fullname, s_acctnum, sCompany;
  string sa_valid_companies[] = { "Bright Light Electric Company", "EC", "Credit Card Company Q", "CQ", "Low Definition TV, Inc", "TV" };
  double d_pay_amount;
  bool want_name;
  prompt_struct pr;
  if (acct.n_level == ADMIN_ACCOUNT) {
    want_name = true;
  }
  else {
    want_name = false;
  }
  cout << "Pay bill command selected. ";
  pr = prompt(want_name, true, &acct, "pay bill");
  if(!pr.is_valid) {
    return 1;
  }
  s_acctnum = pr.prompt_number;
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
  return 0;
}

/*
  The Deposit function takes an Account Object as an argument
  The function will be used to deposit funds into an account that is given.
  This function has 2 modes, an Admin Functionality and a Regular Account Holder Functionality

  The Admin Functionality will first prompt the admin for their full name to verify that the account
  is of type admin. If the admin account is not found the function will redirect the logged in user
  to the main menu. Once admin is verified, the admin will be able to deposit funds into an Account
  that they specify by account number.

  The Regular Account Holder Functionality will verify that they have an account at the bank.
  This is done by prompting the account holder for their account number, the account number will
  then be compared to the account number in the account object. If the account number does not match
  the transaction will be terminated and the user will be sent back to the main menu.

  After proper data validation for both Admin and Regular Account Holder, the program will continue with
  the deposit, it will then make sure that the amount to be deposited is valid by bank guidelines.
    - Paper Transations Only ($5, $10, $20, $50, $100)


*/
int deposit(account acct) {
  string s_firstname, s_lastname, s_fullname, s_acctnum, sCompany;
  double d_deposit_amount;
  bool want_name;
  prompt_struct pr;
  if (acct.n_level == ADMIN_ACCOUNT) {
    want_name = true;
  }
  else {
    want_name = false;
  }
  cout << "Deposit command selected. ";
  pr = prompt(want_name, true, &acct, "deposit");
  if(!pr.is_valid) {
    return 1;
  }
  s_acctnum = pr.prompt_number;
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
  return 0;
}

/*
  The Create Account function will be taking an account object as an argument.
  This function is only accessible by an administrator account at the bank.

  If the account logged in does not have admin priviledges the transaction will be instantly
  terminated, and the user will be returned to the main menu.

  The account to be created will be stored into an account object.
  The new account holder's name will be requested first.
  An account holder name must be filled and be less than 20 characters.
  The account holder name must be unique to the bank, no duplicate names allowed.

  After Account Holder name is accepted an initial balance to the account can be added
  The balance must be greater than $0 and less than or equal to $99999.99

  An account number will then be randomly generated, the account will be set to active
  and the level of the account will be set.

*/

/*!*/int create(account acct)
{
  if (acct.n_level != ADMIN_ACCOUNT) {
    cout << "TOKEN";
    return 0;
  }

  account ac_newaccount;
  string s_first, s_last;
  while (s_first.empty() == true || s_last.empty() == true) {
    cout << "Enter the full name for the new account holder: ";
    cin >> s_first;
    cin >> s_last;
  }
  ac_newaccount.s_holdername = s_first + " " + s_last;
  while (ac_newaccount.s_holdername.length() > 20 || getAccountByName(ac_newaccount.s_holdername).s_holdername.empty() == false) {
    if (ac_newaccount.s_holdername.length() > 20) {
      cout << "The account name is too long. It must be at most 20 characters in length";
    }
    if (ac_newaccount.s_holdername.length() == 0) {
      cout << "The account name is empty. Please enter an account name";
    }
    cout << getAccountByName(ac_newaccount.s_holdername).s_holdername << endl;
    if (!getAccountByName(ac_newaccount.s_holdername).s_holdername.empty()) {
      cout << "This account name already exists. The account name must be unique in the system.";
      return 0;
    }
    cin >> ac_newaccount.s_holdername;
  }
  cout << "Enter the initial balance for the new account holder: ";
  cin >> ac_newaccount.d_balance;
  while (ac_newaccount.d_balance < 0 || ac_newaccount.d_balance > 99999.99) {
    cout << "The balance must be greater than $0.00 and less than or equal to $99999.99";
    cin >> ac_newaccount.d_balance;
  }

  ac_newaccount.c_status = 'A';
  ac_newaccount.n_level = 0;

  writeStandardAccount(ac_newaccount);
  return 0;

}

/*
  The ac_delete function takes an account object as an argument
  This function is only accessible by an administrator account, if account currently logged in
  is not an admin, the transaction will be instantly terminated, and user will be returned to the
  main menu.

  The program will then delete the account that is requested by the admin as long as they exist
  at the bank.

*/
/*!*/int ac_delete(account acct)
{
  if (acct.n_level != ADMIN_ACCOUNT) {
    cout << "TOKEN";
    return 0;
  }

  string s_holdername, s_number;
//  cout << "Enter the name of the account holder: ";
//  cin >> s_holdername;
//  cout << "Enter the account number of the account holder: ";
//  cin >> s_number;
  prompt_struct pr;
  pr = prompt(true, true, &acct, "delete");

  account acc_account = acct;
  s_holdername = pr.prompt_name;
  s_number = pr.prompt_number;

  if (acc_account.s_number.empty())
  {
    cout << "Account not found";
    return 0;
  }
  if (s_holdername.compare(acc_account.s_holdername) == 0) {
    // Match
    cout << "Account deleted (stub)";
    return 0;
  }
  else {
    cout << "Name and number provided do not match for this account. Aborting.";
    return 0;
  }



}

/*
  The disable function takes an account object as an argument.
  This function is accessible only by an admin account, if the account that is currently logged in
  is not an admin, the transaction will be terminated and the user will be returned to the main menu.

  The function will then prompt for the account that is to be disabled, this is done by prompting for
  the name and account number that correspond to each other. If the account is not found in the system
  the transaction is killed and the admin is returned back to the main menu.

  If the account is valid the account will be disabled.

*/
/*!*/int disable(account acct)
{
  if (acct.n_level != ADMIN_ACCOUNT) {
    cout << "TOKEN";
    return 0;
  }
  prompt_struct pr;

  string s_holdername, s_number;
//  cout << "Enter the name of the account holder: ";
//  cin >> s_holdername;
//  cout << "Enter the account number of the account holder: ";
//  cin >> s_number;

  pr = prompt(true,true,&acct, "disable");
  account acc_account = acct;
  s_holdername = pr.prompt_name;
  s_holdername = pr.prompt_number;

  if (acc_account.s_number.empty()) {
    cout << "Account not found";
    return 0;
  }

  if (s_holdername.compare(acc_account.s_holdername) == 0) {
    // Match
    cout << "Account disabled/enabled (stub)";
    return 0;
  }
  else {
    cout << "Name and number do not match for this account. Aborting.";
    return 0;
  }

}

/*
  The changeplan function will take an account object as an argument.
  This function is accessible only by an admin account, if the account that is currently logged in
  is not an admin, the transaction will be terminated and the user will be returned to the main menu.

  The changeplan function is used to change an account of a student type to a regular account type.

  This is done by prompting for an account number and account name that correspond to each other.
  If account name and number do not match the admin is returned to the main menu.

  Once the account is found the function will make sure that the type of account is of student.
  If it is not a student account the admin will be returned to the main menu.
  if the account is a student account it will be changed into a regular account.

*/
/*!*/int changeplan(account acct)
{
  if (acct.n_level != ADMIN_ACCOUNT) {
    cout << "TOKEN";
    return 0;
  }

  string s_holdername, s_number;
//  cout << "Enter the name of the account holder: ";
//  cin >> s_holdername;
//  cout << "Enter the account number of the account holder: ";
//  cin >> s_number;

  prompt_struct pr;
  pr = prompt(true, true, &acct, "changeplan");
  account acc_account = getAccountByNumber(s_number);
  s_holdername = pr.prompt_name;
  s_holdername = pr.prompt_number;

  if (acc_account.s_number.empty()) {
    cout << "Account not found";
    return 0;
  }

  if (s_holdername.compare(acc_account.s_holdername) == 0) {
    // Match
    cout << "Plan Changed (stub)";
    return 0;
  }
  else {
    cout << "Name and number do not match for this account. Aborting.";
    return 0;
  }

}

/*
  The logout function is used to terminate the session that is currently logged in.
  It will check if a user is logged in, in order to logout of the system.
  If logout is successful the user will recieve a message on the screen telling them that
  their session has been ended.
*/
int logout(bool b_logged_in) {
  if (b_logged_in) {
    cout << "Thank you for using the banking system, session ended, you have been successfully logged out.\n";
  }
  else {
    cout << "You must be logged in to log out.\n";
  }
  return 0;
}
