#include "buy.hpp"

#include <iostream>

int main()
{
  Store store = load_items("assets/store.txt");

  Cart cart = shopping_flow(store);
  for (const auto& item : cart)
  {
    std::cout << item.first << ": " << item.second << "\n";
  }

  return 0;
}
