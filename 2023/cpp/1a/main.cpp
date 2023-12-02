#include <fstream>
#include <iostream>

struct OpenFile {
  OpenFile(std::string name) { m_input.open(name, std::ios::in); }
  ~OpenFile() {
    m_input.close();
    printf("calling dtor\n");
  }

  std::fstream m_input;
  std::fstream *getInput() { return &m_input; }
};
inline bool isdigit(char in) { return (int)in > 0x2f && (int)in < 0x3a; }
int main() {
  int uno = 1;
  OpenFile myfile("input.txt");
  auto *p = myfile.getInput();
  std::string tp;
  int final_result = 0;
  while (std::getline(*p, tp)) {
    printf("%s\n", tp.c_str());
    int leftmost = -1;
    int rightmost = -1;
    for (std::string::iterator c = tp.begin(); c != tp.end(); c++) {
      if (std::isdigit(*c)) {
        if (leftmost == -1) {
          leftmost = *c - *"0";
        }
        rightmost = *c - *"0";
      }
    }
    final_result += leftmost * 0xa + rightmost;
  }
  std::cout << "final_result: " << final_result << "\n";
}
