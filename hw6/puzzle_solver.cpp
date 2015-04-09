#include <iostream>
#include <iterator>
#include <deque>
#include "puzzle_solver.h"

using namespace std;

PuzzleSolver::PuzzleSolver(const Board &b, PuzzleHeuristic* ph) : _b(b)
{
	_ph = ph;
	_expansions = 0;
}

PuzzleSolver::~PuzzleSolver()
{

}

void PuzzleSolver::run()
{
	
	PuzzleMoveScoreComp comp;
	PuzzleMove* solved;
	vector<Board*> deletions_;

	Heap<PuzzleMove*, PuzzleMoveScoreComp> openList_(2, comp);
	PuzzleMoveSet closedList_;

	deque<int> sol_;


	PuzzleMove* move = new PuzzleMove(&_b);
	move->h = _ph->compute(*(move->b));

	openList_.push(move);
	closedList_.insert(move);

	// closedList_.insert(move);

	while (!openList_.empty())
	{
		PuzzleMove* m = openList_.top();
		closedList_.insert(m);

		if (m->b->solved())
		{
			solved = m;

			break;
		}

		openList_.pop();

		map<int, Board*> moves = m->b->potentialMoves();
		map<int, Board*>::iterator it;
		PuzzleMoveSet::iterator itt;

		for (it = moves.begin(); it != moves.end(); ++it)
		{
			Board* newB = new Board(*(it->second));
			deletions_.push_back(newB);
			bool unique = true;
		
			PuzzleMove* nextMove = new PuzzleMove(it->first, newB, m);
			nextMove->h = _ph->compute(*(nextMove->b));
			
			for (itt = closedList_.begin(); itt != closedList_.end(); ++itt)
			{
				if (! (*(nextMove->b) < (*((*itt)->b))))
				{
					unique = false;
				}
			}

			if (unique == true)
			{
				openList_.push(nextMove);
				closedList_.insert(nextMove);
				// cout << "Pushed to open list" << endl; // << *(nextMove->b) << endl;
				_expansions++;
			}

			else
			{
				delete nextMove;
			}

			delete it->second;
		}
	}

	while (solved->b < &_b)
	{
		// cout << "Adding to deque" << endl;
		_solution.push_front(solved->tileMove);
		// delete solved;
		solved = solved->prev;
	}

	PuzzleMoveSet::iterator it;
	for (it = closedList_.begin(); it != closedList_.end(); ++it)
	{
		delete *it;
	}

	for (unsigned int i = 0; i < deletions_.size(); i++)
	{
		delete deletions_[i];
	}

	deletions_.clear();

}

std::deque<int> PuzzleSolver::getSolution()
{
	return _solution;
}

int PuzzleSolver::getNumExpansions()
{
	return _expansions;
}