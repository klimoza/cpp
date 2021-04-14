#pragma once

#include <iostream>
#include <fstream>

class Matrix {
public:
  Matrix() noexcept;
  Matrix(std::size_t r, std::size_t c);
  Matrix(const Matrix& m);
  ~Matrix() noexcept;

  void elem(std::size_t i, std::size_t j) const;

  void load(std::string filename);
  void print() const noexcept;

  Matrix& operator=(const Matrix m) noexcept ;
  Matrix& operator+=(const Matrix& m);
  Matrix& operator*=(const Matrix& m);

private:
  void init(std::size_t new_r, std::size_t new_c);
  void free() noexcept;

private:
  std::size_t _rows;
  std::size_t _cols;
  int **_data;
};

class MatrixException : public std::logic_error {
public:
  explicit MatrixException(std::string msg);
};
