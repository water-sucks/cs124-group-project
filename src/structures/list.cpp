#ifndef _LIST_IMPL_H_
#define _LIST_IMPL_H_

#include "structures/list.hpp"

template <typename T> List<T>::List(const List<T>& other)
{
  // Create a deep copy of each node in the original
  // list when copying current list.
  for (const auto& v : other)
  {
    push_back(v);
  }
}

template <typename T> std::size_t List<T>::size() const { return length; }

template <typename T> bool List<T>::empty() const { return length == 0; }

template <typename T> T List<T>::front() const { return head->data; }

template <typename T> T List<T>::back() const { return tail->data; }

template <typename T> typename List<T>::Iterator List<T>::begin() const
{
  return Iterator(head, this);
}

template <typename T> typename List<T>::Iterator List<T>::end() const
{
  return Iterator(nullptr, this);
}

template <typename T> void List<T>::push_front(T element)
{
  Node* new_node = new Node(element);
  length++;
  if (head == nullptr)
  {
    head = new_node;
    tail = new_node;
    return;
  }
  new_node->next = head;
  head->previous = new_node;
  head = new_node;
}

template <typename T> void List<T>::push_back(T element)
{
  Node* new_node = new Node(element);
  length++;
  if (tail == nullptr)
  {
    head = new_node;
    tail = new_node;
    return;
  }
  new_node->previous = tail;
  tail->next = new_node;
  tail = new_node;
}

template <typename T> void List<T>::pop_front()
{
  if (head == nullptr)
  {
    return;
  }
  Node* del = head;
  head = head->next;
  if (head == nullptr)
  {
    tail = nullptr;
  }
  else
  {
    head->previous = nullptr;
  }
  delete del;
  length--;
}

template <typename T> void List<T>::pop_back()
{
  if (tail == nullptr)
  {
    return;
  }
  Node* del = tail;
  tail = tail->previous;
  if (tail == nullptr)
  {
    head = nullptr;
  }
  else
  {
    tail->next = nullptr;
  }
  delete del;
  length--;
}

template <typename T> typename List<T>::Iterator List<T>::erase(Iterator pos)
{
  Node* del = pos.position;
  Node* before = del->previous;
  Node* after = del->next;

  if (del == head)
  {
    head = after;
  }
  else
  {
    before->next = after;
  }

  if (del == tail)
  {
    tail = before;
  }
  else
  {
    after->previous = before;
  }

  delete del;

  return Iterator(after, this);
}

template <typename T> List<T>& List<T>::operator=(const List<T>& other)
{
  // Create deep copies of each node in the original
  // list when reassigning list.
  for (const auto& v : other)
  {
    push_back(v);
  }
  return *this;
}

template <typename T> List<T>::~List()
{
  Node* trav = head;
  while (trav != nullptr)
  {
    Node* next = trav->next;
    delete trav;
    trav = next;
  }
}

template <typename T> List<T>::Node::Node(T data) : data(data) {}

template <typename T>
List<T>::Iterator::Iterator(Node* position, const List<T>* list)
    : position(position), list(list)
{}

template <typename T> T& List<T>::Iterator::operator*()
{
  return position->data;
}

template <typename T> T* List<T>::Iterator::operator->()
{
  return &(position->data);
}

template <typename T> void List<T>::Iterator::operator++()
{
  if (position != nullptr)
  {
    position = position->next;
  }
}

template <typename T>
bool List<T>::Iterator::operator==(const Iterator& other) const
{
  return position == other.position && list == other.list;
}

template <typename T>
bool List<T>::Iterator::operator!=(const Iterator& other) const
{
  return !operator==(other);
}

#endif
