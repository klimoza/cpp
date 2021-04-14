#include "matrix.h"
#include <iostream>

int read_register() {
  std::string reg;
  std::cin >> reg;
  return (reg[1] - '0');
}

int main() {
  Matrix* ar = new Matrix[10];
  std::string s;
  while(std::cin >> s) {
    try {
      if(s == "exit") {
        break;
      } else if(s == "load") {
        int i = read_register();
        std::string filename;
        std::cin >> filename;
        ar[i].load(filename);
      } else if (s == "print") {
        int i = read_register();
        ar[i].print();
      } else if(s == "add") {
        int i = read_register();
        int j = read_register();
        ar[i] += ar[j];
      } else if(s == "mul") {
        int i = read_register();
        int j = read_register();
        ar[i] *= ar[j];
      } else if(s == "elem") {
        int i = read_register();
        int x, y;
        std::cin >> x >> y;
        ar[i].elem(x, y);
      }
    } catch (MatrixException &e) {
      std::cout << e.what() << std::endl;
    } catch (std::bad_alloc &e) {
      std::cout << "Unable to allocate memory." << std::endl;
    }
  }
  delete [] ar;
  return 0;
}
