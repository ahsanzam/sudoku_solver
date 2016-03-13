#Makefile for Sudoku Solver

all: clean sudoku_solver 

sudoku_solver: solver.o
	g++ -g -Wall solver.o sudoku_solver.cpp -o sudoku_solver

solver.o:
	g++ -g -Wall -c solver.cpp -o solver.o

run: 
	./sudoku_solver sudoku.txt

clean: 
	rm solver.o sudoku_solver

