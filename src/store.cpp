#include "store.hpp"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

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

  auto iter = items.begin();
  while (iter != items.end())
  {
    auto item = iter->second;
    if (item.quantity == 0)
    {
      iter = items.erase(iter);
      continue;
    }
    file << item.name << "    " << item.quantity << "    " << std::fixed
         << std::setprecision(2) << std::setfill('0') << item.price << "\n";
    ++iter;
  }

  file.close();
}

const Map<std::string, Item> Store::get_items() const { return items; }
