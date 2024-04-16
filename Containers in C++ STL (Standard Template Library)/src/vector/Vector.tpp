#include "Vector.h"

namespace  {

/*     vector Member functions      */

// конструктор по умолчанию
template <typename value_type>
Vector<value_type>::Vector() : data_(nullptr), size_(0), capacity_(0){};

// конструктор с одним параметром
template <typename value_type>
Vector<value_type>::Vector(size_type n)
    : size_(n), capacity_(n), data_(new value_type[n]{}) {}

// конструктор списка инициализаторов, создает вектор, инициализированный с
// помощью std::initializer_list
template <typename value_type>
Vector<value_type>::Vector(std::initializer_list<value_type> const &items) {
  size_ = capacity_ = items.size();
  data_ = new value_type[capacity_];
  std::copy(items.begin(), items.end(), data_);
}

// конструктор копирования
template <typename value_type>
Vector<value_type>::Vector(const Vector &v)
    : data_(new value_type[v.capacity_]),
      size_(v.size_),
      capacity_(v.capacity_) {
  std::copy(v.data_, v.data_ + v.size_, data_);
}

// конструктор перемещения
template <typename value_type>
Vector<value_type>::Vector(Vector &&v)
    : size_(v.size_), capacity_(v.capacity_), data_(v.data_) {
  v.size_ = v.capacity_ = 0;
  v.data_ = nullptr;
}

// деструктор
template <typename value_type>
Vector<value_type>::~Vector() {
  size_ = capacity_ = 0;
  delete[] data_;
  data_ = nullptr;
}

//Перегрузка оператора присваивания для движущегося объекта
template <typename T>
Vector<T> &Vector<T>::operator=(Vector &&v) {
  if (this != &v) {
    delete[] data_;

    data_ = v.data_;
    size_ = v.size_;
    capacity_ = v.capacity_;

    v.data_ = nullptr;
    v.size_ = 0;
    v.capacity_ = 0;
  }
  return *this;
}

template <typename T>
typename Vector<T>::iterator Vector<T>::insert(iterator pos,
                                               const_reference value) {
  if (pos < begin() || pos > end()) {
    throw std::out_of_range("Iterator position out of range");
  }

  size_type index = pos - begin();

  if (size_ == capacity_) {
    reserve(capacity_ == 0 ? 1 : capacity_ * 2);
  }

  for (size_type i = size_; i > index; --i) {
    data_[i] = data_[i - 1];
  }

  data_[index] = value;
  ++size_;

  return begin() + index;
}

template <typename value_type>
Vector<value_type> &Vector<value_type>::operator=(const Vector &other) {
  if (this != &other) {
    delete[] data_;

    size_ = other.size_;
    capacity_ = other.capacity_;

    data_ = new value_type[capacity_];
    std::copy(other.data_, other.data_ + size_, data_);
  }
  return *this;
}

template <typename value_type>
typename Vector<value_type>::reference Vector<value_type>::operator[](
    size_type pos) {
  if (pos > size_) throw std::out_of_range("Iterator position out of range");
  return data_[pos];
}

//доступ к указанному элементу с проверкой границ
template <typename value_type>
typename Vector<value_type>::reference Vector<value_type>::at(size_type pos) {
  if (pos >= size()) {
    throw std::out_of_range("out of range");
  }
  return data_[pos];
}

// возвращает ссылку на первый эл-т
template <typename value_type>
typename Vector<value_type>::const_reference Vector<value_type>::front() const {
  if (size_ == 0) {
    throw std::out_of_range("empty");
  }
  return data_[0];
}

template <typename value_type>
typename Vector<value_type>::const_reference Vector<value_type>::back() const {
  return data_[size_ - 1];
}

template <typename T>
T *::Vector<T>::data() {
  return data_;
}

template <typename value_type>
typename Vector<value_type>::iterator Vector<value_type>::begin() {
  return data_;
}

template <typename value_type>
typename Vector<value_type>::iterator Vector<value_type>::end() {
  return data_ + size_;
}

template <typename value_type>
bool Vector<value_type>::empty() {
  return size_ == 0;
}

template <typename value_type>
typename Vector<value_type>::size_type Vector<value_type>::size() {
  return size_;
}

// верхний предел на размер вектора
template <typename value_type>
typename Vector<value_type>::size_type Vector<value_type>::max_size() {
  return std::numeric_limits<size_t>::max() / sizeof(size_type);
}

template <typename value_type>
typename Vector<value_type>::size_type Vector<value_type>::capacity() {
  return (capacity_ - size_);
}

template <typename value_type>
void Vector<value_type>::clear() {
  delete[] data_;
  data_ = nullptr;
  size_ = capacity_ = 0;
}

template <typename value_type>
void Vector<value_type>::shrink_to_fit() {
  capacity_ = size_;
  value_type *newData = new value_type[size_];
  std::copy(newData, newData + size_, data_);
  delete[] data_;
  data_ = newData;
  newData = nullptr;
}

// erases element at pos стирает элемент в позиции
template <typename value_type>
void Vector<value_type>::erase(iterator pos) {
  size_--;
  value_type *newData = new value_type[size_];

  size_type count = 0;
  for (size_type i = 0; i < size_ + 1; i++) {
    if (data_ + i != pos) {
      newData[count] = data_[i];
      count++;
    }
  }
  delete[] data_;
  data_ = newData;
}

template <typename value_type>
void Vector<value_type>::push_back(const_reference value) {
  if (size_ >= capacity_) {
    reserve((capacity_ == 0) ? 1 : capacity_ * 2);
  }
  data_[size_++] = value;
}

template <typename value_type>
void Vector<value_type>::pop_back() {
  if (size_ > 0) size_--;
}

template <typename value_type>
void Vector<value_type>::swap(Vector &other) {
  std::swap(data_, other.data_);
  std::swap(size_, other.size_);
  std::swap(capacity_, other.capacity_);
}

template <typename value_type>
void Vector<value_type>::reserve(size_type newCapacity) {
  if (newCapacity > capacity_) {
    value_type *tmp = data_;
    data_ = new value_type[newCapacity];
    std::copy(tmp, tmp + size_, data_);
    delete[] tmp;
    capacity_ = newCapacity;
  }
}

}  // namespace 
