#include "huffman.h"

// ------- BufferedStream ------- //

huffman::BufferedStream::BufferedStream() : buffer(0), i(buffer_size) {}

huffman::BufferedReader::BufferedReader(std::string filename)
    : BufferedStream(), input(std::ifstream(filename, std::ios::binary)) {}

huffman::BufferedWriter::BufferedWriter(std::string string_stream, std::size_t pos)
  : string_stream(string_stream), pos(pos), is_string_stream(true) {}

huffman::BufferedWriter::BufferedWriter(std::string filename)
    : BufferedStream(), output(std::ofstream(filename, std::ios::binary)) {}

void huffman::BufferedWriter::print_buffer() {
  if(!is_string_stream) {
    if(!output.write((char*)&buffer, sizeof(char)))
      throw std::invalid_argument("Output file has disappeared");
  } else {
    for(int i = buffer_size - 1; i >= 0; i--)
      if((1 << i) & buffer)
        string_stream += "1";
      else
        string_stream += "0";
  }
}

void huffman::BufferedWriter::flush() {
  if (i != buffer_size) {
    buffer <<= i;
    print_buffer();
  }
  buffer = 0;
}

huffman::BufferedWriter::~BufferedWriter() {
  flush();
}

std::size_t huffman::BufferedStream::get_statistics() {
  return (bits + CHAR_BIT - 1) / (CHAR_BIT);
}

int huffman::BufferedReader::get_file_size() {
  return HuffmanArchiver::get_file_size(input);
}

int huffman::BufferedReader::read_bit() {
  bits++;
  if (i == buffer_size) {
    if (!input.read((char*)&buffer, sizeof(char)))
      throw std::invalid_argument("Broken input file");
    i = 0;
  }
  int x = (bool)((buffer << i) & (1 << (buffer_size - 1)));
  i++;
  return x;
}

void huffman::BufferedWriter::write_bit(int x) {
  bits++;
  buffer = (buffer << 1) | x;
  i--;
  if (!i) {
    print_buffer();
    i = buffer_size;
  }
}

unsigned char huffman::BufferedReader::read_char() {
  bits += CHAR_BIT;
  if (!i) {
    i = buffer_size;
    return buffer;
  }
  unsigned char c;
  if(!input.read((char*)&c, sizeof(char)))
    throw std::invalid_argument("Broken input file");
  unsigned char tmp = (buffer << i) | (c >> (buffer_size - i));
  buffer = c & ((1 << (buffer_size - i)) - 1);
  return tmp;
}

void huffman::BufferedWriter::write_char(unsigned char c) {
  bits += CHAR_BIT;
  buffer = (buffer << i) | (c >> (buffer_size - i));
  print_buffer();
  buffer = (c & ((1 << (buffer_size - i)) - 1));
}

int huffman::BufferedReader::read_int() {
  int x = 0;
  for (int i = (CHAR_BIT * sizeof(int) / buffer_size) - 1; i >= 0; i--)
    x += (int)read_char() << (i * buffer_size);
  return x;
}

void huffman::BufferedWriter::write_int(int x) {
  for (int i = (CHAR_BIT * sizeof(int) / buffer_size) - 1; i >= 0; i--)
    write_char((x >> (i * buffer_size)) & ((1 << buffer_size) - 1));
}

bool huffman::BufferedReader::good() {
  return input.good();
}

bool huffman::BufferedWriter::good() {
  return output.good();
}

// ------- TreeNode ------- //

huffman::TreeNode::TreeNode(unsigned char symbol)
    : left(nullptr), right(nullptr), is_terminal(true), symbol(symbol){};

huffman::TreeNode::TreeNode(TreeNode *left, TreeNode *right)
    : left(left), right(right), is_terminal(false), symbol(0){};

huffman::TreeNode::TreeNode(BufferedReader &reader) {
  if (!reader.read_bit()) {
    left = new TreeNode(reader);
    right = new TreeNode(reader);
    is_terminal = false;
  } else {
    symbol = reader.read_char();
    is_terminal = true;
  }
}

huffman::TreeNode::~TreeNode() {
  if (!is_terminal) {
    delete left;
    delete right;
  }
}

// https://stackoverflow.com/questions/759707/efficient-way-of-storing-huffman-tree
void huffman::TreeNode::print(BufferedWriter &writer) {
  if (is_terminal) {
    writer.write_bit(1);
    writer.write_char(symbol);
  } else {
    writer.write_bit(0);
    left->print(writer);
    right->print(writer);
  }
}

unsigned char huffman::TreeNode::decode_symbol(BufferedReader &reader) {
  if (is_terminal)
    return symbol;
  else if (reader.read_bit())
    return right->decode_symbol(reader);
  else
    return left->decode_symbol(reader);
}

void huffman::TreeNode::build_codes(std::vector<bool> *codes, std::vector<bool> &stack) {
  if (is_terminal) {
    codes[symbol] = stack;
  } else {
    stack.push_back(0);
    left->build_codes(codes, stack);
    stack.back() = 1;
    right->build_codes(codes, stack);
    stack.pop_back();
  }
}

