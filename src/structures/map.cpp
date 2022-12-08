#ifndef _MAP_IMPL_H_
#define _MAP_IMPL_H_

#include "structures/map.hpp"

template <typename K, typename V> Pair<K, V>::Pair() : Pair(K(), V()) {}

template <typename K, typename V>
Pair<K, V>::Pair(K key, V value) : first(key), second(value)
{}

template <typename Key, typename T, typename Hash>
Map<Key, T, Hash>::Map() : Map(1)
{}

template <typename Key, typename T, typename Hash>
Map<Key, T, Hash>::Map(std::size_t buckets)
    : buckets(new List<Pair<Key, T>>[buckets]), bucket_count(buckets)
{}

template <typename Key, typename T, typename Hash>
Map<Key, T, Hash>::Map(const Map<Key, T, Hash>& other) : Map(other.bucket_count)
{
  length = other.length;

  for (std::size_t i = 0; i < bucket_count; i++)
  {
    buckets[i] = other.buckets[i];
  }
}

template <typename Key, typename T, typename Hash>
Map<Key, T, Hash>& Map<Key, T, Hash>::operator=(const Map<Key, T, Hash>& other)
{
  delete[] buckets;

  length = other.length;
  bucket_count = other.bucket_count;
  buckets = new List<Pair<Key, T>>[bucket_count];

  for (std::size_t i = 0; i < bucket_count; i++)
  {
    buckets[i] = other.buckets[i];
  }

  return *this;
}

template <typename Key, typename T, typename Hash>
std::size_t Map<Key, T, Hash>::size() const
{
  return length;
}

template <typename Key, typename T, typename Hash>
bool Map<Key, T, Hash>::empty() const
{
  return length == 0;
}

template <typename Key, typename T, typename Hash>
void Map<Key, T, Hash>::insert(const Key& key, const T& value)
{
  std::size_t hash = Hash()(key);
  std::size_t index = hash % bucket_count;
  List<Pair<Key, T>>* list = &(buckets[index]);

  for (auto& pair : *list)
  {
    if (pair.first == key)
    {
      // Replace original values for already existing keys
      pair.second = value;
      return;
    }
  }

  // If not found, add a Pair to the bucket
  list->push_front(Pair<Key, T>(key, value));
  length++;
}

template <typename Key, typename T, typename Hash>
Map<Key, T, Hash>::Iterator::Iterator(ListIterator pos,
                                      std::size_t bucket_index,
                                      const Map<Key, T>* container)
    : position(pos), bucket_index(bucket_index), container(container)
{}

template <typename Key, typename T, typename Hash>
typename Map<Key, T, Hash>::Iterator
Map<Key, T, Hash>::find(const Key& key) const
{
  std::size_t hash = Hash()(key);
  std::size_t index = hash % bucket_count;
  List<Pair<Key, T>>* list = &(buckets[index]);

  // Look at each value in bucket and see if it matches the key,
  // otherwise return the end position
  for (auto iter = list->begin(); iter != list->end(); ++iter)
  {
    if (iter->first == key)
    {
      return Iterator(iter, index, this);
    }
  }

  return end();
}

template <typename Key, typename T, typename Hash>
typename Map<Key, T, Hash>::Iterator Map<Key, T, Hash>::erase(Iterator& pos)
{
  return pos.erase();
}

template <typename Key, typename T, typename Hash>
typename Map<Key, T, Hash>::Iterator Map<Key, T, Hash>::begin() const
{
  // Find first non-empty bucket and construct Iterator with its first element
  for (std::size_t i = 0; i < bucket_count; i++)
  {
    if (!(buckets[i].empty()))
    {
      return Iterator(buckets[i].begin(), i, this);
    }
  }

  return end();
}

template <typename Key, typename T, typename Hash>
typename Map<Key, T, Hash>::Iterator Map<Key, T, Hash>::end() const
{
  // There will always be a list here, even if it's empty
  return Iterator(buckets[bucket_count - 1].end(), bucket_count - 1, this);
}

template <typename Key, typename T, typename Hash>
Pair<Key, T>& Map<Key, T, Hash>::Iterator::operator*()
{
  return *position;
}

template <typename Key, typename T, typename Hash>
Pair<Key, T>* Map<Key, T, Hash>::Iterator::operator->()
{
  return &(*position);
}

template <typename Key, typename T, typename Hash>
void Map<Key, T, Hash>::Iterator::operator++()
{
  ++position;
  // If at end of current bucket, we need to find the next bucket
  if (position == container->buckets[bucket_index].end())
  {
    bucket_index++;
    // Find next non-empty bucket and replace position
    for (std::size_t i = bucket_index; i < container->bucket_count; i++)
    {
      if (!container->buckets[i].empty())
      {
        position = container->buckets[i].begin();
        return;
      }
      bucket_index++;
    }
  }
  else
  {
    return;
  }

  // Manually setting position to end()
  position = container->buckets[container->bucket_count - 1].end();
}

template <typename Key, typename T, typename Hash>
bool Map<Key, T, Hash>::Iterator::operator==(const Iterator& other) const
{
  return container == other.container && position == other.position;
}

template <typename Key, typename T, typename Hash>
bool Map<Key, T, Hash>::Iterator::operator!=(const Iterator& other) const
{
  return !operator==(other);
}

template <typename Key, typename T, typename Hash>
typename Map<Key, T, Hash>::Iterator Map<Key, T, Hash>::Iterator::erase()
{
  ListIterator next = container->buckets[bucket_index].erase(position);
  return Iterator(next, bucket_index, container);
}

template <typename Key, typename T, typename Hash> Map<Key, T, Hash>::~Map()
{
  delete[] buckets;
}

#endif
