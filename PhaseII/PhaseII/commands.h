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

void menu(account acct); 
void withdrawal(account acct);
void transfer(account acct);
void paybill(account acct);
void deposit(account acct);
void create(account acct);
void ac_delete(account acct);	//delete is a key word in C++
void disable(account acct);
void changeplan(account acct);
void logout(bool b_loggedin);

#endif // COMMANDS_H_