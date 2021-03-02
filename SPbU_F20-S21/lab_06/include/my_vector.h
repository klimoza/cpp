#ifndef _MY_VECTOR_H_INCLUDED
#define _MY_VECTOR_H_INCLUDED

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <cstdlib>
#include <cstring>

class MyVector {
 public:
  MyVector();
  MyVector(std::size_t init_capacity);
  MyVector(const MyVector &a);
  MyVector& operator=(const MyVector &a);
  ~MyVector();

  void set(std::size_t index, int value);
  int get(std::size_t index);

  std::size_t size();
  std::size_t capacity();

  void reserve(std::size_t new_capacity);
  void resize(std::size_t new_size);

  void push_back(int value);
  void insert(std::size_t index, int value);
  void erase(std::size_t index);

  void init(std::size_t new_sz, std::size_t new_cp);

 private:
  std::size_t _sz, _cp;
  int *_data;
};

#endif
