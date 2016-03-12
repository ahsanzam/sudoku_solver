/*
  Author: Ahsan Zaman
  Email: ahsanzam@usc.edu
*/
#include "solver.h"

//constructor
Solver::Solver(ifstream* infile)
{
	//set initial vals to false
	for(int i=0; i<9; i++){
		for(int j=0; j<9; j++){
			horz[i][j] = false;
			vert[i][j] = false;
			squares[i][j] = false;
		}
	}
	//read in puzzle and set horz array
	for(int i=0; i<9; i++){
		for(int j=0; j<9; j++){
			*infile >> puzzle[i][j];
			if(puzzle[i][j] == 0){
				puzzle[i][j] = blanks*-1;
				blanks++;
			}
			else horz[i][puzzle[i][j]-1] = true;
		}
	}
	//set vert array
	for(int i=1; i<10; i++){
		for(int j=1; j<10; j++)
			if(p(j,i) > 0) vert[i-1][p(j,i)-1] = true;
	}
	//set squares array
	for(int i=0; i<9; i++){
		if(i<3){
			for(int j=0; j<3; j++){
				for(int k=i*3; k<3+i*3; k++)
					if(puzzle[j][k] > 0) squares[i][puzzle[j][k]-1] = true;
			}
		}
		else if(i<6){
			for(int j=3; j<6; j++){
				for(int k=i*3-9; k<i*3-6; k++)
					if(puzzle[j][k] > 0) squares[i][puzzle[j][k]-1] = true;
			}
		}
		else if(i<9){
			for(int j=6; j<9; j++){
				for(int k=i*3-18; k<i*3-15; k++)
					if(puzzle[j][k] > 0) squares[i][puzzle[j][k]-1] = true;
			}
		}
	}
	prem = new vector<int>[blanks];
}

//solver function
int Solver::solve()
{
	markup();
	write_to_file();
	return blanks;
}

//functions for easy access to member vars
bool Solver::h(int row, int num_to_check){return horz[row-1][num_to_check-1];}
bool Solver::v(int col, int num_to_check){return vert[col-1][num_to_check-1];}
bool Solver::s(int square, int num_to_check){return squares[square-1][num_to_check-1];}
int Solver::p(int ver, int hor){return puzzle[ver-1][hor-1];}

//creates sets of possible values for each empty box
void Solver::markup()
{
	for(int i=1; i<10; i++)
		for(int j=1; j<10; j++)
			if(p(i,j) <= 0)
				for(int k=1; k<10; k++)
					if((!h(i,k) && !v(j,k)) && !s(to_square(i,j),k))
						prem[p(i,j)*-1].push_back(k); //error: multiple blanks on same rows
}

//convert row,col number to square number
int Solver::to_square(int i, int j)
{
	if(i<4 && j<4) return 1;
	if(i<4 && j<7) return 2;
	if(i<4 && j<10) return 3;
	if(i<7 && j<4) return 4;
	if(i<7 && j<7) return 5;
	if(i<7 && j<10) return 6;
	if(i<10 && j<4) return 7;
	if(i<10 && j<7) return 8;
	if(i<10 && j<10) return 9;
	else return 0;
}

//writes result to file
void Solver::write_to_file()
{
	ofstream outfile; 
	outfile.open("solution.txt");
	for(int i=1; i<10; i++){
		for(int j=1; j<10; j++) outfile << p(i,j) << "\t";
		outfile << "\n" ;
	}

	outfile << "\nBlanks: " << blanks << "\n" ;

	//debugging purposes
	for(int i=0; i<blanks; i++){
		outfile << i << "\t: " ;
		for(int j=0; j<prem[i].size(); j++){
			outfile << prem[i].at(j) << " ";
		}
		outfile << endl;
	}

	outfile.close();
}
