
template <class T>
list<T>::ListConstIterator::ListConstIterator() : ListIterator() {}
template <class T>
list<T>::ListConstIterator::ListConstIterator(const ListIterator &other)
    : ListIterator(other) {}
template <class T>
list<T>::ListConstIterator::~ListConstIterator() {}

template <class T>
typename list<T>::iterator list<T>::begin() {
  iterator x;
  if (!empty())
    x.ptr_ = this->head;
  else
    x.ptr_ = this->lock;
  return x;
}
template <class T>
typename list<T>::iterator list<T>::end() {
  iterator x;
  x.ptr_ = lock;
  return x;
}
template <class T>
typename list<T>::const_iterator list<T>::begin() const {
  iterator x;
  if (!empty())
    x.ptr_ = this->head;
  else
    x.ptr_ = this->lock;
  return const_iterator(x);
}
template <class T>
typename list<T>::const_iterator list<T>::end() const {
  const_iterator x;
  x.ptr_ = lock;
  return const_iterator(x);
}
template <class T>
typename list<T>::iterator list<T>::TakeIter(iterator other, int x) {
  iterator ret;
  if (x > 0) {
    for (int i = 0; i < x; ++i, ++other) {
    }
    ret = other;
    for (int i = 0; i < x; ++i, --other) {
    }
  } else {
    for (int i = 0; i > x; --i, --other) {
    }
    ret = other;
    for (int i = 0; i > x; --i, ++other) {
    }
  }
  return ret;
}

template <class T>
list<T>::ListIterator::ListIterator() : ptr_(nullptr) {}
template <class T>
list<T>::ListIterator::ListIterator(const ListIterator &other)
    : ptr_(other.ptr_) {}
template <class T>
list<T>::ListIterator::~ListIterator() {}
template <class T>
typename list<T>::ListIterator list<T>::ListIterator::operator++() {
  ptr_ = ptr_->next_;
  return *this;
}
template <class T>
typename list<T>::ListIterator list<T>::ListIterator::operator++(int) {
  ListIterator iter(*this);
  ++(*this);
  return iter;
}
template <class T>
typename list<T>::ListIterator list<T>::ListIterator::operator--() {
  ptr_ = ptr_->prev_;
  return *this;
}
template <class T>
typename list<T>::ListIterator list<T>::ListIterator::operator--(int) {
  ListIterator iter(*this);
  --(*this);
  return iter;
}
template <class T>
T &list<T>::ListIterator::operator*() {
  if (ptr_ == nullptr)
    throw std::invalid_argument(
        "-------------------\niterator = null\n-------------------");
  return ptr_->data_;
};
template <class T>
T *list<T>::ListIterator::operator->() {
  return &ptr_->data_;
};
template <class T>
typename list<T>::ListIterator list<T>::ListIterator::operator=(
    const ListIterator &other) noexcept {
  ptr_ = other.ptr_;
  return *this;
};

template <class T>
int list<T>::ListIterator::operator==(const list<T>::ListIterator &other) {
  int x = (ptr_ == other.ptr_) ? 1 : 0;
  return x;
}
template <class T>
int list<T>::ListIterator::operator!=(const list<T>::ListIterator &other) {
  int x = (ptr_ == other.ptr_) ? 0 : 1;
  return x;
}

template <class T>
const T &list<T>::ListConstIterator::operator*() const {
  return ListIterator::ptr_->data_;
}