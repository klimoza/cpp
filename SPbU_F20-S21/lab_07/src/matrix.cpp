#include "matrix.h"

Matrix::Matrix(std::size_t r, std::size_t c) {
  _rows = r;
  _cols = c;
  _data = new int* [_rows];
  for(int i = 0; i < _rows; i++)
    _data[i] = new int [_cols];
}

Matrix::~Matrix() {
  for(int i = 0; i < _rows; i++) {
    delete [] _data[i];
    _data[i] = nullptr;
  }
  delete [] _data;
  _data = nullptr;
}

std::size_t Matrix::get_rows() { return _rows; }
std::size_t Matrix::get_cols() { return _cols; }

void Matrix::set(std::size_t i, std::size_t j, int val) {
  assert(0 <= i && i < _rows && 0 <= j && j < _cols);
  _data[i][j] = val;
}

int Matrix::get(std::size_t i, std::size_t j) {
  assert(0 <= i && i < _rows && 0 <= j && j < _cols);
  return _data[i][j];
}

void Matrix::print(FILE* f) {
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

bool Matrix::operator==(Matrix& m) {
  if(_rows != m._rows || _cols != m._cols)
    return false;
  for(int i = 0; i < _rows; i++)
    if(!memcmp(_data[i], m._data[i], _cols * sizeof(int)))
      return false;
  return true;
}

bool Matrix::operator!=(Matrix& m) {
  return !(*this == m);
}

Matrix& Matrix::operator+=(Matrix& m) {
  return *this;
}

Matrix& Matrix::operator-=(Matrix& m) {
  return *this;
}

Matrix& Matrix::operator*=(Matrix& m) {
  return *this;
}

Matrix Matrix::operator+(Matrix& m) {
  assert(_rows == m._rows && _cols == m._cols);
  Matrix res(_rows, _cols);
  for(int i = 0; i < _rows; i++)
    for(int j = 0; j < _cols; j++)
      res._data[i][j] = _data[i][j] + m._data[i][j];
  return *this;
}

Matrix Matrix::operator-(Matrix& m) {
  Matrix res(m);
  for(int i = 0; i < res._rows; i++)
    for(int j = 0; j < res._cols; j++)
      res._data[i][j] = -res._data[i][j];
  return (*this + res);

}

Matrix Matrix::operator*(Matrix& m) {
  assert(_cols == m._rows);
  Matrix res(_rows, m._cols);
  for(int i = 0; i < _rows; i++) {
    for(int j = 0; j < m._cols; j++) {
      res._data[i][j] = 0;
      for(int k = 0; j < _cols; k++)
        res._data[i][j] += _data[i][k] * m._data[k][j];
    }
  }
  return *this;
}
