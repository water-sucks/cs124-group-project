#ifndef LIST_H
#define LIST_H

#include <cstdlib>

// Doubly-linked list with iterators that mimics the
// behavior of the STL implementation std::list.
template <typename T> class List
{
public:
  class Iterator;

private:
  struct Node;

public:
  List(){};
  List(const List<T>& other);

  // Number of elements in list.
  std::size_t size() const;
  // Check if the list is empty.
  bool empty() const;

  // Get element at beginning of list. Causes a
  // segfault if the list is empty.
  T front() const;
  // Get element at end of list. Causes a
  // segfault if the list is empty.
  T back() const;

  // Create an iterator starting at the beginning of the list.
  Iterator begin() const;
  // Create an iterator that points to an invalid position in
  // the list.
  Iterator end() const;

  // Add element at beginning of list.
  void push_front(T element);
  // Add element at end of list.
  void push_back(T element);
  // Remove element from beginning of list, if it exists.
  void pop_front();
  // Remove element from end of list, if it exists.
  void pop_back();

  // Erase the element at the given position. Undefined
  // behavior if called with an Iterator that matches end().
  Iterator erase(Iterator pos);

  // Copy elements from one list into another when reassigned.
  List<T>& operator=(const List<T>& other);

  ~List();

  class Iterator
  {
  public:
    explicit Iterator(Node* position, const List* list);

    // Element at current position. Undefined behavior
    // if called on an end position.
    T& operator*();
    // Element at current position. Undefined behavior
    // if called on an end position.
    T* operator->();
    // Advance iterator to next position.
    void operator++();
    // Check iterators for equality.
    bool operator==(const Iterator& other) const;
    // Check iterators for inequality.
    bool operator!=(const Iterator& other) const;

  private:
    // Current position iterator is at.
    Node* position = nullptr;

    // Container that iterator belongs to.
    const List<T>* list;

    friend class List;
  };

private:
  // Object that contains references to next and previous
  // pointers for a given position in the list.
  struct Node
  {
    explicit Node(T data);

    // Data that node contains.
    T data;
    // Previous node in list.
    Node* previous = nullptr;
    // Next node in list.
    Node* next = nullptr;
  };

  // Number of elements of list.
  std::size_t length = 0;

  // Beginning of list.
  Node* head = nullptr;
  // End of list.
  Node* tail = nullptr;
};

#include "../../src/structures/list.cpp"

#endif
