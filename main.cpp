#include <algorithm>
#include <iostream>
#include <fstream>
#include <numeric>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>
#include "main.h"
#include <iterator>
#include <fstream>

using std::vector;
using std::istringstream;
using std::string;
using std::ifstream;
using std::cout;
using std::cin;
using std::endl;


SudokuGame::SudokuGame(std::string filename) {
    ifstream input(filename);

    vector<vector<int>> column;

    string line;
    while (getline(input, line)) {
    vector<int> row;
    for (auto elem: line) {
        if (isdigit(elem)) {
            row.push_back(static_cast<int>(elem) - 48);
        }
    }
    grid_.push_back(row);
    }
}


void SudokuGame::print() const {
    int count_col = 0;
    int count_row = 0;

    for (auto row: grid_) {
        if (count_row == 3 || count_row == 6) {
            cout<<"-------------------------------"<<endl;
        }
        for (auto elem: row) {
            if (count_col == 2 || count_col == 5) {
                cout<<elem<<"  |  ";
            }
            else {
                cout<<elem<<"  ";
            }
            count_col++;
        }
        count_col = 0;
        cout<<endl;
        count_row++;
    }
}

int SudokuGame::size() const {
    int count = 0;

    for (auto row: grid_) {
        count++;
    }

    return count;
}

SudokuGame::SudokuGame(const SudokuGame & sudoku) {
    grid_ = sudoku.grid_;
}

SudokuGame& SudokuGame::operator=(const SudokuGame& sudoku) {
    grid_ = sudoku.grid_;
    return *this;
}



bool SudokuPlayer::check_choice(SudokuGame& game, int row, int col, int n) const{
   
    for (int i = 0; i < 9; i++) {
        if (game.value(row, i) == n) {
            return false;
        }
        if (game.value(i, col) == n) {
            return false;
        }
    }
   
    int row_start = row - (row % 3);
    int col_start = col - (col % 3);

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (game.value(i + row_start, j + col_start) == n) {
                return false;
            }
        }
    }
    
    return true;
}

/// 
/// @param game the game to solve 
/// @return 
bool SudokuPlayer::solve(SudokuGame& game) const {
    
    int row = 0;
    int col = 0;
    bool found = false;

    for (row = 0; row < 9; row++) {
        for (col = 0; col < 9; col++) {
            if (game.value(row, col) == 0) {
                found = true;
                break;
            }
        }
        if (found == true) {
            break;
        }
    }
    if (row == 9 && col == 9) {
        return true;
    }
    for (int i = 1; i <= 9; i++) {
        if (check_choice(game, row, col, i)) {
            game.value(row, col, i);
            if (solve(game) == true)
                return true;
            game.value(row, col, 0);
        }
    }
    
    return false;
}





int main() {

   cout<<"Input file name: ";
   string file;
   cin>>file; 

  SudokuGame game(file);
  SudokuPlayer player;
  cout<<"Original:"<<endl;
  cout<<endl;
  game.print();
  player.solve(game);
  cout<<endl;
  cout<<"Solved:"<<endl;
  cout<<endl;
  game.print();


  return 0;
}