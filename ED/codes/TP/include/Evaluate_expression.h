#include <iostream>
#include <string.h>

int priority(char c);

std::string infix_to_postfix(std::string st, std::string values);

bool evaluate(std::string st, std::string values);
