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

  // Get a constant copy to all items in the store.
  const Map<std::string, Item> get_items() const;

  // Checkout a cart (aka a list of items)
  void checkout(const List<Item>& items, bool silent);

  // Add a new item to the store or update an existing one
  void add_item(std::string item, int amount);

  friend std::ostream& operator<<(std::ostream& os, const Store& obj);

private:
  const std::string filename;
  Map<std::string, Item> items;
};

void add_items_to_store(Store& store, List<Item> items);

#endif
