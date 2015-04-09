#include <iostream>
#include <cmath>
#include "puzzle_heur.h"

using namespace std;

PuzzleManhattanHeuristic::PuzzleManhattanHeuristic()
{

}

int PuzzleManhattanHeuristic::compute(const Board& b)
{
	int score = 0;

	for (int i = 0; i < b.size(); i++)
	{
		if (b[i] == 0)
		{
			continue;
		}
		int val = b[i];
		int valRow = i / b.dim();
		int valCol = i % b.dim();
		int correctRow = val / b.dim();
		int correctCol = val % b.dim();
		int rowDif = abs(valRow-correctRow);
		int colDif = abs(valCol-correctCol);
		int dif = rowDif+colDif;
		score += dif;
	}

	return score;
}

PuzzleOutOfPlaceHeuristic::PuzzleOutOfPlaceHeuristic()
{

}

int PuzzleOutOfPlaceHeuristic::compute(const Board& b)
{
	int score = 0;

	for (int i = 1; i < b.size(); i++)
	{
		if (b[i] != i)
		{
			score++;
		}
	}

	return score;
}

PuzzleBFSHeuristic::PuzzleBFSHeuristic()
{

}

int PuzzleBFSHeuristic::compute(const Board& b)
{
	return 0;
}