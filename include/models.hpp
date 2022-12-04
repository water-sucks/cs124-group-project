#ifndef _MODELS_H_
#define _MODELS_H_

#include <map>
#include <string>

struct Item
{
  explicit Item(std::string name, int quantity, double price);

  std::string name = "";
  int quantity = 0;
  double price = 0;
};

typedef std::map<std::string, Item> Store;
typedef std::map<std::string, int> Cart;

#endif
