#include <iostream>
#include <cstdlib>
#include <deque>
#include "board.h"
#include "puzzle_heur.h"
#include "puzzle_solver.h"

int main(int argc, char *argv[])
{
  if(argc < 5){
    cerr << "Usage: ./puzzle size initMoves seed heur" << endl;
    return 1;
  }

  int dim = atoi(argv[1]);
  int moves = atoi(argv[2]);
  int seed = atoi(argv[3]);
  int method = atoi(argv[4]);

  Board b(dim, moves, seed);

  cout << "ORIGINAL BOARD" << endl << endl << b;


  int move;

  do 
  {
  	cout << "Enter the tile number to move, 0 to quit, or -1 for a cheat: ";
  	cin >> move;
  	if (move != -1 && move > 0)
  	{
  		b.move(move);
  		cout << b;
  	}
  	else if (move == -1)
  	{
  		deque<int> cheat;
  		if (method == 0)
  		{
  			PuzzleHeuristic* h = new PuzzleBFSHeuristic();
  			PuzzleSolver ps(b, h);
		  	ps.run();
		  	cheat = ps.getSolution();
		  	delete h;

		  	cout << endl << "Try this sequence: ";
		  	for (unsigned int i = 0; i < cheat.size(); i++)
		  	{
		  		cout << cheat[i] << " ";
		  	}
		  	cout << endl << "Num exmpansions = " << ps.getNumExpansions() << endl << endl;
  		}
  		if (method == 1)
	    {
		  PuzzleHeuristic* h = new PuzzleOutOfPlaceHeuristic();
		  PuzzleSolver ps(b, h);
		  ps.run();
		  cheat = ps.getSolution();
		  delete h;

		  cout << endl << "Try this sequence: ";
		  for (unsigned int i = 0; i < cheat.size(); i++)
		  {
		  	cout << cheat[i] << " ";
		  }
		  cout << endl << "Num exmpansions = " << ps.getNumExpansions() << endl << endl;
	    }
	    if (method == 2)
	    {
	   	  PuzzleHeuristic* h = new PuzzleManhattanHeuristic();
	   	  PuzzleSolver ps = PuzzleSolver(b, h);
	   	  ps.run();
	   	  cheat = ps.getSolution();
	   	  delete h;

	   	  cout << endl << "Try this sequence: ";
		  for (unsigned int i = 0; i < cheat.size(); i++)
		  {
		  	cout << cheat[i] << " ";
		  }
		  cout << endl << "Num exmpansions = " << ps.getNumExpansions() << endl << endl;
	    }
  		// PuzzleSolver 
  	}
  	else if (move == 0)
  	{
  		return 0;
  	}
  }
  while (!b.solved());

  if (b.solved())
  {
  	cout << "Congrats! You win" << endl;
  }

  return 0;
}
