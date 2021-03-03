#ifndef LAB_07_MATRIX_H
#define LAB_07_MATRIX_H

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>

class Matrix {
public:
  Matrix(std::size_t r, std::size_t c);
  Matrix(const Matrix &m);
  ~Matrix();

  std::size_t get_rows() const;
  std::size_t get_cols() const;
  void set(std::size_t i, std::size_t j, int val);
  int get(std::size_t i, std::size_t j) const;
  void print(FILE *f) const;

  Matrix operator+(const Matrix& m) const;
  Matrix operator-(const Matrix& m) const;
  Matrix operator*(const Matrix& m) const;

  Matrix& operator=(const Matrix& m);
  Matrix& operator+=(const Matrix& m);
  Matrix& operator-=(const Matrix& m);
  Matrix& operator*=(const Matrix& m);

  bool operator==(const Matrix& m) const ;
  bool operator!=(const Matrix& m) const ;

  void init(std::size_t new_r, std::size_t new_c);
  void free();

private:
  std::size_t _rows = 0;
  std::size_t _cols = 0;
  int **_data = nullptr;
};

#endif
