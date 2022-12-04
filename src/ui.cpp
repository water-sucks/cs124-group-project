#include "ui.hpp"

#include <iomanip>
#include <iostream>
#include <sstream>

bool confirm(const std::string& prompt)
{
  while (true)
  {
    std::string input;
    std::cout << prompt << " (Y/N)?: ";
    std::cin >> input;
    std::cin.clear();
    std::cin.ignore();

    if (input.empty())
    {
      std::cout << "Please enter y or n to confirm\n";
      continue;
    }

    switch (tolower(input[0]))
    {
    case 'n':
      return false;
    case 'y':
      return true;
    default:
      std::cout << "Please enter y or n to confirm\n";
    }
  };
}

std::string dollars(double num)
{
  std::stringstream ss;
  ss << "$" << std::fixed << std::setprecision(2) << std::setfill('0') << num;
  return ss.str();
}

int get_int(const std::string& prompt, int min, int max)
{
  while (true)
  {
    int input;
    std::cout << prompt << ": ";
    std::cin >> input;
    std::cin.clear();
    std::cin.ignore();

    if (std::cin.fail())
    {
      std::cout << "Unable to receive valid input; try again\n";
      std::cin.clear();
      continue;
    }

    if (input >= min && input <= max)
    {
      return input;
    }

    std::cout << "Number not in range\n";
  }
}

// Center a string within a certain amount of predefined space.
std::string center(const std::string& str, int width)
{
  int length = str.length();
  if (width < length)
  {
    return str;
  }

  int diff = width - length;
  int pad1 = diff / 2;
  int pad2 = diff - pad1;
  return std::string(pad1, ' ') + str + std::string(pad2, ' ');
}

constexpr int table_width = 52;

void show_cart(const Store& store, const Cart& cart)
{
  double total = 0;

  if (cart.empty())
  {
    std::cout << "Cart is empty!\n";
    return;
  }
  const std::string row_boundary = std::string(table_width, '-');
  std::cout << row_boundary << "\n";
  std::cout << "|" << center("Item", 25) << "|" << center("Quantity", 12) << "|"
            << center("Price", 11) << "|\n";
  std::cout << row_boundary << "\n";
  for (const auto& item : cart)
  {
    const auto& store_item = store.find(item.first)->second;
    total += store_item.price * item.second;
    std::cout << "|" << center(store_item.name, 25) << "|"
              << center(std::to_string(item.second), 12) << "|"
              << center(dollars(store_item.price * item.second), 11) << "|\n"
              << row_boundary << "\n";
  }

  std::cout << "Total: " << dollars(total) << "\n";
}

void show_store(const Store& store)
{
  const std::string row_boundary = std::string(table_width, '-');
  std::cout << row_boundary << "\n";
  std::cout << "|" << center("Item", 25) << "|" << center("Quantity", 12) << "|"
            << center("Price", 11) << "|\n";
  std::cout << row_boundary << "\n";
  auto iter = store.begin();
  while (iter != store.end())
  {
    const auto& item = iter->second;
    std::cout << "|" << center(item.name, 25) << "|"
              << center(std::to_string(item.quantity), 12) << "|"
              << center(dollars(item.price), 11) << "|\n"
              << row_boundary << "\n";
    ++iter;
  }
}
