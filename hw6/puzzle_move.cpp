#include "puzzle_move.h"

PuzzleMove::PuzzleMove(Board* board)
{
	b = board;
	g = 0;
}

PuzzleMove::~PuzzleMove()
{

}

PuzzleMove::PuzzleMove(int tile, Board* board, PuzzleMove *parent)
{
	tileMove = tile;
    b = board;
    prev = parent;
    g = (prev->g)+1;
}