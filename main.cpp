#include "store.hpp"

#include <iostream>

int main()
{
  Items items = load_items("assets/store.txt");

  for (const auto& item: get_items(items))
  {
    std::cout << item.name << "\n";
  }

  return 0;
}