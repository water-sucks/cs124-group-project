#include "flows.hpp"

#include "structures/queue.hpp"
#include "ui.hpp"

#include <climits>
#include <fstream>
#include <iostream>
#include <sstream>

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
  Cart cart(store);

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
    int amount;

    // These will be empty if none are provided
    ss >> command;
    ss >> item;

    // Read number and default to 1 if not provided or invalid
    ss >> amount;
    if (ss.fail())
    {
      amount = 1;
    }

    // Run function depending on command
    // Show menu
    if (command == "help")
    {
      std::cout << HELP;
    }
    // Search for an item in the store
    else if (command == "search")
    {
      store.search(item);
    }
    // Show all items in store
    else if (command == "inventory")
    {
      std::cout << store << "\n";
    }
    // Add item to cart
    else if (command == "add")
    {
      cart.add_item(item, amount);
    }
    // Remove item from cart
    else if (command == "delete")
    {
      cart.remove_item(item, amount);
    }
    // Show all items in cart and total
    else if (command == "cart")
    {
      std::cout << cart << "\n";
    }
    // Proceed to checkout flow
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

List<Item> giving_flow()
{
  List<Item> items;

  bool done = false;

  while (!done)
  {
    std::string name = get_string("What is the name of the item?");
    int quantity = get_int("How many of this item do you have?", 1, INT_MAX);

    std::cout << "Added item to list\n";

    items.push_back(Item(name, quantity, 0.0));

    done = !confirm("Do you have any more more items");
  }

  return items;
}

List<Item> build_item_list_from_line(const Store& store, std::string line)
{
  std::stringstream ss(line);

  std::string name;
  int quantity;

  List<Item> items;

  const auto store_items = store.get_items();

  while (ss >> name >> quantity)
  {
    auto it = store_items.find(name);
    if (it != store_items.end())
    {
      items.push_back(Item(name, quantity, it->second.price));
    }
  }

  return items;
}

void checkout_flow(Store& store, const Cart& cart)
{
  Queue<List<Item>> queue;

  std::ifstream queue_file;
  queue_file.open("./assets/queue.txt");

  std::string line;
  while (getline(queue_file, line))
  {
    queue.push(build_item_list_from_line(store, line));
  }

  while (!queue.empty())
  {
    List<Item> items = queue.front();
    queue.pop();
    store.checkout(items, false);
  }

  queue_file.close();

  List<Item> items;

  auto store_items = store.get_items();

  for (const auto& item : cart.get_items())
  {
    double price = store_items.find(item.first)->second.price;
    items.push_back(Item(item.first, item.second, price));
  }

  store.checkout(items, true);
}
