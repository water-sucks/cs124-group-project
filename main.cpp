#include "flows.hpp"
#include "ui.hpp"

#include "structures/tree.hpp"

#include <iostream>

// clang-format off
// TODO: reword questions better
const BinaryTree lean = BinaryTree(
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

  // Ask user if they are buying items or giving items to store.
  bool giving = confirm("Are you giving items to the store?");

  std::cout
      << "\nCool, let's find the section of the store you'd like to go to!\n\n";

  std::string filename;
  StoreSection section = lean.find_store_section();

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

  Store store(filename);
  store.load();

  if (giving)
  {
    List<Item> items = giving_flow();
    // add_to_store(section, items);
  }
  else
  {
    Cart cart = shopping_flow(store);
    // checkout(store, cart);
  }

  std::cout << "Thanks for coming to our store! Come again!\n";

  return 0;
}
