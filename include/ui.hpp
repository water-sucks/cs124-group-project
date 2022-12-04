#ifndef _UI_H_
#define _UI_H_

#include "models.hpp"

std::string dollars(double num);
bool confirm(const std::string& prompt);
void show_cart(const Store& store, const Cart& cart);
void show_store(const Store& store);
int get_int(const std::string& prompt, int min, int max);

#endif
