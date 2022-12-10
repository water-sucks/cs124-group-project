#include "item.hpp"

Item::Item(std::string name, int quantity, double price)
    : name(name), quantity(quantity), price(price)
{}

// Merge two sorted string vectors into one sorted string vector.
void merge(std::vector<std::string>& words, std::size_t from, std::size_t mid,
           std::size_t to)
{
  std::vector<std::string> temp;

  size_t i = from;
  size_t j = mid + 1;

  while (i <= mid && j <= to)
  {
    if (words[i].compare(words[j]) <= 0)
    {
      temp.push_back(words[i]);
      i++;
    }
    else
    {
      temp.push_back(words[j]);
      j++;
    }
  }

  while (i <= mid)
  {
    temp.push_back(words[i]);
    i++;
  }

  while (j <= to)
  {
    temp.push_back(words[j]);
    j++;
  }

  for (i = from; i <= to; i++)
  {
    words[i] = temp[i - from];
  }
}

void merge_sort(std::vector<std::string>& words, size_t from, size_t to)
{
  if (to - from < 1)
  {
    return;
  };
  size_t mid = (from + to) / 2;
  merge_sort(words, from, mid);
  merge_sort(words, mid + 1, to);
  merge(words, from, mid, to);
}
