#include <fstream>
#include <iostream>
#include <map>
#include <math.h> /* pow */
#include <regex>
#include <vector>

#include <chrono>
// #include <bits/stdc++.h>
struct OpenFile {
  OpenFile(std::string name) { m_input.open(name, std::ios::in); }
  ~OpenFile() {
    m_input.close();
    // printf("calling dtor\n");
  }
  std::fstream m_input;
  std::fstream *getInput() { return &m_input; }
};
int myatoi(std::string input) {
  int out_idx = 0;
  unsigned digit_len = 0;
  for (int p = 0; p < input.length(); p++) {
    if (std::isdigit(input[p]))
      digit_len++;
    else
      return 0;
  }
  int current_digit = 0;
  for (int p = 0; p < input.length(); p++) {
    if (std::isdigit(input[p])) {
      out_idx += static_cast<int>(input[p] - 0x30) *
                 pow(10, digit_len - current_digit - 1);
      current_digit++;
    }
  }
  return out_idx;
}
struct NumPos {
  NumPos() : digit(""), first(-1), last(-1){};
  std::string digit;
  int first;
  int last;
};

bool adjacent(NumPos digit, std::vector<int> positions, bool current) {
  bool adjacent = false;
  for (int i = 0; i < positions.size(); i++) {
    adjacent |= ((digit.first - positions[i]) == 1) ||
                ((digit.last - positions[i]) == -1);
    // if (!current)
    adjacent |= digit.first <= positions[i] && positions[i] <= digit.last;
    // if (adjacent) std::cout << "digit " << digit.digit << " is adjacent in
    // pos " << positions[i] << std::endl;
  }
  return adjacent;
}
std::vector<NumPos> tokenize_nums(std::string line) {

  std::vector<NumPos> output;
  NumPos temp;
  for (int i = 0; i < line.size(); i++) {
    if (std::ispunct(line[i]) && myatoi(temp.digit) != 0) {
      output.push_back(temp);
      temp = NumPos();
    }

    else if (std::isdigit(line[i])) {
      temp.digit += line[i];
      if (temp.first == -1)
        temp.first = i;
      temp.last = i;
    }
  }
  if (temp.digit.size())
    output.push_back(temp);
  return output;
}
std::vector<int> get_punct_positions(std::string line) {
  std::vector<int> output;
  for (unsigned i = 0; i < line.size(); i++) {
    if (std::ispunct(line[i]) && line[i] != *".") {
      output.push_back(i);
    }
  }
  return output;
}
int local_result(std::string previous_line, std::string current_line,
                 std::string next_line) {

  std::vector<NumPos> next_digits = tokenize_nums(next_line);
  std::vector<NumPos> current_digits = tokenize_nums(current_line);
  std::vector<NumPos> previous_digits = tokenize_nums(previous_line);

  std::vector<int> current_pos = get_punct_positions(current_line);
  std::vector<int> next_pos = get_punct_positions(next_line);
  std::vector<int> previous_pos = get_punct_positions(previous_line);
  bool isadjacent = false;
  int current_result = 0;
  for (auto digit : current_digits) {
    isadjacent |= adjacent(digit, current_pos, true);
    isadjacent |= adjacent(digit, next_pos, false);
    isadjacent |= adjacent(digit, previous_pos, false);
    if (isadjacent) {
      int appender = myatoi(digit.digit);
      current_result += appender;
      isadjacent = false;
    }
  };
  return current_result;
}
int main() {
  auto start = std::chrono::high_resolution_clock::now();
  OpenFile myfile("input.txt");
  auto *p = myfile.getInput();
  std::string tp;
  int final_result = 0;
  bool lastline = false;

  std::string previous_line = "";
  std::string current_line = "";
  std::string next_line = "";
  std::vector<NumPos> next_digits;
  std::vector<NumPos> current_digits;
  std::vector<NumPos> previous_digits;

  std::vector<int> current_pos;
  std::vector<int> next_pos;
  std::vector<int> previous_pos;
  std::getline(*p, current_line);
  unsigned line_counter = 1;
  while (std::getline(*p, next_line)) {
    final_result += local_result(previous_line, current_line, next_line);
    previous_line = current_line;
    current_line = next_line;
    line_counter += 1;
  };

  next_line = "";
  // One more time
  final_result += local_result(previous_line, current_line, next_line);

  auto end = std::chrono::high_resolution_clock::now();
  const std::chrono::duration<float, std::milli> diff = end - start;
  std::cout << "Elapsed " << diff.count() << std::endl;
  std::cout << line_counter << std::endl;
  std::cout << final_result << std::endl;
}
