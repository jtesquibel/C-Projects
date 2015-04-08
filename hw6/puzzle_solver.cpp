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
	// delete &_b;
}

void PuzzleSolver::run()
{
	// cout << "In run" << endl;
	PuzzleMoveScoreComp comp;
	PuzzleMove* solved;

	Heap<PuzzleMove*, PuzzleMoveScoreComp> openList_(2, comp);
	PuzzleMoveSet closedList_;

	deque<int> sol_;


	PuzzleMove* move = new PuzzleMove(&_b);
	move->h = _ph->compute(*(move->b));

	openList_.push(move);
	// _expansions++;
	closedList_.insert(move);

	// closedList_.insert(move);

	while (!openList_.empty())
	{
		// cout << "Yo" << endl << endl;
		// cout << "open list size = " << openList_.size() << endl;

		// PuzzleMove* m = new PuzzleMove(openList_.top()->b);
		PuzzleMove* m = openList_.top();
		// cout << "Top Board Popped:" << endl << *(m->b);
		// openList_.pop();
		closedList_.insert(m);
		// cout << "Added this ^ board to closed list" << endl;
		// openList_.pop();

		if (m->b->solved())
		{
			// cout << "Solved" << endl;
			solved = m;
			// cout << "open size = " << openList_.size() << endl;
			// break;
			// while (*(m->b) < _b)
			// {
			// 	// PuzzleMove* curr = new PuzzleMove(m->b);
			// 	sol_.push_front(m->tileMove);
			// 	m = m->prev;
			// }

			break;
		}

		openList_.pop();
		// _expansions--;

		map<int, Board*> moves = m->b->potentialMoves();
		map<int, Board*>::iterator it;
		PuzzleMoveSet::iterator itt;

		// cout << "potential moves size = " << moves.size() << endl;
		// cout << "closed list size = " << closedList_.size() << endl;
		
		// bool unique = true;
		for (it = moves.begin(); it != moves.end(); ++it)
		{
			bool unique = true;
			// cout << "In map[]" << endl;
			PuzzleMove* nextMove = new PuzzleMove(it->first, it->second, m);
			nextMove->h = _ph->compute(*(nextMove->b));
			// nextMove->f = nextMove->h + nextMove->g;
			for (itt = closedList_.begin(); itt != closedList_.end(); ++itt)
			{
				// if (closedList_.count(nextMove) == 0)
				// if (it->second == (*closedList_.find(nextMove))->b)
				// cout << "Here" << endl;
				if (! (*(nextMove->b) < (*((*itt)->b))))
				{
					unique = false;
					// delete nextMove;
					// break;
					// openList_.push(nextMove);
					// closedList_.insert(nextMove);
					// cout << "Pushed to open list" << endl; // << *(nextMove->b) << endl;
					// _expansions++;
				}
			}

			// cout << "Later" << endl;

			if (unique == true)
			{
				// cout << "Unique was true" << endl;
				openList_.push(nextMove);
				closedList_.insert(nextMove);
				// cout << "Pushed to open list" << endl; // << *(nextMove->b) << endl;
				_expansions++;
			}

			// else
			// {
				// delete nextMove;
			// }

			// else
			// {
			// 	PuzzleMoveSet::iterator itt = closedList_.find(nextMove);
			// 	if (nextMove->f < (*itt)->f)
			// 	{
			// 		(*itt)->f = nextMove->f;
			// 		// vector<Board*> h1 = openList_.getHeap();
			// 		// Heap<PuzzleMove*, PuzzleMoveScoreComp> newList_(4, comp);
			// 		for (unsigned int i = 0; i < openList_.size(); i++)
			// 		{
			// 			// newList_
			// 		}


			// 	}
				



			// }
			// for (itt = closedList_.begin(); itt != closedList_.end(); ++itt)
			// {
			// 	cout << "In set iterator" << endl;
			// 	// int hVal = nextMove->g + _ph->compute(*(nextMove->b));
			// 	if (!(nextMove->b < (*itt)->b))
			// 	{
			// 		unique = false;
			// 		cout << "Already in closed list" << endl;
			// 	}
			// }
			// if (unique == true)
			// {
			// 	openList_.push(nextMove);
			// 	cout << "Pushed to open list" << endl; // << *(nextMove->b) << endl;
			// 	_expansions++;
			// }
		}

	}

	while (solved->b < &_b)
	{
		// cout << "Adding to deque" << endl;
		_solution.push_front(solved->tileMove);
		// delete solved;
		solved = solved->prev;
	}

	// PuzzleMove* del;
	// while (!(openList_.empty()))
	// {
	// 	// del = openList_.top();
	// 	// delete del;
	// }

	// delete move;
	// delete openList_;


}

std::deque<int> PuzzleSolver::getSolution()
{
	return _solution;
}

int PuzzleSolver::getNumExpansions()
{
	return _expansions;
}