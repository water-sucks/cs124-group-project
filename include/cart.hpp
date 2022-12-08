#ifndef _CART_H_
#define _CART_H_

#include "store.hpp"
#include <string>

class Cart
{
public:
  explicit Cart(const Store& store);

  // Add item to cart with bounds checking
  void add_item(std::string item, int amount);
  // Remove item from cart with bounds checking
  void remove_item(std::string item, int amount);

  // Get a const snapshot of all the items in the cart
  const Map<std::string, int> get_items() const;

  // Representation of the cart in table form
  friend std::ostream& operator<<(std::ostream& os, const Cart& obj);

private:
  const Map<std::string, Item> store;
  Map<std::string, int> items;
};

#endif
