#ifndef UTILITIES_H_
#define UTILITIES_H_
#include "commands.h"
#include <string>

account getAccountInfo(std::string ssHolderName);
account getAccountByNumber(std::string ssNumber);

#endif // UTILITIES_H_