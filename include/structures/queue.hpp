#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "structures/list.hpp"

// Queue that mimics the behavior of the
// STL implementation std::queue.
template <typename T> class Queue
{
public:
  // Number of elements in queue.
  std::size_t size() const;
  // Check if the queue is empty.
  bool empty() const;

  // Get element at beginning of queue. Undefined
  // behavior if the queue is empty.
  T front() const;
  // Get element at end of queue. Undefined behavior
  // if the queue is empty.
  T back() const;

  // Add element to back of queue.
  void push(T element);
  // Remove element from front of queue.
  void pop();

private:
  // Underlying linked list that the queue manages.
  List<T> list;
};

#include "../../src/structures/queue.cpp"

#endif
