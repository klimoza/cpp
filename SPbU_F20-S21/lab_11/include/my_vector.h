#ifndef MY_VECTOR_H_
#define MY_VECTOR_H_

#include <cstddef>
#include <algorithm>
#include <cassert>
#include <iostream>
#include <cstring>

namespace containers {

template<typename T>
class my_vector {
public:
  my_vector();
  my_vector(std::size_t n);
  my_vector(const my_vector& other);
  my_vector& operator=(const my_vector& other);
  ~my_vector();

  std::size_t size() const;
  std::size_t capacity() const;
  bool empty() const;

  void resize(std::size_t n);
  void reserve(std::size_t n);

  T& operator[](std::size_t index) const;

  void push_back(const T& t);
  void pop_back();
  void clear();

private:
  void delete_array();

private:
  std::size_t capacity_;
  std::size_t size_;
  char* array_ = nullptr;
};

}

#include "my_vector_impl.h"

#endif  // MY_VECTOR_H_
