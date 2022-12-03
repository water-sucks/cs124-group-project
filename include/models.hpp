#ifndef _MODELS_H_
#define _MODELS_H_

struct Item
{
  Item(std::string name, int quantity, double price);
  Item(const Item& other);

  std::string name;
  int quantity;
  double price;
};

#endif