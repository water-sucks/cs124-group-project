#include "buy.hpp"
#include "ui.hpp"

#include "structures/tree.hpp"

#include <iostream>

// clang-format off
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

  Store store;
  StoreSection section = lean.find_store_section();

  switch (section)
  {
  case StoreSection::Meat:
    store = load_items("./assets/meat.txt");
    break;
  case StoreSection::Produce:
    store = load_items("./assets/produce.txt");
    break;
  case StoreSection::Freezer:
    store = load_items("./assets/freezer.txt");
    break;
  case StoreSection::Shelves:
    store = load_items("./assets/shelves.txt");
    break;
  case StoreSection::None:
    std::cerr << "fatal: store section not found\n";
    return 1;
  }

  show_store(store);

  // if (giving) {
  //  List<Item> items = giving_flow(const Store& store)
  //  add_to_store(StoreSection section, const List<Item>& items);
  // }
  // else {
  //  Cart cart = shopping_flow(const Store& store)
  //  checkout(const Store& store, Cart& cart);
  // }

  // Store store = load_items("assets/store.txt");
  //
  // Cart cart = shopping_flow(store);
  // for (const auto& item : cart)
  // {
  //   std::cout << item.first << ": " << item.second << "\n";
  // }

  std::cout << "Thanks for coming to our store! Come again!\n";

  return 0;
}
