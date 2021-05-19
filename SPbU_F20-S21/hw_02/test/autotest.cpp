#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#define HUFFMAN_TESTS
#include "doctest.h"
#include "huffman.h"

const std::string big = "res/big.txt";
const std::string asmongold = "res/asmongold.txt";
const std::string zero_file = "res/zero_file";
const std::string treenode_test = "res/treenode_test";

TEST_CASE("BufferedReader") {
  SUBCASE("function: get_file_size()") {
    SUBCASE("file: big.txt") {
      CHECK(huffman::BufferedReader(big).get_file_size() == 377796);
    }
    SUBCASE("file: asmongold.txt") {
      CHECK(huffman::BufferedReader(asmongold).get_file_size() == 38);
    }
    SUBCASE("file: zero_file") {
      CHECK(huffman::BufferedReader(zero_file).get_file_size() == 0);
    }
  }

  SUBCASE("function: get_statistics()") {
    huffman::BufferedReader reader(big);
    CHECK(reader.get_statistics() == 0);

    for(int i = 0; i < 2; i++)
      reader.read_bit();
    CHECK(reader.get_statistics() == 1);

    for(int i = 0; i < 2; i++)
      reader.read_char();
    CHECK(reader.get_statistics() == 3);

    reader.read_int();
    CHECK(reader.get_statistics() == 7);

    for(int i = 0; i < CHAR_BIT - 2; i++) {
      reader.read_bit();
      CHECK(reader.get_statistics() == 7);
    }

    reader.read_bit();
    CHECK(reader.get_statistics() == 8);
  }

  SUBCASE("function: good()") {
    SUBCASE("file exsits") {
      CHECK(huffman::BufferedReader(big).good());
      CHECK(huffman::BufferedReader(asmongold).good());
      CHECK(huffman::BufferedReader(zero_file).good());
    }
    SUBCASE("file doesn't exists") {
      CHECK(!huffman::BufferedReader("something_that_doesnt_exists").good());
    }
  }

  SUBCASE("function: read_bit()") {
    SUBCASE("file: big.txt") {
      huffman::BufferedReader reader(big);
      std::string ans = "010011000110111101110010011001010110110100100000";
      for(int i = 0; i < 6 * CHAR_BIT; i++)
        CHECK((ans[i] - '0') == reader.read_bit());
    }

    SUBCASE("file: asmongold.txt") {
      huffman::BufferedReader reader(asmongold);
      std::string ans = "010100110101010101010000001000000101100101000001"
                        "010011000100110000001010000010100100100101010100"
                        "010100110010000001001101010001010000101001001001"
                        "010101000101001100100000010110010100000100100000"
                        "010000100100111101011001001000000100000101010011"
                        "010011010100111101001110010001110100111101001100"
                        "0100010000001010";
      for(int i = 0; i < 38 * CHAR_BIT; i++)
        CHECK((ans[i] - '0') == reader.read_bit());
      try {
        reader.read_bit();
        CHECK(false);
      } catch(std::exception &e) {
        CHECK(!strcmp(e.what(), "Broken input file"));
      }
    }

    SUBCASE("file: zero_file") {
      try {
        huffman::BufferedReader(zero_file).read_bit();
        CHECK(false);
      } catch(std::exception &e) {
        CHECK(!strcmp(e.what(), "Broken input file"));
      }
    }
  }
  SUBCASE("function: read_char()") {
    SUBCASE("file: big.txt") {
      huffman::BufferedReader reader(big);
      std::string ans = "Lorem ";
      for(int i = 0; i < 6; i++)
        CHECK(ans[i] == reader.read_char());
    }

    SUBCASE("file: asmongold.txt") {
      huffman::BufferedReader reader(asmongold);
      std::string ans = "SUP YALL\n"
                        "\n"
                        "ITS ME\n"
                        "ITS YA BOY ASMONGOLD";
      for(int i = 0; i < 37; i++) {
        CHECK(ans[i] == reader.read_char());
      }
      reader.read_char();
      try {
        reader.read_char();
        CHECK(false);
      } catch(std::exception &e) {
        CHECK(!strcmp(e.what(), "Broken input file"));
      }
    }

    SUBCASE("file: zero_file") {
      try {
        huffman::BufferedReader(zero_file).read_char();
        CHECK(false);
      } catch(std::exception &e) {
        CHECK(!strcmp(e.what(), "Broken input file"));
      }
    }
  }

  SUBCASE("function: read_int()") {
    huffman::BufferedReader reader(big);
    std::vector<int> ans = {1282372197, 1830840688, 1937075488};
    for(int i = 0; i < 3; i++)
      CHECK(ans[i] == reader.read_int());
  }
}

TEST_CASE("TreeNode") {
  huffman::TreeNode* ans1 = new huffman::TreeNode(127);
  huffman::TreeNode* ans2 = new huffman::TreeNode(16);
  huffman::TreeNode* ans3 = new huffman::TreeNode(56);
  huffman::TreeNode* ans4 = new huffman::TreeNode(ans2, ans3);
  huffman::TreeNode ans5(ans1, ans4);

  SUBCASE("constructor: TreeNode(BufferedReader)") {
    huffman::BufferedReader reader(treenode_test);
    huffman::TreeNode res = huffman::TreeNode(reader);
    CHECK(ans5.equal(&res));
  }

  SUBCASE("function: print()") {
    huffman::BufferedWriter writer("", 0);
    ans5.print(writer);
    writer.flush();
    CHECK(writer.string_stream == "01011111110100010000100111000000");
  }
}
