template <class T>
list<T>::Node::Node() : next_(nullptr), prev_(nullptr) {}
template <class T>
list<T>::Node::Node(T x) : data_(x), next_(nullptr), prev_(nullptr) {}
template <class T>
list<T>::Node::Node(Node *x)
    : data_(x->data_), next_(x->next_), prev_(x->prev_) {}
template <class T>
void list<T>::LockList(T x) {
  head->prev_ = lock;
  tail->next_ = lock;
  lock->next_ = head;
  lock->prev_ = tail;
  lock->data_ = x;
}
template <class T>
list<T>::list() {
  lock = new Node;
  head = tail = nullptr;
}
template <class t>
list<t>::list(size_type n) : list() {
  if (n > 0)
    for (size_type i = 0; i < n; ++i) {
      push_back(0);
    }
}
template <class T>
list<T>::list(std::initializer_list<value_type> const &items) : list() {
  for (auto i = items.begin(); i != items.end(); ++i) {
    push_back(*i);
  }
}
template <class T>
list<T>::list(const list &l) : list() {
  for (auto i = l.begin(); i != l.end(); ++i) {
    push_back(*i);
  }
}
template <class T>
list<T>::list(list &&l) {
  Moving(std::move(l));
}
template <class T>
list<T> &list<T>::operator=(list &&l) noexcept {
  if (this != &l) {
    if (lock != nullptr) {
      clear();
      delete lock;
    }
    Moving(std::move(l));
  }
  return *this;
}
template <class T>
list<T>::~list() {
  clear();
  delete lock;
}
template <class T>
list<T> &list<T>::operator=(const list &l) noexcept {
  if (this != &l) {
    if (lock != nullptr) {
      clear();
    }
    for (auto i = l.begin(); i != l.end(); ++i) {
      push_back(*i);
    }
  }
  return *this;
}
template <class T>
void list<T>::Moving(list &&l) {
  head = l.head;
  lock = l.lock;
  tail = l.tail;
  l.head = l.lock = l.tail = nullptr;
}
template <class T>
bool list<T>::empty() const noexcept {
  return (head == nullptr) ? true : false;
}
template <class T>
typename list<T>::size_type list<T>::size() const noexcept {
  size_type ret = 0;
  for (auto i = begin(); i != end(); ++i, ++ret) {
  }
  return ret;
}
template <class T>
typename list<T>::size_type list<T>::max_size() const noexcept {
  return std::numeric_limits<size_type>::max() / sizeof(Node) / 2;
}
template <class T>
typename list<T>::const_reference list<T>::front() const {
  return head->data_;
}
template <class T>
typename list<T>::const_reference list<T>::back() const {
  return tail->data_;
}
template <class T>
void list<T>::clear() {
  while (!empty()) {
    pop_back();
  }
}
template <class T>
typename list<T>::iterator list<T>::insert(iterator pos,
                                           const_reference value) {
  Node *node;
  if (pos == begin()) {
    push_front(value);
    node = head;
  } else if (pos == end()) {
    push_back(value);
    node = tail;
  } else {
    node = new Node(value);
    auto i = pos.ptr_->prev_;
    node->next_ = i->next_;
    node->next_->prev_ = node;
    node->prev_ = i;
    i->next_ = node;
  }
  auto n = begin();
  for (; n.ptr_ != node; ++n) {
  }
  return n;
}
template <class T>
void list<T>::erase(iterator pos) {
  if (pos == begin()) {
    pop_front();
  } else if (pos == end()) {
    throw std::invalid_argument(
        "-------------\nInvalid argument. "
        "\n------------------------");
  } else if (pos.ptr_ == tail) {
    pop_back();
  } else {
    pos.ptr_->prev_->next_ = pos.ptr_->next_;
    pos.ptr_->next_->prev_ = pos.ptr_->prev_;
    delete pos.ptr_;
  }
}
template <class T>
void list<T>::push_back(const_reference value) {
  Node *node = new Node(value);
  if (empty()) {
    head = node;
    tail = node;
  } else {
    tail->next_ = node;
    node->prev_ = tail;
    tail = node;
  }
  LockList(head->data_);
}
template <class T>
void list<T>::pop_back() {
  Node *temp = tail->prev_;
  if (!empty()) {
    if (head != tail) {
      tail->prev_->next_ = lock;
      delete tail;
      tail = temp;
      LockList(head->data_);
    } else {
      delete tail;
      head = tail = nullptr;
    }
  }
}
template <class T>
void list<T>::push_front(const_reference value) {
  Node *node = new Node(value);
  if (empty()) {
    head = node;
    tail = node;
  } else {
    head->prev_ = node;
    node->next_ = head;
    head = node;
  }
  LockList(head->data_);
}
template <class T>
void list<T>::pop_front() {
  Node *temp = head->next_;
  if (!empty()) {
    if (head == tail) {
      pop_back();
    } else {
      head->next_->prev_ = lock;
      delete head;
      head = temp;
      LockList(head->data_);
    }
  }
}

template <class T>
void list<T>::getVal() {
  for (auto i = begin(); i != end(); ++i) {
    std::cout << *i << " ";
  }
  std::cout << '\n';
}

template <class T>
void list<T>::swap(list &other) {
  list<T> x = std::move(other);
  other = std::move(*this);
  *this = std::move(x);
}
template <class T>
void list<T>::merge(list &other) {
  if (other.head != nullptr) {
    list<T> x;
    for (auto j = other.begin(), i = begin(); j != other.end();) {
      if ((*i <= *j || j == other.end()) && i != end()) {
        x.push_back(*i);
        ++i;
      } else {
        x.push_back(*j);
        ++j;
      }
      if (i == end() && j == other.end()) break;
    }
    other.clear();
    *this = std::move(x);
  }
}
template <class T>
void list<T>::sort() {
  if (head != tail) {
    T x;
    for (auto i = ++begin(); i != end(); ++i) {
      x = *i;
      auto j = TakeIter(i, -1);
      for (; j != end() && x < *j; --j) {
        j.ptr_->next_->data_ = j.ptr_->data_;
      }
      ++j;
      *j = x;
    }
  }
}
template <class T>
void list<T>::splice(const_iterator pos, list &other) {
  for (auto i = other.begin(); i != other.end(); ++i) insert(pos, *i);
  other.clear();
}
template <class T>
void list<T>::unique() {
  for (auto i = begin(), j = TakeIter(i, 1); i != end() && j != end();
       ++i, ++j) {
    if (*i == *j) {
      auto temp = i;
      --i;
      erase(temp);
    }
  }
}
template <class T>
void list<T>::reverse() {
  int x = 0;
  if (head != tail) {
    for (auto j = begin();; --j) {
      if (x && j == begin()) break;
      x = 1;
      std::swap(j.ptr_->next_, j.ptr_->prev_);
    }
    std::swap(head, tail);
  }
}
template <class T>
template <class... Args>
typename list<T>::iterator list<T>::emplace(const_iterator pos,
                                            Args &&...args) {
  std::initializer_list<T> ar{args...};
  for (auto i : ar) {
    pos = insert(pos, i);
    pos++;
  }
  return pos;
}
template <class T>
template <class... Args>
void list<T>::emplace_front(Args &&...args) {
  std::initializer_list<T> ar{args...};
  for (auto i : ar) {
    push_front(i);
  }
}
template <class T>
template <class... Args>
void list<T>::emplace_back(Args &&...args) {
  std::initializer_list<T> ar{args...};
  for (auto i : ar) {
    push_back(i);
  }
};
