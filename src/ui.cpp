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

double get_price(const std::string& prompt)
{
  while (true)
  {
    double input;
    std::cout << prompt << ": $";
    std::cin >> input;
    std::cin.clear();
    std::cin.ignore();

    if (!std::cin.fail())
    {
      return input;
    }

    std::cout << "Unable to receive valid input; try again\n";
  }
}

std::string get_string(const std::string& prompt)
{
  while (true)
  {
    std::string input;
    std::cout << prompt << " ";
    std::cin >> input;
    std::cin.clear();
    std::cin.ignore();

    if (!input.empty())
    {
      std::stringstream ss(input);
      std::string ret;
      ss >> ret;
      return ret;
    }

    std::cout << "Input is empty, try again\n";
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
