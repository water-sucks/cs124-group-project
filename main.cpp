#include "flows.hpp"
#include "ui.hpp"

#include "structures/tree.hpp"

#include <iostream>

// clang-format off
const BinaryTree tree = BinaryTree(
  "Are you looking for fresh food?",
  BinaryTree(
    "Are you looking for meat?",
    BinaryTree(StoreSection::Meat),
    BinaryTree(StoreSection::Produce)
  ),
  BinaryTree(
    "Are you looking for frozen food?",
    BinaryTree(StoreSection::Freezer),
    BinaryTree(StoreSection::Shelves)
  )
);
// clang-format on

int main()
{
  std::cout << "Hello!\n";
  std::cout
      << "This is The Store, a co-op store for food where you can\n"
         "both sell and give food away to others who are in need of\n"
         "food. You can either give items, or buy items from the store.\n\n";

  // Ask user if they are buying items or giving items to store.
  std::cout << "Do you want to give items or buy items from the store?\n"
               "  1. Give items to store.\n"
               "  2. Buy items from store.\n";
  int giving = get_int("Enter a number", 1, 2) == 1;

  std::cout
      << "\nCool, let's find the section of the store you'd like to go to!\n\n";

  // Ask questions to user and get a corresponding store section
  StoreSection section = tree.find_store_section();

  // Get store filename based on selected section
  std::string filename;
  switch (section)
  {
  case StoreSection::Meat:
    filename = "assets/meat.txt";
    break;
  case StoreSection::Produce:
    filename = "assets/produce.txt";
    break;
  case StoreSection::Freezer:
    filename = "assets/freezer.txt";
    break;
  case StoreSection::Shelves:
    filename = "assets/shelves.txt";
    break;
  case StoreSection::None:
    std::cerr << "fatal: store section not found\n";
    return 1;
  }

  // Read store file
  Store store(filename);
  store.load();

  if (giving)
  {
    std::cout << "\nAlright, let's start adding items to the store!\n\n";

    // Get items from user and add them to the store
    List<Item> items = giving_flow();
    add_items_to_store(store, items);
  }
  else
  {
    std::cout
        << "\nAlright, let's start buying items! You are now in a shell.\n\n";

    // Let user shop for stuff and then check out items
    Cart cart = shopping_flow(store);
    checkout_flow(store, cart);
  }

  // Write new store to disk
  store.persist();

  std::cout << "Thanks for coming to our store! Come again!\n";

  return 0;
}
