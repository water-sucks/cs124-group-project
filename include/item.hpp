#ifndef _ITEM_H_
#define _ITEM_H_

#include <string>

struct Item
{
  explicit Item(std::string name, int quantity, double price);

  std::string name = "";
  int quantity = 0;
  double price = 0;
};

#endif
