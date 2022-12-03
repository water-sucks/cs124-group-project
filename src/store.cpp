#include "store.hpp"

#include "structures/list.hpp"

#include <fstream>
#include <iostream>
#include <map>
#include <sstream>

Item::Item(std::string name, int quantity, double price)
    : name(name), quantity(quantity), price(price)
{}

Item::Item(const Item& other) {}

Items load_items(std::string filename)
{
  std::ifstream file;
  file.open(filename);

  Items items;

  if (!file)
  {
    return items;
  }

  std::string line;

  while (getline(file, line))
  {
    std::string item_name;
    int quantity;
    double price;

    std::istringstream ss(line);

    ss >> item_name;
    ss >> quantity;
    ss >> price;

    items.insert({item_name, Item(item_name, quantity, price)});
  }

  file.close();

  return items;
}

bool add_item(const Items& store, std::map<std::string, int>& items,
              std::string item)
{
  auto lean = store.find(item);
  if (lean != store.end())
  {
    items[item] = items[item] + 1;
    return true;
  }
  return false;
}

List<Item> get_items(Items store)
{
  std::map<std::string, int> items;
  List<Item> cart;

  for (int i = 0; i < 3; i++)
  {
    std::string item;

    std::cout << "Enter item to add to list: ";
    std::cin >> item;

    if (add_item(store, items, item))
    {
      std::cout << "Added item!\n";
    }
    else
    {
      std::cout << "Unable to add " << item << ", does not exist!\n";
    }
  }

  for (const auto& kv : items)
  {
    auto thing = store["thing"];
    // Item item = Item(kv.first, kv.second, store[kv.first].price);
    // cart.push_back(item);
  }

  return cart;
}