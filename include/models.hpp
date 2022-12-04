#ifndef _MODELS_H_
#define _MODELS_H_

#include "structures/map.hpp"
#include <string>

struct Item
{
  explicit Item(std::string name, int quantity, double price);

  std::string name = "";
  int quantity = 0;
  double price = 0;
};

typedef Map<std::string, Item> Store;
typedef Map<std::string, int> Cart;

#endif
