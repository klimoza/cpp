#include "matrix.h"
#include <new>

Matrix::Matrix() noexcept : _rows(0), _cols(0), _data(nullptr) {}

void Matrix::init(std::size_t new_r, std::size_t new_c) {
  _data = (int**)new char[new_r * new_c * sizeof(int) + new_r * sizeof(int*)];
  if(_data == nullptr)
    throw std::bad_alloc();
  _rows = new_r;
  _cols = new_c;

  _data[0] = (int*) (_data + _rows);
  for(std::size_t i = 1; i < _rows; i++)
    _data[i] = _data[i - 1] + _cols;

  for(std::size_t i = 0; i < _rows; i++)
    std::fill(_data[i], _data[i] + _cols, 0);
}

void Matrix::free() noexcept {
  if(_data)
    delete [] _data;
  _data = nullptr;
}

Matrix::Matrix(std::size_t r, std::size_t c) {
  init(r, c);
}

Matrix::Matrix(const Matrix& m) : Matrix(m._rows, m._cols) {
  for(std::size_t i = 0; i < _rows; i++)
      std::copy(m._data[i], m._data[i] + _cols, _data[i]);
}

Matrix::~Matrix() noexcept {
  free();
}

void Matrix::elem(std::size_t i, std::size_t j) const {
  if(i < 0 || i >= _rows || j < 0 || j >= _cols)
    throw MatrixException("ACCESS: bad index.");
  std::cout << _data[i][j] << std::endl;
}

void Matrix::load(std::string filename) {
  std::ifstream file(filename);
  if(!file)
    throw MatrixException("LOAD: unable to open file.");

  std::size_t r, c;

  if(!(file >> r) || !(file >> c)) {
    file.close();
    throw MatrixException("LOAD: invalid file format.");
  }

  Matrix tmp;
  try {
    tmp = Matrix(r, c);
  } catch(std::bad_alloc &e) {
    file.close();
    throw e;
  }

  for(std::size_t i = 0; i < r; i++) {
    for(std::size_t j = 0; j < c; j++) {
      if(!(file >> tmp._data[i][j])) {
        file.close();
        throw MatrixException("LOAD: invalid file format.");
      }
    }
  }
  file.close();
  *this = tmp;
}

void Matrix::print() const noexcept {
  for(std::size_t i = 0; i < _rows; i++) {
    for(std::size_t j = 0; j < _cols; j++) {
      std::cout << _data[i][j];
      if(j + 1 < _cols)
        std::cout << " ";
    }
    std::cout << std::endl;
  }
}

Matrix& Matrix::operator=(Matrix m) noexcept {
  if(&m == this)
    return *this;
  std::swap(_rows, m._rows);
  std::swap(_cols, m._cols);
  std::swap(_data, m._data);
  return *this;
}

Matrix& Matrix::operator+=(const Matrix& m) {
  if(_rows != m._rows || _cols != m._cols)
    throw MatrixException("ADD: dimensions do not match.");

  for(std::size_t i = 0; i < _rows; i++)
    for(std::size_t j = 0; j < _cols; j++)
      _data[i][j] += m._data[i][j];
  return *this;
}

Matrix& Matrix::operator*=(const Matrix& m) {
  if(_cols != m._rows)
    throw MatrixException("MUL: #arg1.columns != #arg2.rows.");

  Matrix res(_rows, m._cols);
  for(std::size_t i = 0; i < _rows; i++)
    for(std::size_t j = 0; j < m._cols; j++)
      for(std::size_t k = 0; k < _cols; k++)
        res._data[i][j] += _data[i][k] * m._data[k][j];

  *this = res;
  return *this;
}

MatrixException::MatrixException(std::string msg) : logic_error(msg) {}
