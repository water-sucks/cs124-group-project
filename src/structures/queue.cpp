#ifndef _QUEUE_IMPL_H_
#define _QUEUE_IMPL_H_

#include "structures/queue.hpp"

template <typename T> std::size_t Queue<T>::size() const { return list.size(); }

template <typename T> bool Queue<T>::empty() const { return list.empty(); }

template <typename T> T Queue<T>::front() const { return list.front(); }

template <typename T> T Queue<T>::back() const { return list.back(); }

template <typename T> void Queue<T>::push(T element)
{
  list.push_back(element);
}

template <typename T> void Queue<T>::pop() { list.pop_front(); }

#endif
