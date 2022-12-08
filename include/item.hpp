#ifndef _ITEM_H_
#define _ITEM_H_

#include <string>
#include <vector>

struct Item
{
  Item();
  Item(std::string name, int quantity, double price);

  bool operator>(const Item& other);

  std::string name = "";
  int quantity = 0;
  double price = 0;
};

// void heapsort(Item items[], std::size_t length);
void merge_sort(std::vector<std::string>& vector, std::size_t from,
                std::size_t to);

#endif
