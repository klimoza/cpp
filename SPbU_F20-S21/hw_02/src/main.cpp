#include <cassert>
#include <string_view>

#include "huffman.h"

int main(int argc, char *argv[]) {
  assert(argc == 6);
  int type = -1;
  std::string in = "";
  std::string out = "";
  for (int i = 1; i < argc; i++) {
    std::string_view arg = argv[i];
    if (arg == "-c") {
      assert(type == -1);
      type = 0;
    } else if (arg == "-u") {
      assert(type == -1);
      type = 1;
    } else if (arg == "-f" || arg == "--file") {
      assert(i != argc - 1 && in == "");
      in = argv[i + 1];
      i++;
    } else if (arg == "-o" || arg == "--output") {
      assert(i != argc - 1 && out == "");
      out = argv[i + 1];
      i++;
    } else {
      assert(false);
    }
  }
  assert(type != -1 && in != "" && out != "" && in != out);
  try {
    if (!type)
      huffman::HuffmanArchiver::encode(in, out).print();
    else
      huffman::HuffmanArchiver::decode(in, out).print();
  } catch (std::exception &e) {
    std::cout << e.what() << std::endl;
    return 1;
  }
  return 0;
}
