/*
  Author: Ahsan Zaman
  Email: ahsanzam@usc.edu
*/
#include <fstream>
#include "solver.h"

int main(int argc, char* argv[]){
	if(argc < 2) return 1;
	ifstream infile(argv[1]);
	if( infile.fail() ) return 1;
	Solver s_solve(&infile);
	infile.close();
	return s_solve.solve();
}
