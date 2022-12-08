#include "cart.hpp"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

#include "ui.hpp"

Cart::Cart(const Store& store) : store(store.get_items()) {}

void Cart::add_item(std::string item, int amount)
{
  if (item.empty())
  {
    std::cout << "Must specify item to buy\n";
    return;
  }
  auto it = store.find(item);
  if (it != store.end())
  {
    auto existing_item = items.find(item);
    if (existing_item != items.end())
    {
      amount += existing_item->second;
    }
    if (amount > it->second.quantity)
    {
      std::cout << "Store does not have enough stock of this item\n";
      return;
    }
    items.insert(item, amount);
    std::cout << "Added to cart\n";
  }
  else
  {
    std::cout << item << " not found in store\n";
  }
}

void Cart::remove_item(std::string item, int amount)
{
  if (item.empty())
  {
    std::cout << "Must specify item to delete\n";
    return;
  }
  auto it = items.find(item);
  if (it != items.end())
  {
    auto store_item = *it;
    if (store_item.second > 1 && amount == 0)
    {
      std::cout << "You have " << store_item.second
                << " of these in your cart.\n";
      amount = get_int("How many do you want to remove?", 1, store_item.second);
    }
    if (store_item.second - amount < 0)
    {
      std::cout << "Removing all " << item << " from cart\n";
    }
    if (store_item.second - amount <= 0)
    {
      items.erase(it);
    }
    else
    {
      auto current = items.find(store_item.first)->second;
      items.insert(item, current - amount);
    }
    std::cout << "Removed from cart\n";
  }
  else
  {
    std::cout << item << " not found in cart\n";
  }
}

const Map<std::string, int> Cart::get_items() const { return items; }

std::ostream& operator<<(std::ostream& os, const Store& obj)
{
  const std::string row_boundary = std::string(52, '-');
  os << row_boundary << "\n";
  os << "|" << center("Item", 25) << "|" << center("Quantity", 12) << "|"
     << center("Price", 11) << "|\n";
  os << row_boundary << "\n";
  auto iter = obj.items.begin();
  while (iter != obj.items.end())
  {
    const auto& item = iter->second;
    os << "|" << center(item.name, 25) << "|"
       << center(std::to_string(item.quantity), 12) << "|"
       << center(dollars(item.price), 11) << "|\n"
       << row_boundary << "\n";
    ++iter;
  }

  return os;
}

std::ostream& operator<<(std::ostream& os, const Cart& obj)
{
  double total = 0;

  if (obj.items.empty())
  {
    std::cout << "Cart is empty!\n";
    return os;
  }
  const std::string row_boundary = std::string(52, '-');
  os << row_boundary << "\n";
  os << "|" << center("Item", 25) << "|" << center("Quantity", 12) << "|"
     << center("Price", 11) << "|\n";
  os << row_boundary << "\n";
  for (const auto& item : obj.items)
  {
    const auto& store_item = obj.store.find(item.first)->second;
    total += store_item.price * item.second;
    os << "|" << center(store_item.name, 25) << "|"
       << center(std::to_string(item.second), 12) << "|"
       << center(dollars(store_item.price * item.second), 11) << "|\n"
       << row_boundary << "\n";
  }

  os << "Total: " << dollars(total) << "\n";

  return os;
}
