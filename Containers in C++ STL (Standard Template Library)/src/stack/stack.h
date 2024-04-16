#ifndef TRYES_MAO_H
#define TRYES_MAO_H
#include "../list/list.h"
namespace  {
template <class T>
class stack : private list<T> {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  stack();
  stack(const stack &s);
  stack(stack &&s);
  stack(std::initializer_list<value_type> const &items);
  stack<T> &operator=(stack &&s);
  stack<T> &operator=(const stack &s);
  ~stack();

  void push(const_reference value);
  void pop();
  const_reference top();
  bool empty();
  size_type size();
  void swap(stack &other);
  template <class... Args>
  void emplace_front(Args &&...args);
};
#include "stack.tpp"
}  // namespace 
#endif