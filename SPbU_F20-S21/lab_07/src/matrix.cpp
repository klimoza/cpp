#include "matrix.h"

void Matrix::init(std::size_t new_r, std::size_t new_c) {
  _rows = new_r;
  _cols = new_c;
  _data = (int**) new char [_rows * _cols * sizeof(int) + _rows * sizeof(int*)];

  _data[0] = (int*) (_data + _rows);
  for(int i = 1; i < _rows; i++)
    _data[i] = _data[i - 1] + _cols;

  for(int i = 0; i < _rows; i++)
    std::fill(_data[i], _data[i] + _cols, 0);
}

void Matrix::free() {
  delete [] _data;
  _data = nullptr;
}

Matrix::Matrix(std::size_t r, std::size_t c) {
  init(r, c);
}

Matrix::Matrix(const Matrix &m) {
  *this = m;
}

Matrix::~Matrix() {
  free();
}

std::size_t Matrix::get_rows() const {
  return _rows;
}

std::size_t Matrix::get_cols() const {
  return _cols;
}

void Matrix::set(std::size_t i, std::size_t j, int val) {
  _data[i][j] = val;
}

int Matrix::get(std::size_t i, std::size_t j) const {
  return _data[i][j];
}

void Matrix::print(FILE* f) const {
  for(int i = 0; i < _rows; i++) {
    for(int j = 0; j < _cols; j++) {
      fprintf(f, "%d", _data[i][j]);
      if(j + 1 < _cols)
        fprintf(f, " ");
      else
        fprintf(f, "\n");
    }
  }
}

bool Matrix::operator==(const Matrix& m) const {
  if(_rows != m._rows || _cols != m._cols)
    return false;
  for(int i = 0; i < _rows; i++)
    for(int j = 0; j < _cols; j++)
      if(_data[i][j] != m._data[i][j])
        return false;
  return true;
}

bool Matrix::operator!=(const Matrix& m) const {
  return !(*this == m);
}

Matrix& Matrix::operator=(const Matrix& m) {
  free();
  init(m._rows, m._rows);
  for(int i = 0; i < _rows; i++)
      std::copy(m._data[i], m._data[i] + _cols, _data[i]);
  return *this;
}

Matrix& Matrix::operator+=(const Matrix& m) {
  *this = *this + m;
  return *this;
}

Matrix& Matrix::operator-=(const Matrix& m) {
  *this = *this - m;
  return *this;
}

Matrix& Matrix::operator*=(const Matrix& m) {
  *this = *this * m;
  return *this;
}

Matrix Matrix::operator+(const Matrix& m) const {
  Matrix res(_rows, _cols);
  for(int i = 0; i < _rows; i++)
    for(int j = 0; j < _cols; j++)
      res._data[i][j] = _data[i][j] + m._data[i][j];
  return res;
}

Matrix Matrix::operator-(const Matrix& m) const {
  Matrix res(m);
  for(int i = 0; i < res._rows; i++)
    for(int j = 0; j < res._cols; j++)
      res._data[i][j] = -res._data[i][j];
  res += *this;
  return res;

}

Matrix Matrix::operator*(const Matrix& m) const {
  Matrix res(_rows, m._cols);
  for(int i = 0; i < _rows; i++)
    for(int j = 0; j < m._cols; j++)
      for(int k = 0; k < _cols; k++)
        res._data[i][j] += _data[i][k] * m._data[k][j];
  return res;
}
