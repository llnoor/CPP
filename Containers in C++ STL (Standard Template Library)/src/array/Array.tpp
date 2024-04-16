namespace  {

template <typename T, size_t N>
Array<T, N>& Array<T, N>::operator=(Array&& a) {
  for (size_type i = 0; i < N; ++i) {
    data_[i] = std::move(a.data_[i]);
  }
  return *this;
}

template <typename T, size_t s>
typename Array<T, s>::reference Array<T, s>::at(size_type pos) {
  if (pos >= s) throw std::out_of_range("Index out of range");
  return data_[pos];
}

template <typename T, size_t s>
typename Array<T, s>::reference Array<T, s>::operator[](size_type pos) {
  return data_[pos];
}

template <typename T, size_t s>
typename Array<T, s>::const_reference Array<T, s>::front() const {
  return data_[0];
}

template <typename T, size_t s>
typename Array<T, s>::const_reference Array<T, s>::back() const {
  return data_[size_ - 1];
}

template <typename T, size_t s>
typename Array<T, s>::iterator Array<T, s>::data() {
  return data_;
}

template <typename T, size_t s>
typename Array<T, s>::iterator Array<T, s>::begin() {
  return data_;
}

template <typename T, size_t s>
typename Array<T, s>::iterator Array<T, s>::end() {
  return data_ + s;
}

template <typename T, size_t s>
bool Array<T, s>::empty() {
  return size_ == 0;
}

template <typename T, size_t s>
typename Array<T, s>::size_type Array<T, s>::size() const {
  return s;
}

template <typename T, size_t s>
typename Array<T, s>::size_type Array<T, s>::max_size() const {
  return s;
}

template <typename T, size_t s>
void Array<T, s>::swap(Array& other) {
  for (size_t i = 0; i < s; i++) {
    std::swap(data_[i], other.data_[i]);
  }
}

template <typename T, size_t s>
void Array<T, s>::fill(const_reference value) {
  std::fill(size_, size_ + s, value);
}

}  // namespace 
