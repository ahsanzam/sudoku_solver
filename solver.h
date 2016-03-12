/*
  Author: Ahsan Zaman
  Email: ahsanzam@usc.edu
*/
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

class Solver{
public:
	Solver(ifstream* infile);
	int solve();
private:
	//functs for easy access
	bool h(int row, int num_to_check);
	bool v(int col, int num_to_check);
	bool s(int square, int num_to_check);
	int p(int ver, int hor);

	//creates sets of possible values for each empty box
	void markup();

	//convert row,col number to square number
	int to_square(int i, int j);

	//writes result to file
	void write_to_file();

	//member vars
	int blanks;
	//array containing the actual puzzle
	int puzzle[9][9];
	//array of vectors containing possible vals 
	vector<int>* prem;
	//arrays containing whether a row/col/square has a number
	bool horz[9][9];
	bool vert[9][9];
	bool squares[9][9];

};
