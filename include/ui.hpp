#ifndef _UI_H_
#define _UI_H_

#include <string>

std::string dollars(double num);
std::string center(const std::string& str, int width);
bool confirm(const std::string& prompt);
int get_int(const std::string& prompt, int min, int max);
std::string get_string(const std::string& prompt);

#endif
