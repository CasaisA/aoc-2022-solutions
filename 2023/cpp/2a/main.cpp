#include <fstream>
#include <iostream>
#include <map>
#include <math.h> /* pow */
#include <regex>
#include <vector>

// #include <bits/stdc++.h>
using strings = std::vector<std::string>;
struct OpenFile {
  OpenFile(std::string name) { m_input.open(name, std::ios::in); }
  ~OpenFile() {
    m_input.close();
    // printf("calling dtor\n");
  }
  std::fstream m_input;
  std::fstream *getInput() { return &m_input; }
};
int str_to_idx(std::string input) {
  int out_idx = 0;
  unsigned digit_len = 0;
  for (int p = 0; p < input.length(); p++) {
    if (std::isdigit(input[p]))
      digit_len++;
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
std::vector<std::string> tokenize(std::string line, const char *delimiter) {
  strings output;
  std::string temp = "";
  for (int i = 0; i < line.size(); i++) {
    if (line[i] == *delimiter) {
      output.push_back(temp);
      temp = "";
    }

    else
      temp += line[i];
  }
  output.push_back(temp);
  return output;
}
int main() {
  OpenFile myfile("input.txt");
  auto *p = myfile.getInput();
  std::string tp;
  int final_result = 0;
  while (std::getline(*p, tp)) {
    auto semicolon = tokenize(tp, ":");
    auto game_idx_str = semicolon[0];
    const auto rest = semicolon[1];
    auto game_idx = str_to_idx(game_idx_str);
    std::cout << "game_idx " << game_idx_str << std::endl;
    auto games = tokenize(rest, ";");
    bool game_ok = true;
    for (int game_i = 0; game_i < games.size(); game_i++) {
      int reds = 0;
      int greens = 0;
      int blues = 0;
      auto colors = tokenize(games[game_i], ",");
      for (std::string color : colors) {
        auto value = str_to_idx(color);
        std::cout << color << " " << value << std::endl;
        if (color.find("red")!= std::string::npos)
          reds+=value;
        if (color.find("blue")!= std::string::npos)
          blues+=value;
        if (color.find("green")!= std::string::npos)
          greens+=value;
      }
      if (!(reds <= 12 && greens <= 13 && blues <= 14)) {
        game_ok = false;
        break;
      }
    }
    if (game_ok)
      final_result += game_idx;
  }
  std::cout << final_result << std::endl;
}
