template <class T>
stack<T>::stack() : list<T>::list() {}
template <class T>
stack<T>::stack(const stack &s) : list<T>::list() {
  for (auto i = s.list<T>::head; i != s.list<T>::lock; i = i->next_) {
    push(i->data_);
  }
}
template <class T>
stack<T>::stack(stack &&s) : list<T>::list(std::move(s)) {}
template <class T>
stack<T>::stack(std::initializer_list<value_type> const &items) {
  for (auto i = items.begin(); i != items.end(); i++) {
    push(*i);
  }
}
template <class T>
stack<T> &stack<T>::operator=(stack &&s) {
  if (this != &s) {
    if (list<T>::lock != nullptr) {
      list<T>::clear();
      delete list<T>::lock;
    }
    list<T>::Moving(std::move(s));
  }
  return *this;
}
template <class T>
stack<T> &stack<T>::operator=(const stack &s) {
  if (this != &s) {
    if (this->tail != nullptr) {
      list<T>::clear();
    }
    typename list<T>::Node *node = s.list<T>::tail;
    if (s.list<T>::tail != nullptr) {
      while (node != s.list<T>::lock) {
        push(node->data_);
        node = node->prev_;
      }
    }
  }
  return *this;
}
template <class T>
stack<T>::~stack() {}

template <class T>
void stack<T>::push(const_reference value) {
  list<T>::push_front(value);
}

template <class T>
void stack<T>::pop() {
  if (!empty()) list<T>::pop_front();
}
template <class T>
typename stack<T>::const_reference stack<T>::top() {
  return list<T>::front();
}
template <class T>
bool stack<T>::empty() {
  return list<T>::empty();
}
template <class T>
typename stack<T>::size_type stack<T>::size() {
  return list<T>::size();
}
template <class T>
void stack<T>::swap(stack &other) {
  list<T>::swap(other);
}
template <class T>
template <class... Args>
void stack<T>::emplace_front(Args &&...args) {
  list<T>::emplace_front(args...);
}