#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <iomanip>
#include <sstream>
#include "utilities.h"

using namespace std;
/*
  getAccountByName is a function that takes an account holder name, and a filename as an argument.
  This function is used to retrieve information from an account by the name of the account holder.
  The account holder name is searched for in the accounts textfile, once found it will grab the
  line that the account holder name was found and store all the information on that line into
  an account object.
*/
account getAccountByName( string s_holdername, string s_filename ) {

  // ----------Major Variables------------
  account acct;
  string s_account_line;
  string s_line_handler;
  bool b_matched_line;
  // ----------End Major Variables--------

  ifstream ifs_accounts_file;
  ifs_accounts_file.open( s_filename );
  getline( ifs_accounts_file, s_account_line );
  
  while (s_account_line != "") {
    // Matched s_holdername to a substring in the file.
    b_matched_line = ( s_holdername.compare( s_account_line.substr( 6, s_holdername.length() ) ) == 0 );

    if ( b_matched_line ) {
      acct.s_holdername = s_holdername;
      acct.n_level = STANDARD_ACCOUNT;
      acct.s_number = s_account_line.substr( 0, 5 );
      acct.c_status = s_account_line.at( 27 );
      acct.d_balance = stod(s_account_line.substr( 29, 36 ) );
      // cout << acct.s_holdername << endl;
      // cout << acct.n_level << endl;
      // cout << acct.s_number << endl;
      // cout << acct.c_status << endl;
      // cout << acct.d_balance << endl;
    }
    getline( ifs_accounts_file, s_account_line );
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
account getAccountByNumber( string s_number, string s_filename ) {

  // ----------Major Variables------------
  account acct;
  string s_account_line;
  string s_line_handler;
  bool b_matched_line;
  // ----------End Major Variables--------

  ifstream ifs_accounts_file;
  ifs_accounts_file.open( s_filename );
  getline( ifs_accounts_file, s_account_line );
  
  while (s_account_line != "") {
    // Matched s_holdername to a substring in the file.
    b_matched_line = ( s_number.compare( s_account_line.substr( 0, s_number.length() ) ) == 0 );

    if ( b_matched_line ) {
      acct.s_holdername = s_account_line.substr(6, 20);
      acct.n_level = STANDARD_ACCOUNT;
      acct.s_number = s_number;
      acct.c_status = s_account_line.at( 27 );
      acct.d_balance = stod(s_account_line.substr( 29, 36 ) );
      // cout << acct.s_holdername << endl;
      // cout << acct.n_level << endl;
      // cout << acct.s_number << endl;
      // cout << acct.c_status << endl;
      // cout << acct.d_balance << endl;
    }
    getline( ifs_accounts_file, s_account_line );
  }
  return acct;
}

/*
  This function is used to compare 2 strings and will return true if the strings match.
*/
bool contains( vector<string> sa_values, string value ) {
  bool found = false;
  for (const string &sa_value : sa_values) {
    if ( sa_value.compare( value ) == 0 )
    {
      found = true;
      break;
    }
  }
  return found;
}

// Find and validate user account (used by admins). This function will prompt the admin user for account details and if an account is found, this will return an account struct containing the user data.
account getUserAccount() {

  // ----------Major Variables------------
  string s_first, s_last, s_holdername, s_number;
  account acc_blank;
  // ----------End Major Variables--------

  // ----------PROMPT---------------------
  while ( s_first.empty() == true || s_last.empty() == true ) {
    cout << "Enter the full name for the account holder:" << endl;
    cin >> s_first;
    if ( s_first.compare( "quit" ) == 0 ) {
      exit( 0 );
    }
    cin >> s_last;
    if ( s_last.compare( "quit" ) == 0 ) {
      exit( 0 );
    }
  }
  s_holdername = s_first + " " + s_last;
  cout << "Enter the account number of the account holder: " << endl;;
  cin >> s_number;
  if ( s_number.compare( "quit" ) == 0 ) {
    exit( 0 );
  }
  //----------END PROMPT------------------

  //----------VALIDATION------------------
  account acc_account = getAccountByNumber( s_number );
  if ( acc_account.s_number.empty() ) {
    cout << "Account not found" << endl;
    return acc_blank;
  }
  else if ( s_holdername.compare( acc_account.s_holdername ) == 0 ) {
    cout << "Provided holder name and account holder names do not match." << endl;
    return acc_blank;
  }
  //----------END VALIDATION--------------
  return acc_account;
}

// Comparison of account number and input number. Returns TRUE if they match, FALSE if they do not.
bool userValidation( string s_accountNumber ) {
  // ----------Major Variables------------
  string s_number;
  // ----------End Major Variables--------

  // ------------PROMPT AND VALIDATION-----------
  cout << "Please enter your account number:" << endl;
  cin >> s_number;

  if ( s_number.compare( "quit" ) == 0 ) {
    exit( 0 );
  }

  if ( s_number.compare( s_accountNumber ) != 0 ) {
    // No Match
    cout << "The account number entered does not match the number on file. Aborting." << endl;
    return false;
  }
  // ------------END PROMPT AND VALIDATION-------
return true;
}


int writeStandardAccount( account acct, string s_filename ) {
  cout << "New account created with accountname " + acct.s_holdername + "( stub )" << endl;
  return 0;
}

int updateStandardAccount( account acct, string s_filename ) {
  cout << "Account Updated ( stub )" << endl;
  return 0;
}

int writeTransactionFile( string transaction ) {

  int t_count;
  //file will be created with an initial value of 0 every day,
  // if not set, program will create the file, and place a garbage initial value. It will still work
  // but number will be whatever is stored in memory.
  string highest_count_name = "num_transactions_thusfar.txt";
  ifstream trans_count;
  trans_count.open(highest_count_name);
  trans_count >> t_count;
  trans_count.close();
  string file_name = "trans" + to_string(t_count) + ".txt";

  ofstream trans_file;
  ofstream highest_count;

  trans_file.open(file_name);
  highest_count.open(highest_count_name);
  trans_file << transaction << endl;
  highest_count << t_count + 1 << endl;
  trans_file.close();
  cout << "Transaction File written ( stub )" << endl;
  return 0;
}

// Attempt to cast a string to a double. Throws errors if it can't happen.
double attempt_conversion( std::string s_1 ) {
 try {
  stod( s_1 );
  } 
  catch ( const std::invalid_argument& ) {
    cout << "Argument is invalid" << endl;
    return -1337;
  } 
  catch ( const std::out_of_range& ) {
    cout << "Argument is out of range for a double" << endl;
    return -1337;
  }
  return stod( s_1 );
}

string transaction_to_string(transaction t){
	string acct_as_string;
	stringstream s;
	s << fixed << setprecision(2) << t.d_funds_involved;
	string val = s.str();
	acct_as_string = t.trasaction_code + " "
			+ t.account_holder_name.append(20 - t.account_holder_name.length(), ' ') + " "
			+ t.s_acct_number + " "
			+ val.append(8 - val.length(), '0') + " " + t.s_misc_info;
	return acct_as_string;
}

int write_to_transaction(transaction* t, account a, string trans_code, double funds, string misc){
		t->account_holder_name = a.s_holdername;
	    t->d_funds_involved = funds;
	    t->trasaction_code = trans_code;
	    t->s_acct_number = a.s_number;
	    t->s_misc_info = misc;
	    return 0;
}
