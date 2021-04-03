#pragma once

#include "my_vector.h"

namespace containers {

template<typename T>
my_vector<T>::my_vector() : capacity_(1), size_(0) {
  array_ = new char[capacity_ * sizeof(T)];
}

template<typename T>
my_vector<T>::my_vector(std::size_t n) : capacity_(n), size_(n) {
  reserve(n);
  for(std::size_t i = 0; i < size_; i++)
      new (array_ + i * sizeof(T)) T();
}

template<typename T>
my_vector<T>::my_vector(const my_vector<T> &other) : my_vector() {
  *this = other;
}

template<typename T>
my_vector<T>& my_vector<T>::operator=(const my_vector<T> &other) {
  if (&other == this)
    return *this;
  delete_array();

  capacity_ = other.capacity_;
  array_ = new char[capacity_ * sizeof(T)];
  size_ = other.size_;

  for(std::size_t i = 0; i < size_; i++)
    new (array_ + i * sizeof(T)) T(other[i]);
  return *this;
}

template<typename T>
my_vector<T>::~my_vector() {
  delete_array();
}

template<typename T>
std::size_t my_vector<T>::size() const {
  return size_;
}

template<typename T>
std::size_t my_vector<T>::capacity() const {
  return capacity_;
}

template<typename T>
bool my_vector<T>::empty() const {
  return size_ == 0;
}

template<typename T>
T& my_vector<T>::operator[](std::size_t index) const {
  return *((T*)(array_ + index * sizeof(T)));
}

template<typename T>
void my_vector<T>::reserve(std::size_t n) {
  std::size_t l = 1;
  while(l < n)
    l <<= 1;
  if (l <= capacity_)
    return;
  capacity_ = l;
  char *tmp = array_;
  array_ = new char[capacity_ * sizeof(T)];
  if(tmp)
    std::memcpy(array_, tmp, size_ * sizeof(T));
  delete [] tmp;
}

template<typename T>
void my_vector<T>::resize(std::size_t new_size) {
  reserve(new_size);
  if(size_ < new_size) {
    while(size_ < new_size) {
      new (array_ + size_ * sizeof(T)) T();
      size_++;
    }
  } else {
    while(size_ > new_size) {
      size_--;
      ((T*)(array_ + size_ * sizeof(T)))->~T();
    }
  }
}

template<typename T>
void my_vector<T>::push_back(const T& t) {
  if (size_ == capacity_)
    reserve(2 * capacity_);
  new (array_ + size_ * sizeof(T)) T(t);
  size_++;
}

template<typename T>
void my_vector<T>::pop_back() {
  assert(size_ > 0);
  size_--;
  ((T*)(array_ + size_ * sizeof(T)))->~T();
}

template<typename T>
void my_vector<T>::clear() {
  while(size_)
    pop_back();
}

template<typename T>
void my_vector<T>::delete_array() {
  clear();
  delete [] array_;
  capacity_ = size_ = 0;
}

template<class T>
std::ostream& operator <<(std::ostream& out, const my_vector<T> & a) {
  for(std::size_t i = 0; i < a.size(); i++) {
    out << a[i];
    if(i < (a.size() - 1))
      out << " ";
  }
  return out;
}

}
