#include <cstdint>
#include <cassert>

namespace lab_13 {

template <typename T, std::size_t N>
class my_array {
 public:
  my_array() = default;

  T const& at(std::size_t index) const {
    assert(index < N);
    return data_[index];
  }

  T const& operator[](std::size_t index) const {
    return data_[index];
  }

  T& at(std::size_t index) {
    assert(index < N);
    return data_[index];
  }

  T& operator[](std::size_t index) {
    return data_[index];
  }

  bool empty() const {
    return N == 0;
  }
  std::size_t size() const {
    return N;
  }

  void fill(const T& val) {
    for (std::size_t i = 0; i < N; i++)
      data_[i] = val;
  }

 private:
  T data_[N];
};

template <std::size_t N>
class my_array<bool, N> {
 private:
  class proxy;
  static const std::size_t block_size = 8;

  std::size_t block_number(std::size_t index) const {
    return index / block_size;
  }

  std::size_t id(std::size_t index) const {
    return index & (block_size - 1);
  }

  std::size_t number_of_blocks() const {
    return (N + block_size - 1) / block_size;
  }

  bool elem(std::size_t index) const {
    return data_[block_number(index)] & (1 << id(index));
  }

 public:
  my_array() = default;

  bool at(std::size_t index) const {
    assert(index < N);
    return elem(index);
  }

  bool operator[](std::size_t index) const {
    return elem(index);
  }

  proxy at(std::size_t index) {
    assert(index < N);
    return proxy(data_[block_number(index)], id(index));
  }

  proxy operator[](std::size_t index) {
    return proxy(data_[block_number(index)], id(index));
  }

  bool empty() const {
    return N == 0;
  }

  std::size_t size() const {
    return N;
  }

  void fill(bool val) {
    for (std::size_t i = 0; i < number_of_blocks(); i++)
      data_[i] = -val;
  }

 private:
  uint8_t data_[(N + block_size - 1) / block_size];

  class proxy {
   private:
    uint8_t& data_;
    uint8_t index, msk;
    proxy(uint8_t& data_, uint8_t index) : data_(data_), index(index), msk(1 << index) {}
    friend class my_array;
   public:

    operator bool() const {
      return data_ & msk;
    }

    proxy& operator=(bool value) {
      data_ &= ~msk;
      data_ |= value << index;
      return *this;
    }

    proxy& operator=(const proxy& other) {
      return *this = (bool)other;
    }
  };
};

}
