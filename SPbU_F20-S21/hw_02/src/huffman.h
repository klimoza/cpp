#pragma once
#include <climits>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <memory>

namespace huffman {

class BufferedStream {
 protected:
 #ifdef HUFFMAN_TESTS
   public:
 #endif

  const std::size_t buffer_size = 8;

  unsigned char buffer;
  std::size_t i;
  std::size_t bits = 0;

 public:
  BufferedStream();
  std::size_t get_statistics();
};

class BufferedReader : public BufferedStream {
 private:
 #ifdef HUFFMAN_TESTS
   public:
 #endif

  std::ifstream input;

 public:
  BufferedReader(std::string filename);

  int get_file_size();
  bool good();

  int read_bit();
  unsigned char read_char();
  int read_int();
};

class BufferedWriter : public BufferedStream {
 private:
 #ifdef HUFFMAN_TESTS
   public:
 #endif

  std::ofstream output;
  std::string string_stream;
  std::size_t pos;
  bool is_string_stream = false;
  void flush();
  void print_buffer();

 public:
  ~BufferedWriter();
  BufferedWriter(std::string string_stream, std::size_t pos);
  BufferedWriter(std::string filename);

  bool good();

  void write_bit(int x);
  void write_char(unsigned char c);
  void write_int(int x);
};

class TreeNode {
 private:
 #ifdef HUFFMAN_TESTS
   public:
 #endif

  TreeNode *left, *right;
  bool is_terminal;
  unsigned char symbol;

  bool equal(TreeNode *t);
 public:
  TreeNode(BufferedReader& reader);
  TreeNode(unsigned char symbol);
  TreeNode(TreeNode* left, TreeNode* right);
  ~TreeNode();

  void print(BufferedWriter& writer);
  unsigned char decode_symbol(BufferedReader& reader);

  void build_codes(std::vector<bool>* codes, std::vector<bool>& stack);
};

class HuffTree {
 private:
 #ifdef HUFFMAN_TESTS
   public:
 #endif

  static const std::size_t A = 1 << CHAR_BIT;

  std::vector<bool> codes[A];
  TreeNode *root;

  void build_codes();
  std::vector<std::pair<int, TreeNode*>> create_table(std::ifstream& input);
  TreeNode* table_to_tree(std::vector<std::pair<int, TreeNode*>> table);

 public:
  HuffTree(std::ifstream& input);
  HuffTree(BufferedReader& reader);
  ~HuffTree();

  void print_tree(BufferedWriter& writer);
  void encode_symbol(unsigned char c, BufferedWriter& writer);
  unsigned char decode_symbol(BufferedReader& reader);
};

class HuffmanArchiver {
 public:
  class Statistics {
   public:
    std::size_t n1, n2, n3;

    Statistics();
    Statistics(std::size_t n1, std::size_t n2, std::size_t n3);
    void print();
  };

  static int get_file_size(std::ifstream& input);
  static Statistics encode(std::string in, std::string out);
  static Statistics decode(std::string in, std::string out);
};

}  // namespace huffman
