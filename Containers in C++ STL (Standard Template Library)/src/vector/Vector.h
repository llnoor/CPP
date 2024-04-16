#ifndef CPP2_CONTAINERS_VECTOR_VECTOR_H
#define CPP2_CONTAINERS_VECTOR_VECTOR_H
#include <stdexcept>

namespace  {
template <typename T>
class Vector {
 public:
  // Member type
  using value_type =
      T;  // T defines the type of an element (T is template parameter)
  using reference = T &;  // T & defines the type of the reference to an element
  using const_reference =
      const T &;         // const T & defines the type of the constant reference
  using iterator = T *;  // T * or internal class VectorIterator<T> defines the
                         // type for iterating through the container
  using const_iterator =
      const T *;  // const T * or internal class VectorConstIterator<T> defines
                  // the constant type for iterating through the container
  using size_type = size_t;  // size_t defines the type of the container size
                             // (standard type is size_t)

  // Functions
  Vector();  // default constructor, creates empty vector
  Vector(
      size_type n);  // parameterized constructor, creates the vector of size n
  Vector(std::initializer_list<value_type> const
             &items);       // initializer list constructor, creates vector
                            // initizialized using std::initializer_list
  Vector(const Vector &v);  // copy constructor
  Vector(Vector &&v);       // move constructor
  ~Vector();                // destructor
  Vector &operator=(
      Vector &&v);  // assignment operator overload for moving object
  Vector &operator=(const Vector &other);  //?

  // Element access
  reference at(size_type pos);  // access specified element with bounds checking
  reference operator[](size_type pos);  // access specified element
  const_reference front() const;        // access the first element
  const_reference back() const;         // access the last element
  T *data();                            // direct access to the underlying array

  // vector iterators
  iterator begin();
  iterator end();

  // vector Capacity
  bool empty();          // checks whether the container is empty
  size_type size();      // returns the number of elements
  size_type max_size();  // returns the maximum possible number of elements
  void reserve(
      size_type size);   // allocate storage of size elements and copies current
                         // array elements to a newely allocated array
  size_type capacity();  // returns the number of elements that can be held in
                         // currently allocated storage
  void shrink_to_fit();  // reduces memory usage by freeing unused memory

  // vector Modifiers
  void clear();  // clears the contents
  iterator insert(
      iterator pos,
      const_reference
          value);  // inserts elements into concrete pos and returns the
                   // iterator that points to the new element вставляет элементы
                   // в конкретный pos и возвращает итератор, указывающий на
                   // новый элемент
  void erase(iterator pos);  // erases element at pos стирает элемент в позиции
  void push_back(const_reference value);  // adds an element to the end
                                          // добавляет элемент в конец
  void pop_back();  // removes the last element
  void swap(Vector &other);  // swaps the contents меняет местами содержимое

 private:
  value_type *data_;
  size_type size_;
  size_type capacity_;
};
}  // namespace 

#include "Vector.tpp"
#endif  // CPP2_CONTAINERS_VECTOR_VECTOR_H
