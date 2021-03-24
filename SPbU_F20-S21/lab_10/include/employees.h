#ifndef LAB11_EMPLOYEES_H_INCLUDED
#define LAB11_EMPLOYEES_H_INCLUDED

#include <stdint.h>
#include <iostream>
#include <cassert>
#include <vector>
#include <fstream>
#include <string>

class Employee {
public:
  Employee(std::string post);

  virtual ~Employee();

  virtual int salary() const = 0;
  std::string get_post();

  virtual std::ostream& print(std::ostream& out) const;
  virtual std::istream& read(std::istream& in);
  virtual std::ofstream& print_f(std::ofstream& out) const;
  virtual std::ifstream& read_f(std::ifstream& in);

  friend std::istream& operator >>(std::istream& in, Employee& e);
  friend std::ostream& operator <<(std::ostream& out, Employee const & e);

  friend std::ifstream& operator >>(std::ifstream& in, Employee& e);
  friend std::ofstream& operator <<(std::ofstream& out, Employee const & e);

  static Employee* create(std::istream& in);
  static Employee* create_f(std::ifstream& in);

protected:
  std::string post;
  std::string _name;
  int32_t _base_salary;
};

class Developer : public Employee {
public:
  // Сделано для того, чтобы можно было обращаться к TYPE без экземпляра класса
  inline static const int TYPE = 1;
public:
  int salary() const override {
    int salary = _base_salary;
    if (_has_bonus) { salary += 1000; }
    return salary;
  }

  Developer();

  std::ostream& print(std::ostream& out) const override;
  std::istream& read(std::istream& in) override;
  std::ofstream& print_f(std::ofstream& out) const override;
  std::ifstream& read_f(std::ifstream& in) override;

private:
  bool _has_bonus;
};

class SalesManager : public Employee {
public:
  // Сделано для того, чтобы можно было обращаться к TYPE без экземпляра класса
  inline static const int TYPE = 2;
public:
  int salary() const override {
    return _base_salary + _sold_nm * _price * 0.01;
  }

  SalesManager();

  std::ostream& print(std::ostream& out) const override;
  std::istream& read(std::istream& in) override;
  std::ofstream& print_f(std::ofstream& out) const override;
  std::ifstream& read_f(std::ifstream& in) override;

private:
  int32_t _sold_nm, _price;
};

class EmployeesArray {
public:
  EmployeesArray();
  ~EmployeesArray();

  void add(const Employee *e);
  void add(EmployeesArray const & a);
  int total_salary() const;

  void free();

  friend std::ifstream& operator >>(std::ifstream& in, EmployeesArray & a);
  friend std::ostream& operator <<(std::ostream& out, EmployeesArray const & a);
  friend std::ofstream& operator <<(std::ofstream& out, EmployeesArray const & a);

private:
  std::vector<Employee*> _employees;
};

#endif
