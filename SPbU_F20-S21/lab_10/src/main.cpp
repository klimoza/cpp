#include "employees.h"
#include <string>
#include <iostream>
#include <fstream>

int main() {
  std::string s;
  EmployeesArray list;
  while(std::cin >> s) {
    if(s == "exit") {
      break;
    } else if(s == "load") {
      std::string filename;
      std::cin >> filename;

      std::ifstream file;
      file.open(filename, std::ios::binary);
      EmployeesArray tmp_list;
      file >> tmp_list;
      list.add(tmp_list);

      file.close();
    } else if(s == "save") {
      std::string filename;
      std::cin >> filename;

      std::ofstream file;
      file.open(filename, std::ios::binary);
      file << list;

      file.close();
    } else if(s == "add") {
      list.add(Employee::create(std::cin));
    } else if(s == "list") {
      std::cout << list;
    }
  }
  list.free();
  return 0;
}
