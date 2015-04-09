all: puzzle

puzzle: puzzle.cpp
	g++ -g -Wall -o puzzle puzzle.cpp board.cpp puzzle_move.cpp puzzle_heur.cpp puzzle_solver.cpp

clean:
	-@rm puzzle