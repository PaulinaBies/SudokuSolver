#pragma once
#include <string>
#include <tuple>
#include <vector>
using std::vector;

class SudokuGame {
 vector<vector<int>> grid_;

 public:
  SudokuGame() = default;
  SudokuGame(std::string filename);

  const std::vector<std::vector<int>>& grid() const {return grid_;};
  void print() const;
  int size() const;
  int value(int row, int column) const {return grid_.at(row).at(column);};
  void value(int row, int column, int newValue) {grid_.at(row).at(column) = newValue;};

  ~SudokuGame() {};
  SudokuGame(const SudokuGame&);
  SudokuGame &operator=(const SudokuGame&);


};



class SudokuPlayer {
 bool check_choice(SudokuGame&, int, int, int) const;

 public:
  SudokuPlayer() = default;
  bool solve(SudokuGame& game) const;
};
