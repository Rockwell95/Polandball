#ifndef UTILITIES_H_
#define UTILITIES_H_
#include "commands.h"
#include <string>

account getAccountInfo(std::string ssHolderName);
account getAccountByNumber(std::string ssNumber);
bool contains(std::string arrayOfValues[], std::string value);

#endif // UTILITIES_H_