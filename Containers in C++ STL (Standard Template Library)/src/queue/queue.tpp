template <class T>
queue<T>::queue() : list<T>::list() {}
template <class T>
queue<T>::queue(const queue &q) : list<T>::list() {
  for (auto i = q.list<T>::head; i != q.list<T>::lock; i = i->next_) {
    push(i->data_);
  }
}
template <class T>
queue<T>::queue(queue &&q) : list<T>::list(std::move(q)) {}
template <class T>
queue<T>::queue(std::initializer_list<value_type> const &items) {
  for (auto i = items.begin(); i != items.end(); i++) {
    push(*i);
  }
}
template <class T>
queue<T> &queue<T>::operator=(queue &&q) {
  if (this != &q) {
    if (list<T>::lock != nullptr) {
      list<T>::clear();
      delete list<T>::lock;
    }
    list<T>::Moving(std::move(q));
  }
  return *this;
}
template <class T>
queue<T> &queue<T>::operator=(const queue &q) {
  if (this != &q) {
    if (this->tail != nullptr) {
      list<T>::clear();
    }
    typename list<T>::Node *node = q.list<T>::tail;
    if (q.list<T>::tail != nullptr) {
      while (node != q.list<T>::lock) {
        push(node->data_);
        node = node->prev_;
      }
    }
  }
  return *this;
}
template <class T>
queue<T>::~queue(){};
template <class T>
void queue<T>::push(const_reference value) {
  list<T>::push_back(value);
}
template <class T>
void queue<T>::pop() {
  if (!empty()) list<T>::pop_front();
}
template <class T>
typename queue<T>::const_reference queue<T>::front() {
  if (list<T>::head != nullptr)
    return list<T>::back();
  else
    return list<T>::lock->data_;
}
template <class T>
typename queue<T>::const_reference queue<T>::back() {
  if (list<T>::head != nullptr)
    return list<T>::front();
  else
    return list<T>::lock->data_;
}
template <class T>
bool queue<T>::empty() {
  return list<T>::empty();
}
template <class T>
void queue<T>::swap(queue &other) {
  list<T>::swap(other);
}
template <class T>
typename queue<T>::size_type queue<T>::size() {
  return list<T>::size();
}
template <class T>
template <class... Args>
void queue<T>::emplace_back(Args &&...args) {
  list<T>::emplace_back(args...);
}
