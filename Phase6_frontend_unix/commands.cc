#include "utilities.h"
#include <stdlib.h>
#include <iostream>
#include <iomanip>
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

  // ----------Major Variables------------
  string s_command;
  bool b_logged_in = true;
  // ----------End Major Variables--------

  // ----------MAIN MENU------------------
  while ( true ) {
    cout << "Ready..." << endl;
    cin >> s_command;
    if ( s_command.compare( "quit" ) == 0) {
      exit( 0 );
    }
    else if ( s_command.compare( "withdrawal" ) == 0 ) {
      withdrawal( acct );
    }
    else if ( s_command.compare( "transfer" ) == 0 ) {
      transfer( acct );
    }
    else if ( s_command.compare( "paybill" ) == 0 ) {
      paybill( acct );
    }
    else if ( s_command.compare( "deposit" ) == 0 ) {
      deposit( acct );
    }
    /*!*/else if ( s_command.compare( "create" ) == 0 ) {
      create(acct);
    }
    /*!*/else if ( s_command.compare("delete") == 0) {
      ac_delete( acct );
    }
    /*!*/else if ( s_command.compare( "disable" ) == 0 ) {
      disable( acct );
    }
    /*!*/else if( s_command.compare( "enable" ) == 0 ) {
    	enable( acct );
    }
    /*!*/else if ( s_command.compare( "changeplan" ) == 0 ) {
      changeplan( acct );
    }
    else if ( s_command.compare( "logout" ) == 0 ) {
      logout( b_logged_in );
      if ( b_logged_in )
      {
        return 0;
      }
    }
    else {
      cout << "Invalid entry, terminating session. You will now be logged out." << endl;
      return 0;
    }
  }
  // ----------END MAIN MENU---------------
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
int withdrawal( account acct ) {
  
  // ----------Major Variables------------
  string s_number;
  string s_withdrawamt;
  double d_wdamount = -1337;
  account acc_account;
  transaction t;
  // ----------End Major Variables--------


  if ( acct.n_level == ADMIN_ACCOUNT ) {
    // ----------PROMPT AND VALIDATION------
    acc_account = getUserAccount();
    acct = acc_account;
    if ( acc_account.s_number.empty() )  {
      return 0;
    }
    // ----------END PROMPT AND VALIDATION--
  }
  else {
    cout << "Withdraw command selected." << endl;
    // ----------PROMPT AND VALIDATION------
    if ( !userValidation( acct.s_number ) )
    {
      return 0;
    }
    // ----------END PROMPT AND VALIDATION--
  }
  
  // ------------PROMPT WITHDRAW------------
  while ( true ) {
    cout << "Enter an amount with withdraw. Example: 500.00." << endl;
    cin >> s_withdrawamt;
    d_wdamount = attempt_conversion(s_withdrawamt);
    if (s_withdrawamt.compare( "quit" ) == 0) {
      exit( 0 );
    }
    else if ( d_wdamount == -1337 ) {
      cout << "Balance cannot be set to that." << endl;
    }
    else if ( d_wdamount > 500 ) {
      cout << "Error, withdraw amount exceeds $500.00, please enter another value:" << endl;      
    }
    else if ( d_wdamount < 0.01 ) {
      cout << "Error, withdraw amount must be greater than $0.00, please enter another value:" << endl;      
    }
    else if ( d_wdamount > acct.d_balance ) {
      cout << "Error, not enough funds in account to complete transaction, please enter another value:" << endl;      
    }
    else {
      break;
    }
  }
  // ------------END PROMPT WITHDRAW--------

  // ------------PROCESSING-----------------
    acct.d_balance -= d_wdamount;
    cout << "Withdraw complete. New Balance: $" << fixed << setprecision( 2 ) << acct.d_balance  << endl;
    write_to_transaction(&t, acct, "01", d_wdamount);
    string sTrans = transaction_to_string(t);
    writeTransactionFile(sTrans);
  // ------------END PROCESSING-------------
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
int transfer( account acct ) {
  
  // ----------Major Variables------------
  string sFromAcctNum, sToAcctNum, s_number;
  double d_trans_amount;
  account tToAccount;
  account acc_account;
  transaction t_from;
  transaction t_to;
  // ----------End Major Variables--------


  if ( acct.n_level == ADMIN_ACCOUNT ) {  
    // ----------PROMPT AND VALIDATION------
    acc_account = getUserAccount();
    acct = acc_account;

    if ( acc_account.s_number.empty() )  {
      return 0;
    }
    // ----------END PROMPT AND VALIDATION--
  }
  else {
    cout << "Transfer mode selected."  << endl;
    // ----------PROMPT AND VALIDATION------
    if ( !userValidation( acct.s_number ) )
    {
      return 0;
    }
    // ----------END PROMPT AND VALIDATION--
  }

  // ------------PROMPT TO ACCOUNT---------------
  while ( true ) {
    cout << "Please enter the number of the account to transfer to." << endl;
    cin >> sToAcctNum;
    if ( sToAcctNum.compare( "quit" ) == 0 ) {
      exit( 0 );
    }
    tToAccount = getAccountByNumber( sToAcctNum );
    if ( tToAccount.s_number.empty() ) {
      cout << "Target account does not exist. Please try a new number." << endl;
    }
    else {
      break;
    }
  }
  // ------------END PROMPT TO ACCOUNT-----------

  // ------------PROMPT AMOUNT-------------------
  while ( true ) {
    cout << "Please enter the amount you wish to transfer from " + acct.s_number + " to " + tToAccount.s_number + "." << endl;
    cin >> d_trans_amount;
    if ( d_trans_amount > 1000 ) {
        cout << "Transfer amount exceeds $1000.00, please enter another value." << endl;      
    }
    else if ( d_trans_amount < 0.01 ) {
      cout << "Transfer amount must be greater than $0.00, please enter another value." << endl;      
    }
    else if ( d_trans_amount > acct.d_balance ) {
      cout << "Error, not enough funds in account to complete transaction, please enter another value:" << endl;  
    }
    else {
      break;
    }
  }
  // ------------END PROMPT AMOUNT---------------

  // ------------PROCESSING----------------------
  acct.d_balance -= d_trans_amount;
  tToAccount.d_balance += d_trans_amount;
  cout << fixed;
  cout << setprecision( 2 );
  cout << "Transferring $" << fixed << setprecision( 2 ) << d_trans_amount << " from " + sFromAcctNum + " to " + sToAcctNum + "." << endl;
  cout << "Transfer complete, ending transaction..." << endl;
  cout << "Remaining Balance: $" << fixed << setprecision( 2 ) << acct.d_balance << endl;
  write_to_transaction(&t_from, acct, "01", d_trans_amount);
  write_to_transaction(&t_to, tToAccount, "04", d_trans_amount);
  string sTrans = transaction_to_string(t_from) + "\n" + transaction_to_string(t_to);
  writeTransactionFile(sTrans);
  // ------------END PROCESSING------------------
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
int paybill( account acct ) {

  // ----------Major Variables------------
  string sCompany, s_number;
  vector<string> sa_valid_companies = { "Bright Light Electric Company", "EC", "Credit Card Company Q", "CQ", "Low Definition TV, Inc", "TV" };
  double d_pay_amount;
  account acc_account;
  transaction t;
  // ----------End Major Variables--------

  if ( acct.n_level == ADMIN_ACCOUNT ) {
    // ----------PROMPT AND VALIDATION------
    acc_account = getUserAccount();
    acct = acc_account;
    if ( acc_account.s_number.empty() )  {
      return 0;
    }
    // ----------END PROMPT AND VALIDATION--
  }
  else {
    cout << "Pay bill command selected.";
    // ----------PROMPT AND VALIDATION------
    if ( !userValidation( acct.s_number ) )
    {
      return 0;
    }
    // ----------END PROMPT AND VALIDATION--
  }

  // ------------PROMPT COMPANY NAME-------------
  while ( true ) {
    cout << "Please enter the company name to pay:" << endl;
    cin >> sCompany;
    if ( contains( sa_valid_companies, sCompany ) == false ) {
      cout << "The company name is not a recognized company name." << endl;
    }
    else {
      break;
    }
  }
  // ------------END PROMPT COMPANY NAME---------

  while ( true ) {
    cout << "Please enter an amount to pay. Example: 500.00 :" << endl;
    cin >> d_pay_amount;
    if ( d_pay_amount == 0 )
    {
      return 0;
    }
    else if ( d_pay_amount > 2000 ) {
      cout << "The maximum amount that can be paid to a bill holder is $2000.00 in the current session. The amount entered exceeds $2000.00 " << endl;  
    }
    else if ( d_pay_amount < 0.01 ) {
      cout << "The minimum amount that can be paid to a bill holder is greater than $0.00 in the current session." << endl; 
    }
    else if ( d_pay_amount > acct.d_balance ) {
      cout << "The payment exceeds the current account balance. Payment has not been processed." << endl;  
    }
    else {
      break;
    }
  }
  // ------------PROMPT AMOUNT TO PAY------------
  acct.d_balance -= d_pay_amount;
  cout << "Payment Successful. ( stub )"  << endl;
  cout << "New Balance: $" <<  fixed << setprecision( 2 ) << acct.d_balance << endl;
  write_to_transaction(&t, acct, "03", d_pay_amount, sCompany);
  string sTrans = transaction_to_string(t);
  writeTransactionFile(sTrans);
  // ------------END PROCESSING------------------
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
    - Paper Transations Only ( $5, $10, $20, $50, $100 )


*/
int deposit( account acct ) {

  // ----------Major Variables------------
  string sCompany, s_number;
  double d_deposit_amount;
  account acc_account;
  transaction t;
  // ----------End Major Variables--------

  if ( acct.n_level == ADMIN_ACCOUNT ) {
    // ---PROMPT AND VALIDATION-----------
    acc_account = getUserAccount();
    acct = acc_account;
    if ( acc_account.s_number.empty() )  {
      return 0;
    }
    // ---END PROMPT AND VALIDATION-------
  }
  else {
    cout << "Deposit command selected.";
    // ----------PROMPT AND VALIDATION------
    if ( !userValidation( acct.s_number ) )
    {
      return 0;
    }
    // ----------END PROMPT AND VALIDATION--
  }

  // ------------DEPOSIT AMOUNT------------------
  while ( true ) {
    cout << "Please enter an amount to deposit"  << endl;
    cin >> d_deposit_amount;
    if ( d_deposit_amount == 0) {
      return 0;
    }   
    else if ( d_deposit_amount < 0.01) {
      cout << "Please enter a valid amount to deposit. Example: 200.00" << endl;    
    }
    else {
      break;
    }
  }
  // ------------END DEPOSIT AMOUNT--------------

  // ------------PROCESSING----------------------
  acct.d_balance += d_deposit_amount;
  cout << "Deposit successful." << endl;
  cout << "New Balance: $" << fixed << setprecision( 2 ) << acct.d_balance << endl;
  write_to_transaction(&t, acct, "04", d_deposit_amount);
  string sTrans = transaction_to_string(t);
  writeTransactionFile(sTrans);
  // ------------END PROCESSING-------------------    
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

/*!*/int create( account acct ) {

  // ----------AUTHENTICATION-------------
  if ( acct.n_level != ADMIN_ACCOUNT ) {
    cout << "You must be logged in as an admin to use this command" << endl;
    return 0;
  }
  // ----------END AUTHENTICATION---------

  // ----------Major Variables------------
  account ac_newaccount;
  ac_newaccount.d_balance = -1337;
  string s_first, s_last;
  string s_newbalance;
  transaction t;
  // ----------End Major Variables--------

  // ----------CREATE NAME----------------
  while ( true ) {
    cout << "Enter the full name for the new account holder:" << endl;
    cin >> s_first;

    if ( s_first.compare( "quit" ) == 0 ) {
      exit( 0 );
    }
    cin >> s_last;
    if ( s_last.compare( "quit" ) == 0 ) {
      exit( 0 );
    }

    ac_newaccount.s_holdername = s_first + " " + s_last;

    if ( ac_newaccount.s_holdername.length() > 20 ) {
      cout << "The account name is too long. It must be at most 20 characters in length." << endl;
    }
    else if ( ac_newaccount.s_holdername.length() == 0 ) {
      cout << "The account name is empty. Please enter an account name." << endl;
    }
    else if ( !getAccountByName( ac_newaccount.s_holdername ).s_holdername.empty() ) {
      cout << "This account name already exists. The account name must be unique in the system." << endl;
      return 0;
    }
    else {
      break;
    } 
  }
  // ----------END CREATE NAME------------

  // ----------INITIAL BALANCE------------
  while ( true ) {
    cout << "Enter the initial balance for the new account holder. Example: 500.00." << endl;
    cin >> s_newbalance;
    ac_newaccount.d_balance = attempt_conversion(s_newbalance);
    if ( s_newbalance.compare( "quit" ) == 0) {
      exit( 0 );
    }
    else if ( ac_newaccount.d_balance == -1337) {
      cout << "Balance cannot be set to that." << endl;
    }
    else if ( ac_newaccount.d_balance < 0 || ac_newaccount.d_balance > 99999.99 ) {
      cout << "The balance must be greater than or equal to $0.00 and less than or equal to $99999.99" << endl;     
    }
    else {
      break;
    }
  }
  // ----------END INITIAL BALANCE--------

  // ----------PROCESSING-----------------

  ac_newaccount.c_status = 'A';
  ac_newaccount.n_level = 0;
  ac_newaccount.s_number = "00000";
  writeStandardAccount( ac_newaccount );
  write_to_transaction(&t, ac_newaccount, "05", ac_newaccount.d_balance);
  string sTrans = transaction_to_string(t);
  writeTransactionFile(sTrans);
  // ----------END PROCESSING-------------
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
/*!*/int ac_delete( account acct ) {

  // ----------AUTHENTICATION-------------
  if ( acct.n_level != ADMIN_ACCOUNT ) {
    cout << "You must be logged in as an admin to use this command" << endl;
    return 0;
  }
  // ----------END AUTHENTICATION---------

  // ----------Major Variables------------
  account acc_account;
  transaction t;
  // ----------End Major Variables--------

  // ----------PROMPT AND VALIDATION------
  acc_account = getUserAccount();

  if ( acc_account.s_number.empty() )  {
    return 0;
  }
  // ----------END PROMPT AND VALIDATION--

  //----------PROCESSING------------------
  cout << "Account Deleted ( stub )" << endl;
  write_to_transaction(&t, acc_account, "06", 0);
  string sTrans = transaction_to_string(t);
  writeTransactionFile(sTrans);
  return 0;
  //----------END PROCESSING--------------


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
/*!*/int disable( account acct ) {
  // ----------AUTHENTICATION-------------
  if ( acct.n_level != ADMIN_ACCOUNT ) {
    cout << "You must be logged in as an admin to use this command" << endl;
    return 0;
  }
  // ----------END AUTHENTICATION---------

  // ----------Major Variables------------
  account acc_account;
  transaction t;
  // ----------End Major Variables--------

  // ----------PROMPT AND VALIDATION------
  acc_account = getUserAccount();

  if ( acc_account.s_number.empty() )  {
    return 0;
  }
  // ----------END PROMPT AND VALIDATION--

  //----------PROCESSING------------------
  cout << "Account Disabled ( stub )" << endl;
  write_to_transaction(&t, acc_account, "07", 0);
  string sTrans = transaction_to_string(t);
  writeTransactionFile(sTrans);
  return 0;
  //----------END PROCESSING--------------
}

/*!*/int enable(account acct){
	// ----------AUTHENTICATION-------------
	  if ( acct.n_level != ADMIN_ACCOUNT ) {
	    cout << "You must be logged in as an admin to use this command" << endl;
	    return 0;
	  }
	  // ----------END AUTHENTICATION---------

	  // ----------Major Variables------------
	  account acc_account;
	  transaction t;
	  // ----------End Major Variables--------

	  // ----------PROMPT AND VALIDATION------
	  acc_account = getUserAccount();

	  if ( acc_account.s_number.empty() )  {
	    return 0;
	  }
	  // ----------END PROMPT AND VALIDATION--

	  //----------PROCESSING------------------
	  cout << "Account Enabled ( stub )" << endl;
	  write_to_transaction(&t, acc_account, "09", 0);
	  string sTrans = transaction_to_string(t);
	  writeTransactionFile(sTrans);
	  return 0;
	  //----------END PROCESSING--------------
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
/*!*/int changeplan( account acct ) {

  // ----------AUTHENTICATION-------------
  if ( acct.n_level != ADMIN_ACCOUNT ) {
    cout << "You must be logged in as an admin to use this command" << endl;
    return 0;
  }
  // ----------END AUTHENTICATION---------

  // ----------Major Variables------------
  account acc_account;
  transaction t;
  // ----------End Major Variables--------

  // ----------PROMPT AND VALIDATION------
  acc_account = getUserAccount();

  if ( acc_account.s_number.empty() )  {
    return 0;
  }
  // ----------END PROMPT AND VALIDATION--

  //----------PROCESSING------------------
  cout << "Plan Changed ( stub )" << endl;
  write_to_transaction(&t, acc_account, "08", 0);
  string sTrans = transaction_to_string(t);
  writeTransactionFile(sTrans);
  return 0;
  //----------END PROCESSING--------------
}

/*
  The logout function is used to terminate the session that is currently logged in.
  It will check if a user is logged in, in order to logout of the system.
  If logout is successful the user will recieve a message on the screen telling them that
  their session has been ended.
*/
int logout( bool b_logged_in ) {
  if ( b_logged_in ) {
    cout << "You have been successfully logged out. Thank you for using the system, have a nice day." << endl;
  }
  else {
    cout << "You must first be logged in to log out." << endl;
  }
  return 0;
}
