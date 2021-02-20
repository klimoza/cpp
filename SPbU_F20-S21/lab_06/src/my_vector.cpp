#include "my_vector.h"

#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <cstring>

MyVector::MyVector() {
  const int INITIAL_CAPACITY = 2;
  _cp = INITIAL_CAPACITY;
  _sz = 0;
  _data = (int*) malloc(sizeof(int) * _cp);
}

MyVector::MyVector(std::size_t init_capacity) {
  _cp = init_capacity;
  _sz = 0;
  _data = (int*) malloc(sizeof(int) * _cp);
}

MyVector::MyVector(MyVector &a) {
  _cp = a._cp;
  _sz = a._sz;
  _data = (int*) malloc(sizeof(int) * _cp);
  memcpy(_data, a._data, sizeof(int) * _sz);
}

MyVector& MyVector::operator=(const MyVector &a) {
  if (&a == this)
    return *this;
  free(_data);
  _sz = a._sz;
  _cp = a._cp;
  _data = (int*) malloc(sizeof(int) * _cp);
  memcpy(_data, a._data, sizeof(int) * _sz);
  return *this;
}

MyVector::~MyVector() {
  free(_data);
  _data = nullptr;
}

void MyVector::set(std::size_t index, int value) {
  assert(index < _sz);
  _data[index] = value;
}

int MyVector::get(std::size_t index) {
  assert(index < _sz);
  return _data[index];
}

std::size_t MyVector::size() {
  return _sz;
}

std::size_t MyVector::capacity() {
  return _cp;
}

void MyVector::reserve(std::size_t new_capacity) {
  if (new_capacity <= _cp)
    return;
  _cp = new_capacity;
  _data = (int*) realloc(_data, sizeof(int) * _cp);
}

void MyVector::resize(std::size_t new_size) {
  reserve(new_size);
  if (_sz < new_size)
    memset(_data + _sz, 0, sizeof(int) * (new_size - _sz));
  _sz = new_size;
}

void MyVector::push_back(int value) {
  if (_sz == _cp)
    reserve(std::max(2 * _cp, (size_t)1));
  _data[_sz++] = value;
}

void MyVector::insert(std::size_t index, int value) {
  assert(index <= _sz);
  if (_sz == _cp)
    reserve(std::max(2 * _cp, (size_t)1));
  memcpy(_data + index + 1, _data + index, sizeof(int) * (_sz - index));
  _sz++;
  set(index, value);
}

void MyVector::erase(std::size_t index) {
  assert(index < _sz);
  memcpy(_data + index, _data + index + 1, sizeof(int) * (_sz - index + 1));
  _sz--;
}
