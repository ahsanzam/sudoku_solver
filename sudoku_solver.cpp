#include "sudoku_solver.h"

void Sudoku::setval(int i, int j, int val){
    board[i][j] = val;
}
int Sudoku::printval(int i, int j){
    return board[i][j];
}

Sudoku::~Sudoku() {
}

bool Sudoku::isValid(int row, int col) {
  int value = board[row][col];

  for (int i=0; i<9; i++) {
    if (i == row) {
    continue;
    }
    
    int temp = board[i][col];
    if (temp == value) {
      return false;
    }
  }
  
  for (int i=0; i<9; i++) {
      if (i == col) {
      continue;
    }
    
    int temp = board[row][i];
    if (temp == value) {
      return false;
    }
  }
  
  int box_row = row / 3; 
  int box_col = col / 3; 
  
  for (int i=box_row * 3; i < box_row * 3 + 3; i++) {
    for (int j=box_col * 3; j < box_col * 3 + 3; j++) {
      if (i == row && j == col) {
        continue;
      }
      
      int temp = board[i][j];
      if (temp == value) {
        return false;
      }
    }
  }
  
  return true;
}

bool Sudoku::solve(){
  return solveHelper(0, 0);
}


bool Sudoku::solveHelper(int row, int col) {
  if( board[row][col] == 0 ){
    for(int k=1; k<10; k++){
      board[row][col] = k;
      if( isValid(row, col) ){
        if( row == 8 && col == 8 ) return true; //at end of puzzle; last square
        else if( col == 8 ) { //jump to next row if at end of columns
          if( solveHelper(row+1, 0) ) return true; 
          else board[row][col] = 0;
        }
        else if( solveHelper(row, col+1) ) return true; //else increment column 
        else board[row][col] = 0;
      }
      else board[row][col] = 0; //reset for next number
      if( k==9 ) return false; //if no numbers fit
    }
  }
  if(row == 8 && col == 8 ) return true; 
  else if( col == 8 ) return solveHelper(row+1, 0);
  else return solveHelper(row, col+1);
} 
