#include "puzzle_move.h"

PuzzleMove::PuzzleMove(Board* board)
{
	b = board;
	g = 0;
	prev = NULL;
}

PuzzleMove::~PuzzleMove()
{
	delete b;
	// delete prev;
}

PuzzleMove::PuzzleMove(int tile, Board* board, PuzzleMove *parent)
{
	tileMove = tile;
    b = board;
    prev = parent;
    g = (prev->g)+1;
}