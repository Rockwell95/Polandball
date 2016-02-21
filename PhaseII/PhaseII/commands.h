#ifndef COMMANDS_H_
#define COMMANDS_H_
#include <string>
//...
typedef struct {
  int nLevel;	// 0 for standard, 1 for admin
  std::string sNumber;
  std::string sHolderName;
  char cStatus;
  double dBalance;
}account;

void menu(account acct); 
void withdrawal(account acct);
void transfer(account acct);
void paybill(account acct);
void deposit(account acct);
void create(account acct);
void delte(account acct);	//delete is a key word in C++
void disable(account acct);
void changeplan(account acct);
void logout(bool bLoggedIn);

#endif // COMMANDS_H_