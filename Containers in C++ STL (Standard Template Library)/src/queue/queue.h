#ifndef TRYES_MAI_H
#define TRYES_MAI_H
#include "../list/list.h"
namespace  {
template <class T>
class queue : private list<T> {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  queue();
  queue(const queue &q);
  queue(queue &&q);
  queue(std::initializer_list<value_type> const &items);
  queue<T> &operator=(queue &&q);
  queue<T> &operator=(const queue &q);
  ~queue();

  void push(const_reference value);
  void pop();
  const_reference front();
  const_reference back();
  bool empty();
  size_type size();
  void swap(queue &other);
  template <class... Args>
  void emplace_back(Args &&...args);
};
#include "queue.tpp"
}  // namespace 
#endif