bool huffman::TreeNode::equal(TreeNode *t) {
  if(is_terminal) {
    return (t->is_terminal && symbol == t->symbol);
  } else {
    return !t->is_terminal && left->equal(t->left) && right->equal(t->right);
  }
}

// ------- HuffTree ------- //

std::vector<std::pair<int, huffman::TreeNode*>>
huffman::HuffTree::create_table(std::ifstream &input) {
  std::vector<std::pair<int, TreeNode *>> table(A);
  for (std::size_t i = 0; i < A; i++)
    table[i] = std::make_pair(0, new TreeNode(i));

  unsigned char c;
  while (input.read((char*)&c, sizeof(char)))
    table[c].first++;

  std::size_t i = 0;
  while (table.size() > 1 && i < table.size()) {
    if (!table[i].first) {
      std::swap(table[i], table.back());
      delete table.back().second;
      table.pop_back();
    } else {
      i++;
    }
  }

  return table;
}

huffman::TreeNode* huffman::HuffTree::table_to_tree(std::vector<std::pair<int, TreeNode*>> table) {
  while (table.size() > 1) {
    std::size_t m_1 = 0, m_2 = 1;
    if (table[m_1].first > table[m_2].first)
      std::swap(m_1, m_2);

    for (std::size_t i = 2; i < table.size(); i++) {
      if (table[i].first < table[m_1].first) {
        m_2 = m_1;
        m_1 = i;
      } else if (table[i].first <= table[m_2].first) {
        m_2 = i;
      }
    }

    table.push_back(
        std::make_pair(table[m_1].first + table[m_2].first,
                       new TreeNode(table[m_1].second, table[m_2].second)));

    std::swap(table[m_1], table.back());
    table.pop_back();
    std::swap(table[m_2], table.back());
    table.pop_back();
  }
  return table[0].second;
}

huffman::HuffTree::HuffTree(std::ifstream &input) {
  root = table_to_tree(create_table(input));
  build_codes();
}

huffman::HuffTree::HuffTree(BufferedReader &reader) {
  root = new TreeNode(reader);
  build_codes();
}

huffman::HuffTree::~HuffTree() {
  delete root;
}

void huffman::HuffTree::build_codes() {
  std::vector<bool> stack;
  root->build_codes(codes, stack);
}

void huffman::HuffTree::print_tree(BufferedWriter &writer) {
  root->print(writer);
}

void huffman::HuffTree::encode_symbol(unsigned char c, BufferedWriter &writer) {
  for (int b : codes[c])
    writer.write_bit(b);
}

unsigned char huffman::HuffTree::decode_symbol(BufferedReader &reader) {
  return root->decode_symbol(reader);
}

// ------- HuffmanArchiver ------- //

int huffman::HuffmanArchiver::get_file_size(std::ifstream &input) {
  input.seekg(0, std::ios::end);
  int file_size = input.tellg();
  input.seekg(0, std::ios::beg);
  return file_size;
}

huffman::HuffmanArchiver::Statistics huffman::HuffmanArchiver::encode(std::string in, std::string out) {
  Statistics stat;
  std::ifstream input(in, std::ios::binary);
  BufferedWriter writer(out);
  if(!input.good() || !writer.good())
    throw std::invalid_argument("Bad file names");

  int file_size = get_file_size(input);
  stat.n1 = file_size;
  HuffTree tree = HuffTree(input);

  writer.write_int(file_size);
  tree.print_tree(writer);

  stat.n3 = writer.get_statistics();

  input.clear();
  input.seekg(0, std::ios::beg);

  unsigned char c;
  while (input.read((char *)&c, sizeof(char)))
    tree.encode_symbol(c, writer);

  stat.n2 = writer.get_statistics() - stat.n3;
  return stat;
}

huffman::HuffmanArchiver::Statistics huffman::HuffmanArchiver::decode(std::string in, std::string out) {
  BufferedReader reader(in);
  std::ofstream output(out, std::ios::binary);
  if(!reader.good() || !output.good())
    throw std::invalid_argument("Bad file names");

  std::size_t file_size = reader.get_file_size();
  std::size_t text_size = reader.read_int();
  HuffTree tree = HuffTree(reader);

  Statistics stat(file_size - reader.get_statistics(), text_size, reader.get_statistics());

  for (std::size_t i = 0; i < text_size; i++) {
    unsigned char c = tree.decode_symbol(reader);
    output.write((char *)&c, sizeof(char));
  }
  return stat;
}

huffman::HuffmanArchiver::Statistics::Statistics() : n1(0), n2(0), n3(0) {}

huffman::HuffmanArchiver::Statistics::Statistics(std::size_t n1, std::size_t n2, std::size_t n3)
    : n1(n1), n2(n2), n3(n3) {}

void huffman::HuffmanArchiver::Statistics::print() {
  std::cout << n1 << std::endl << n2 << std::endl << n3 << std::endl;
}
