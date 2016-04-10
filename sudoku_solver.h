#ifndef Sudoku_H
#define Sudoku_H

class Sudoku {

public:
	~Sudoku();

        bool solve(); // solves the puzzle
        void setval(int i, int j, int val);
        int printval(int i, int j);

private:
	bool isValid(int row, int col);
	bool solveHelper(int row, int col);
        int board[9][9];
};

#endif
