#include "buy.hpp"

#include "ui.hpp"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <sstream>

Item::Item(std::string name, int quantity, double price)
    : name(name), quantity(quantity), price(price)
{}

Store load_items(std::string filename)
{
  std::ifstream file;
  file.open(filename);

  Store items;

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

    items.insert(item_name, Item(item_name, quantity, price));
  }

  file.close();

  return items;
}

void add_item(const Store& store, Cart& cart, std::string item,
              std::string amount)
{
  if (item.empty())
  {
    std::cout << "Must specify item to buy\n";
    return;
  }
  auto it = store.find(item);
  if (it != store.end())
  {
    int to_add = 1;
    if (!amount.empty())
    {
      try
      {
        to_add = std::stoi(amount);
      } catch (...)
      {
        std::cout << "Invalid amount entered, default to 1\n";
      }
    }
    auto existing_item = cart.find(item);
    if (existing_item != cart.end())
    {
      to_add += existing_item->second;
    }
    if (to_add > it->second.quantity)
    {
      std::cout << "Store does not have enough stock of this item\n";
      return;
    }
    // cart[item] = cart[item] + to_add;
    cart.insert(item, to_add);
    std::cout << "Added to cart\n";
  }
  else
  {
    std::cout << item << " not found in store\n";
  }
}

void find_item(const Store& store, std::string item)
{
  if (item.empty())
  {
    std::cout << "Must specify item to search for\n";
    return;
  }
  auto it = store.find(item);
  if (it != store.end())
  {
    std::cout << "Found " << item << " in store for "
              << dollars(it->second.price) << "\n";
  }
  else
  {
    std::cout << item << " not found in store\n";
  }
}

void remove_item(Cart& cart, std::string item, std::string amount)
{
  if (item.empty())
  {
    std::cout << "Must specify item to delete\n";
    return;
  }
  auto it = cart.find(item);
  if (it != cart.end())
  {
    auto store_item = *it;
    int to_remove = 0;
    if (!amount.empty())
    {
      try
      {
        to_remove = std::stoi(amount);
      } catch (...)
      {
        std::cout << "Invalid amount entered\n";
      }
    }
    if (store_item.second > 1 && to_remove == 0)
    {
      std::cout << "You have " << store_item.second
                << " of these in your cart.\n";
      to_remove =
          get_int("How many do you want to remove?", 1, store_item.second);
    }
    // Removing more items than there are in cart
    // TODO: figure out better message later
    if (store_item.second - to_remove < 0)
    {
      std::cout << "Removing all " << item << " from cart\n";
    }
    if (store_item.second - to_remove <= 0)
    {
      cart.erase(it);
    }
    else
    {
      auto current = cart.find(store_item.first)->second;
      cart.insert(item, current - to_remove);
    }
    std::cout << "Removed from cart\n";
  }
  else
  {
    std::cout << item << " not found in cart\n";
  }
}

const std::string HELP =
    "Commands: \n"
    "  - help :: show this menu\n"
    "  - inventory :: show all available items in store\n"
    "  - search <item> :: find if item exists\n"
    "  - add <item> [amount = 1] :: add item to cart\n"
    "  - delete <item> [amount = 1] :: delete item from cart if it exists\n"
    "  - cart :: show items in cart\n"
    "  - checkout :: finish adding items and go to checkout\n";

Cart shopping_flow(const Store& store)
{
  Cart cart;

  std::cout << HELP;
  bool done = false;

  while (!done)
  {
    std::string input;

    std::cout << ">>> ";
    getline(std::cin, input);

    // Read command in as first word froms stringstream
    std::stringstream ss(input);
    std::string command;
    std::string item;
    std::string amount;

    // These will be empty if none are provided;
    ss >> command;
    ss >> item;
    ss >> amount;

    // Run function depending on command
    if (command == "help")
    {
      std::cout << HELP;
    }
    else if (command == "search")
    {
      find_item(store, item);
    }
    else if (command == "inventory")
    {
      show_store(store);
    }
    else if (command == "add")
    {
      add_item(store, cart, item, amount);
    }
    else if (command == "delete")
    {
      remove_item(cart, item, amount);
    }
    else if (command == "cart")
    {
      show_cart(store, cart);
    }
    else if (command == "checkout")
    {
      done = true;
    }
    else
    {
      std::cout << "Invalid command; type help for a list of commands\n";
    }
  }

  return cart;
}
