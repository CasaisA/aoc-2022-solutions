#include <fstream>
#include <iostream>
#include <map>

struct OpenFile {
  OpenFile(std::string name) { m_input.open(name, std::ios::in); }
  ~OpenFile() {
    m_input.close();
    // printf("calling dtor\n");
  }
  std::fstream m_input;
  std::fstream *getInput() { return &m_input; }
};
inline bool isdigit(char in) { return (int)in > 0x2f && (int)in < 0x3a; }

int main() {
  std::map<std::string, int> m{{"one", 1},   {"two", 2},   {"three", 3},
                               {"four", 4},  {"five", 5},  {"six", 6},
                               {"seven", 7}, {"eight", 8}, {"nine", 9}};
  OpenFile myfile("./input.txt");
  auto *p = myfile.getInput();
  std::string tp;
  int final_result = 0;
  int counter = 1;
  while (std::getline(*p, tp)) {
    int leftmost = -1;
    int rightmost = -1;
    std::string buffer{""};
    for (std::string::iterator c = tp.begin(); c != tp.end(); c++) {
      if (isdigit(*c)) {
        if (leftmost == -1) {
          leftmost = *c - *"0";
        }
        rightmost = *c - *"0";
      }

      else {
        buffer += *c;
        for (std::map<std::string, int>::iterator it = m.begin(); it != m.end();
             it++) {
          if (buffer.find(it->first) != std::string::npos) {
            if (leftmost == -1)
              leftmost = it->second;
            rightmost = it->second;
            buffer = *c;
          }
        }
      }
    }
    int32_t line_result = leftmost * 10 + rightmost;
    std::cout << counter++ << ": " <<  tp << std::endl;
    std::cout << line_result << std::endl;
    final_result += line_result;
  }
  std::cout << "final_result: " << final_result << "\n";
}
