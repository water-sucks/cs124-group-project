#ifndef _STORE_H_
#define _STORE_H_

#include "item.hpp"
#include "structures/map.hpp"

class Store
{
public:
  Store(const std::string& filename);

  void search(const std::string& item) const;

  // Load items from store file, overwriting any previous contents of items
  void load();

  // Persist current items to file, overwriting it
  void persist();

  const Map<std::string, Item> get_items() const;

  // Checkout a cart (aka a list of items)
  // void checkout()

  // Add a new item to the store or update an existing one
  // void add_item(std::string item, int amount);

  // Remove an item from the store if it exists
  // void remove_item(std::string item, int amount)

  friend std::ostream& operator<<(std::ostream& os, const Store& obj);

private:
  const std::string filename;
  Map<std::string, Item> items;
};

#endif
