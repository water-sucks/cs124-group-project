#include "store.hpp"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

#include "ui.hpp"

Store::Store(const std::string& filename) : filename(filename) {}

void Store::search(const std::string& item) const
{
  if (item.empty())
  {
    std::cout << "must specify item to search for\n";
    return;
  }
  auto it = items.find(item);
  if (it != items.end())
  {
    std::cout << "found " << item << " in store for "
              << dollars(it->second.price) << "\n";
  }
  else
  {
    std::cout << item << " not found in store\n";
  }
}

void Store::load()
{
  std::ifstream file;
  file.open(filename);

  if (!file)
  {
    return;
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

    items.insert(item_name, Item(item_name, quantity, price));
  }

  file.close();
}

void Store::persist()
{
  std::ofstream file;
  file.open(filename, std::ios::trunc);

  if (!file)
  {
    return;
  }

  std::vector<std::string> rows;

  auto iter = items.begin();
  while (iter != items.end())
  {
    auto item = iter->second;
    if (item.quantity == 0)
    {
      iter = items.erase(iter);
      continue;
    }
    std::stringstream ss;
    ss << item.name << "    " << item.quantity << "    " << std::fixed
       << std::setprecision(2) << std::setfill('0') << item.price << "\n";
    rows.push_back(ss.str());
    ++iter;
  }

  merge_sort(rows, 0, rows.size() - 1);

  for (const auto& row : rows)
  {
    file << row;
  }

  file.close();
}

void Store::add_item(std::string item, int amount)
{
  if (item.empty())
  {
    return;
  }

  double price;

  auto it = items.find(item);
  if (it != items.end())
  {
    amount += it->second.quantity;
    price = it->second.price;
  }
  else
  {
    std::cout << item << " is not in the store yet.\n";
    price = get_price("Enter a price for this item");
  }

  items.insert(item, Item(item, amount, price));
}

void Store::checkout(const List<Item>& items, bool interactive)
{
  double total = 0;

  for (const auto& item : items)
  {
    Item store_item = this->items.find(item.name)->second;
    if (item.quantity > store_item.quantity)
    {
      if (interactive)
      {
        std::cout << "Not enough stock for " << item.name << ", skipping\n";
        continue;
      }
    }
    if (store_item.quantity - item.quantity == 0)
    {
      auto it = this->items.find(item.name);
      this->items.erase(it);
    }
    else
    {
      this->items.insert(
          item.name,
          Item(item.name, store_item.quantity - item.quantity, item.price));
    }
    total += item.quantity * item.price;
  }

  if (interactive)
  {
    std::cout << "Total: " << dollars(total) << "\n";
  }
}

const Map<std::string, Item> Store::get_items() const { return items; }

void add_items_to_store(Store& store, List<Item> items)
{
  for (const auto& item : items)
  {
    store.add_item(item.name, item.quantity);
  }
}
