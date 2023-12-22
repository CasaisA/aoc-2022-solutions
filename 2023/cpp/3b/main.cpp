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
  ~OpenFile() { m_input.close(); }
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

std::pair<unsigned, int> adjacent(int star, std::vector<NumPos> positions) {
  unsigned counter = 0;
  int gear = 1;
  for (int i = 0; i < positions.size(); i++) {
    bool isadjacent = false;
    isadjacent |= ((star - positions[i].first) == -1) ||
                  ((star - positions[i].last) == 1);
    isadjacent |= star >= positions[i].first && positions[i].last >= star;
    if (isadjacent) {
      gear *= std::atoi(positions[i].digit.c_str());
      counter += 1;
    }
  }
  return {counter, gear};
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
    if (line[i] == *"*") {
      output.push_back(i);
    }
  }
  return output;
}
int current_line_result(std::string previous_line, std::string current_line,
                        std::string next_line) {

  std::vector<NumPos> next_digits = tokenize_nums(next_line);
  std::vector<NumPos> previous_digits = tokenize_nums(previous_line);
  std::vector<NumPos> current_digits = tokenize_nums(current_line);

  std::vector<int> current_stars = get_punct_positions(current_line);
  int current_result = 0;
  for (auto star : current_stars) {
    // std::cout << "Star in " << star << std::endl;
    auto [prev_adj, prev_gear] = adjacent(star, previous_digits);
    auto [next_adj, next_gear] = adjacent(star, next_digits);
    auto [this_adj, this_gear] = adjacent(star, current_digits);
    if (prev_adj + next_adj == 2)
      current_result += prev_gear * next_gear;
    else if (prev_adj + this_adj == 2)
      current_result += prev_gear * this_gear;
    else if (next_adj + this_adj == 2)
      current_result += next_gear * this_gear;
    else if (this_adj == 2)
      current_result += this_gear;
  };
  return current_result;
}
int main() {
  auto start = std::chrono::high_resolution_clock::now();
  OpenFile myfile("input.txt");
  auto *input_pointer = myfile.getInput();
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
  std::getline(*input_pointer, current_line);
  unsigned line_counter = 1;
  while (std::getline(*input_pointer, next_line)) {
    final_result += current_line_result(previous_line, current_line, next_line);
    previous_line = current_line;
    current_line = next_line;
    line_counter += 1;
  };

  // One more time
  next_line = "";
  final_result += current_line_result(previous_line, current_line, next_line);

  auto end = std::chrono::high_resolution_clock::now();
  const std::chrono::duration<float, std::milli> diff = end - start;
  std::cout << "Elapsed " << diff.count() << std::endl;
  std::cout << line_counter << std::endl;
  std::cout << final_result << std::endl;
}
