#include <iostream>
#include <cstring>

#include "my_vector.h"

namespace product {

class Product {
public:
  Product() = delete;

  Product(const char* name, int quantity, double price) : quantity_(quantity), price_(price) {
    std::size_t len = std::strlen(name);
    name_ = new char [len + 1];
    std::strcpy(name_, name);
  };

  Product(const Product& p) : Product(p.name_, p.quantity_, p.price_) {}

  ~Product() {
    delete [] name_;
  }

  // Сделано просто для удобства тестирования
  bool operator==(const Product &a) const {
    return (!strcmp(name_, a.name_) && price_ == a.price_ && quantity_ == a.quantity_);
  }

  friend std::ostream& operator <<(std::ostream& out, Product& p);

private:
  char *name_;  // Указатель владеет C-style строкой, на которую указывает.
  int quantity_;
  double price_;
};

std::ostream& operator <<(std::ostream& out, Product& p) {
  return out << p.name_ << " " << p.quantity_ << " " << p.price_;
}

void print(const containers::my_vector<int>& v) {
  std::cout << v << std::endl;
}

}  // namespace product

namespace test {
  template<typename T>
  void test_my_vector(T e, T f) {
    containers::my_vector<T> a;
    assert(a.size() == 0);
    assert(a.capacity() == 1);

    a.push_back(e);
    assert(a.size() == 1);
    assert(!a.empty());
    assert(a[0] == e);
    assert(a.capacity() == 1);

    containers::my_vector<T> b = a;
    assert(b.size() == 1);
    assert(b.capacity() == 1);
    assert(b[0] == e);

    b.clear();
    assert(b.empty());

    b.reserve(10);
    assert(b.capacity() == 16);

    a.push_back(f);
    assert(a.size() == 2);
    assert(a[a.size() - 1] == f);

    b.push_back(f);
    b.push_back(f);
    assert(b.size() == 2);
    assert((b[0] == f) && (b[1] == f));

    containers::my_vector<T> c;
    c = b;
    assert(c.size() == 2);
    assert((c[0] == f) && (c[1] == f));

    c.pop_back();
    assert(c.size() == 1);
    assert(c[0] == f);

    c.pop_back();
    assert(c.size() == 0);
  }

  template<typename T>
  void test_my_vector_default_constructible() {
    containers::my_vector<T> t(3);
    assert(t.size() == 3);
    assert(t.capacity() == 4);
    assert((t[0] == T()) && (t[1] == T()) && (t[2] == T()));

    t.resize(5);
    assert(t.size() == 5);
    assert(t.capacity() == 8);
    assert((t[3] == T()) && (t[4] == T()));

    t.resize(2);
    assert(t.size() == 2);
    assert(t.capacity() == 8);
  }
}

int main() {
  test::test_my_vector<int>(5, 2);
  test::test_my_vector<product::Product>(product::Product("asdf", 4, 12.0), product::Product("qwe", -1, 7.5));

  test::test_my_vector_default_constructible<int>();
  return 0;
}
