#include "employees.h"

Employee::Employee(std::string post, int type) : post(post), type(type) {}

Employee::~Employee() {}

std::string Employee::get_post() {
  return post;
}

Employee* get_employee(int tp) {
  switch (tp) {
    case (int)Employee::Types::Developer:
      return new Developer;
    case (int)Employee::Types::SalesManager:
      return new SalesManager;
    default:
      assert(false);
  }
}

Employee* Employee::create(std::istream& in) {
  int tp;
  in >> tp;
  Employee* e = get_employee(tp);
  in >> *e;
  return e;
}

Employee* Employee::create_f(std::ifstream& in) {
  int tp = 0;
  in.read((char*) &tp, sizeof(int));
  Employee* e = get_employee(tp);
  in >> *e;
  return e;
}

Developer::Developer() : Employee("Developer", 1) {}

int Developer::salary() const {
  int salary = _base_salary;
  if (_has_bonus) { salary += 1000; }
  return salary;
}

SalesManager::SalesManager() : Employee("Sales Manager", 2) {}

int SalesManager::salary() const {
  return _base_salary + _sold_nm * _price * 0.01;
}

std::ostream& Employee::print(std::ostream& out) const {
  return out << "Name: " << _name << std::endl
             << "Base Salary: " << _base_salary << std::endl;
}

std::ostream& Developer::print(std::ostream& out) const {
  return Employee::print(out) << "Has bonus: " << (_has_bonus ? '+' : '-');
}

std::ostream& SalesManager::print(std::ostream& out) const {
  return Employee::print(out) << "Sold items: " << _sold_nm << std::endl
                              << "Item price: " << _price;
}

std::ofstream& Employee::print_f(std::ofstream& out) const {
  out.write(_name.c_str(), sizeof(char) * (_name.length() + 1));
  out.write((char*) &_base_salary, sizeof(int));
  return out;
}

std::ofstream& Developer::print_f(std::ofstream& out) const {
  out.write((char*) &type, sizeof(int));
  Employee::print_f(out);
  out.write((char*) &_has_bonus, sizeof(bool));
  return out;
}

std::ofstream& SalesManager::print_f(std::ofstream& out) const {
  out.write((char*) &type, sizeof(int));
  Employee::print_f(out);
  out.write((char*) &_sold_nm, sizeof(int));
  out.write((char*) &_price, sizeof(int));
  return out;
}

std::istream& Employee::read(std::istream& in) {
  return in >> _name >> _base_salary;
}

std::istream& Developer::read(std::istream& in) {
  return Employee::read(in) >> _has_bonus;
}

std::istream& SalesManager::read(std::istream& in) {
  return Employee::read(in) >> _sold_nm >> _price;
}

std::ifstream& Employee::read_f(std::ifstream& in) {
  char c = 0;
  do {
    in.read(&c, sizeof(char));
    if (c)
      _name += c;
  } while (c);
  in.read((char*) &_base_salary, sizeof(int));
  return in;
}

std::ifstream& Developer::read_f(std::ifstream& in) {
  Employee::read_f(in);
  in.read((char*) &_has_bonus, sizeof(bool));
  return in;
}

std::ifstream& SalesManager::read_f(std::ifstream& in) {
  Employee::read_f(in);
  in.read((char*) &_sold_nm, sizeof(int));
  in.read((char*) &_price, sizeof(int));
  return in;
}

//Overloaded operators

std::ostream& operator<<(std::ostream& out, Employee const& e) {
  return e.print(out);
}

std::istream& operator>>(std::istream& in, Employee& e) {
  return e.read(in);
}

std::ofstream& operator<<(std::ofstream& out, Employee const& e) {
  return e.print_f(out);
}

std::ifstream& operator>>(std::ifstream& in, Employee& e) {
  return e.read_f(in);
}

// EmployeesArray

EmployeesArray::EmployeesArray() {
  _employees = std::vector<Employee*>();
}

EmployeesArray::~EmployeesArray() {}

void EmployeesArray::free() {
  for (Employee* e : _employees) {
    delete e;
  }
}

void EmployeesArray::add(const Employee* e) {
  _employees.push_back((Employee*)e);
}

void EmployeesArray::add(EmployeesArray const& a) {
  for (Employee* e : a._employees)
    _employees.push_back(e);
}

int EmployeesArray::total_salary() const {
  int32_t ans = 0;
  for (const Employee* e : _employees)
    ans += e->salary();
  return ans;
}

std::ostream& operator<<(std::ostream& out, EmployeesArray const& a) {
  for (std::size_t i = 0; i < a._employees.size(); i++) {
    out << (i + 1) << ". " << a._employees[i]->get_post() << std::endl
        << *a._employees[i] << std::endl;
  }
  return out << "== Total salary: " << a.total_salary() << std::endl << std::endl;
}

std::ofstream& operator<<(std::ofstream& out, EmployeesArray const& a) {
  int sz = a._employees.size();
  out.write((char*) &sz, sizeof(int));
  for (int i = 0; i < sz; i++)
    out << *a._employees[i];
  return out;
}

std::ifstream& operator>>(std::ifstream& in, EmployeesArray& a) {
  int sz = 0;
  in.read((char*) &sz, sizeof(int));
  a._employees.resize(sz);
  for (int i = 0; i < sz; i++)
    a._employees[i] = Employee::create_f(in);
  return in;
}
