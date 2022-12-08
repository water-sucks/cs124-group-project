#ifndef _CART_H_
#define _CART_H_

#include "store.hpp"
#include <string>

class Cart
{
public:
  explicit Cart(const Store& store);

  void add_item(std::string item, int amount);
  void remove_item(std::string item, int amount);

  friend std::ostream& operator<<(std::ostream& os, const Cart& obj);

private:
  const Map<std::string, Item> store;
  Map<std::string, int> items;
};

#endif
