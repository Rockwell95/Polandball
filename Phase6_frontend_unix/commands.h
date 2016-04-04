#ifndef COMMANDS_H_
#define COMMANDS_H_
#include <string>
//...
typedef struct {
  int n_level;	// 0 for standard, 1 for admin
  std::string s_number;
  std::string s_holdername;
  char c_status;
  double d_balance;
  bool b_freezetransactions;
}account;

typedef struct {
  std::string trasaction_code;
  std::string account_holder_name;
  std::string s_acct_number;
  double d_funds_involved;
  std::string s_misc_info;
}transaction;

int menu( account acct );
int withdrawal( account acct );
int transfer( account acct );
int paybill( account acct );
int deposit( account acct );
int create( account acct );
int ac_delete( account acct );	//delete is a key word in C++
int disable( account acct );
int enable(account acct);
int changeplan( account acct );
int logout( bool b_loggedin );

#endif // COMMANDS_H_
