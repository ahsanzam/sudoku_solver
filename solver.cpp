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
	prem = new vector<vector<int> >;

	outfile.open("solution.txt");
}

Solver::~Solver(){
	outfile.close();
}
//solver function
int Solver::solve()
{
	bool only_choice = true;
	//write_to_file();
	//int x=1;
	//first solve for all the boxes that have only one possibility
	while(only_choice){
		markup();
		int filled_blanks = 0;
		for(int i=0; i<prem->size(); i++){
			if( prem->at(i).size() == 1){
				bool found = false;
				for(int j=1; (!found && j<10); j++){
					for(int k=1; (!found && k<10); k++){
						if( p(j,k) == i*-1 ){
							puzzle[j-1][k-1] = prem->at(i).at(0);
							horz[j-1][p(j,k)-1] = true;
							vert[k-1][p(j,k)-1] = true;
							squares[to_square(j,k)-1][p(j,k)-1] = true;
							filled_blanks++;
							found = true; 
						}
					}
				}
			}
		}
		blanks -= filled_blanks;
		cout << "Blanks:" << blanks << endl;
		if(filled_blanks == 0) only_choice = false;
		else{ 
			label_blanks();
			while(prem->size() != 0) prem->pop_back();
		}
	}
	//then solve using elimination 
	//...somehow...

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
	int index = 0;
	for(int i=1; i<10; i++)
		for(int j=1; j<10; j++)
			if( p(i,j) <= 0 ){
				vector<int> poss;
				prem->push_back(poss);
				for(int k=1; k<10; k++)
					if((!h(i,k) && !v(j,k)) && !s(to_square(i,j),k))
						prem->at(index).push_back(k); 
				index++;
			}
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

//labels all the blanks starting from zero
void Solver::label_blanks(){
	int blank_num = 0;
	for(int i=1; i<10; i++){
		for(int j=1; j<10; j++){
			if( p(i,j) <= 0 ){
				puzzle[i-1][j-1] = blank_num;
				blank_num--;
			}
		}
	}
}

//writes result to file
void Solver::write_to_file()
{

	for(int i=1; i<10; i++){
		for(int j=1; j<10; j++) outfile << p(i,j) << "\t";
		outfile << "\n" ;
	}

	outfile << "\nBlanks: " << blanks << "\n" ;
/*
	//debugging purposes
	for(int i=0; i<prem->size(); i++){
		outfile << i << "\t: " ;
		for(int j=0; j<prem->at(i).size(); j++){
			outfile << prem->at(i).at(j) << " ";
		}
		outfile << endl;
	}*/

}