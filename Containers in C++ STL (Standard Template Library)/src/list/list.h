#ifndef TRYES_MAIN_H
#define TRYES_MAIN_H
#include <stdlib.h>

#include <iostream>
#include <limits>
namespace  {
template <class T>
class list {
 public:
  class ListIterator;
  class ListConstIterator;

 public:  // usings
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;
  using iterator = ListIterator;
  using const_iterator = ListConstIterator;

 public:  // constructers
  list();
  list(size_type n);
  list(std::initializer_list<value_type> const &items);
  list(const list &l);
  list(list &&l);
  ~list();
  list<T> &operator=(list &&l) noexcept;
  list<T> &operator=(const list &other_List) noexcept;

 public:  // functions
  bool empty() const noexcept;
  size_type size() const noexcept;
  size_type max_size() const noexcept;
  const_reference front() const;
  const_reference back() const;
  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void push_front(const_reference value);
  void pop_front();
  void getVal();
  void swap(list &other);
  void merge(list &other);
  void sort();
  void splice(const_iterator pos, list &other);
  void unique();
  void reverse();
  template <class... Args>
  iterator emplace(const_iterator pos, Args &&...args);
  template <class... Args>
  void emplace_front(Args &&...args);
  template <class... Args>
  void emplace_back(Args &&...args);

 protected:
  struct Node;

 public:  // iterator
  class ListIterator {
    friend list;

   public:
    ListIterator();
    ~ListIterator();
    ListIterator(const ListIterator &other);
    ListIterator operator++();
    ListIterator operator++(int);
    ListIterator operator--();
    ListIterator operator--(int);
    int operator==(const ListIterator &other);
    int operator!=(const ListIterator &other);
    T &operator*();
    T *operator->();
    iterator operator=(const ListIterator &other) noexcept;

   private:
    Node *ptr_;
  };
  class ListConstIterator : public ListIterator {
    friend list;

   public:
    ListConstIterator();
    ListConstIterator(const ListIterator &other);
    const T &operator*() const;
    ~ListConstIterator();
  };

  const_iterator begin() const;
  const_iterator end() const;
  iterator begin();
  iterator end();

 protected:
  typedef struct Node {
    T data_;
    Node *next_, *prev_;
    Node();
    Node(T x);
    Node(Node *x);
  } Node;
  Node *lock, *head, *tail;
  void LockList(T x);
  void Moving(list &&l);
  iterator TakeIter(iterator other, int x);
};
#include "iterator.tpp"
#include "list.tpp"
}  // namespace 
#endif