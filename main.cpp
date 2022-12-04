#include "buy.hpp"

#include <iostream>

int main()
{
  Store store = load_items("assets/store.txt");

  for (const auto& item : store)
  {
    std::cout << item.first << ": " << item.second.name << "\n";
  }

  Cart cart = shopping_flow(store);
  for (const auto& item : cart)
  {
    std::cout << item.first << ": " << item.second << "\n";
  }

  return 0;
}
