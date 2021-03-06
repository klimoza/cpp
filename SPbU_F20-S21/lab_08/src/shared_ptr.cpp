#include "shared_ptr.hpp"

void shared_ptr::free() {
  storage_->decr();
  if(!storage_->getCounter()) {
    storage_->free();
    delete storage_;
  }
  storage_ = nullptr;
}

void shared_ptr::Storage::free() {
  delete data_;
  data_ = nullptr;
  ref_count_ = 0;
}

shared_ptr::shared_ptr(Matrix* obj) {
  storage_ = new Storage(obj);
}

shared_ptr::shared_ptr(const shared_ptr& other) {
  other.storage_->incr();
  storage_ = other.storage_;
}

shared_ptr& shared_ptr::operator=(shared_ptr other) {
  if(this == &other)
    return *this;
  std::swap(storage_, other.storage_);
  return *this;
}

shared_ptr::~shared_ptr() {
  free();
}

Matrix* shared_ptr::ptr() const {
  return storage_->getObject();
}

bool shared_ptr::isNull() const {
  return (storage_->getObject() == nullptr);
}

void shared_ptr::reset(Matrix* obj) {
  *this = shared_ptr(obj);
}

Matrix* shared_ptr::operator->() const {
  return storage_->getObject();
}

Matrix& shared_ptr::operator*() const {
  return *(storage_->getObject());
}

shared_ptr::Storage::Storage(Matrix* mtx) {
  data_ = mtx;
  ref_count_ = 1;
}

shared_ptr::Storage::~Storage() {
  free();
}

void shared_ptr::Storage::incr() {
  ref_count_++;
}

void shared_ptr::Storage::decr() {
  ref_count_--;
}

int shared_ptr::Storage::getCounter() const {
  return ref_count_;
}

Matrix* shared_ptr::Storage::getObject() const {
  return data_;
}
