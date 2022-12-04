#ifndef _MAP_H_
#define _MAP_H_

#include "structures/list.hpp"
#include <string>

// Objects that specialize this template can be used in
// templates that require hashcodes, such as maps and sets.
// This is basically the same as the std::hash function
// object, but I want to override it for char.
template <typename T> struct Hash
{
  // Calculate the hash code for a given element.
  std::size_t operator()(const T& x) const;
};

template <> struct Hash<std::string>
{
  size_t operator()(const std::string x) const
  {
    int h = 0;
    for (std::size_t i = 0; i < x.length(); i++)
    {
      h = 31 * h + x[i];
    }
    return h;
  }
};

// Store two objects of different types in a single object.
template <typename T, typename U> struct Pair
{
  Pair();
  Pair(T first, U second);

  T first;
  U second;
};

// Unordered map implementation that is vaguely similar to std::unordered_map
// and is implemented using an internal, specialized hash table.
template <typename Key, typename T, typename Hash = Hash<Key>> class Map
{
public:
  Map();
  explicit Map(std::size_t buckets);
  Map(const Map<Key, T, Hash>& other);

  class Iterator;

  // Number of elements in map.
  std::size_t size() const;
  // If map has no elements.
  bool empty() const;

  // Insert (key, value) into a map, similar to operator[].
  void insert(const Key& key, const T& value);
  // Find an element with a specific key; returns the end if
  // none are found.
  Iterator find(const Key& key) const;

  Iterator erase(Iterator& pos);

  // Create an iterator starting at the beginning of the map.
  Iterator begin() const;
  // Create an iterator that points to an undefined position
  // in the map; this is defined as the end position in the
  // last bucket.
  Iterator end() const;

  // I don't have an idea on how to return a proper reference
  // from this overload; I might have to change my list iterator
  // definition?; for right now, I'll stick to custom insert and
  // find methods, even if they're not like std::unordered_map.
  // T& operator[](const Key& key);

  class Iterator
  {
  public:
    // Convenient typedef alias for the internal list iterator
    using ListIterator = typename List<Pair<Key, T>>::Iterator;

    explicit Iterator(ListIterator pos, std::size_t bucket_index,
                      const Map<Key, T>* container);

    // Pair<Key, T> at current position.
    Pair<Key, T>& operator*();
    // Pair<Key, T> at current position.
    Pair<Key, T>* operator->();
    // Advance iterator to next position.
    void operator++();
    // Check iterators for equality.
    bool operator==(const Iterator& other) const;
    // Check iterators for inequality.
    bool operator!=(const Iterator& other) const;
    // Erase element at index
    Iterator erase();

  private:
    // Current position iterator is at.
    ListIterator position;
    // Location in bucket array of the list that iterator is part of.
    std::size_t bucket_index;
    // Container that iterator belongs to.
    const Map<Key, T>* container;
  };

  ~Map();

private:
  // Prevent direct reassignment (because I'm lazy and want to get rid of
  // warnings).
  Map<Key, T>& operator=(const Map<Key, T>& other);
  // Static array of buckets for hash table.
  List<Pair<Key, T>>* buckets;
  // Number of buckets in map.
  std::size_t bucket_count;
  // Number of elements in map.
  std::size_t length = 0;
};

#include "../../src/structures/map.cpp"

#endif
