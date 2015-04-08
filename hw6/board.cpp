#include <iostream>
#include <iomanip>
#include <map>
#include <cmath>
#include <cstdlib>
#include <stdexcept>
#include "board.h"

using namespace std;


Board::Board(int dim, int numInitMoves, int seed )
{
  _size = dim*dim;
  _tiles = new int[_size];
  srand(seed);
  for(int i=0; i < _size; i++){
    _tiles[i] = i;
  }
  int blankLoc = 0;
  while(numInitMoves > 0){
    int r = rand()%4;
    int randNeighbor = -1;
    if(r == 0){
      int n = blankLoc - dim;
      if(n >= 0){
	randNeighbor = n;
      }
    }
    else if(r == 1){
      int w = blankLoc - 1;
      if(blankLoc % dim != 0){
	randNeighbor = w;
      }
    }
    else if(r == 2){
      int s = blankLoc + dim;
      if(s  < _size){
	randNeighbor = s;
      }
    }
    else {
      int e = blankLoc + 1;
      if(blankLoc % dim != dim-1){
	randNeighbor = e;
      }
    }
    if(randNeighbor > -1){
      _tiles[blankLoc] = _tiles[randNeighbor];
      _tiles[randNeighbor] = 0;
      blankLoc = randNeighbor;
      numInitMoves--;
    }
  }
}


Board::Board(const Board& b)
{
  _size = b._size;
  _tiles = new int[_size];
  // Board* newBoard = new Board(*b.dim(), 0, 0);
  for (int i = 0; i < _size; i++)
  {
    _tiles[i] = b._tiles[i];
  }
}

Board::~Board()
{
  delete [] _tiles;
}

void Board::move(int tile)
{
  int side_dim = dim();
  int tr, tc, br, bc;

  // find tile row and column
  int i=-1;
  while(_tiles[++i] != tile);

  tr = i / side_dim; 
  tc = i % side_dim;

  // find blank row and column
  int j=-1;
  while(_tiles[++j] != 0);

  br = j / side_dim;
  bc = j % side_dim;

  if( abs(static_cast<double>(tr-br)) + abs(static_cast<double>(tc-bc)) != 1){
    cout << "Invalid move of tile " << tile << " at ";
    cout << tr << "," << tc << " and blank spot at ";
    cout << br << "," << bc << endl;
    return;
  }
  // Swap tile and blank spot
  _tiles[j] = tile;
  _tiles[i] = 0;
}

// Generate new boards representing all the potential moves of tiles into 
// the current blank tile location. The returned map should have
// the key as the tile moved and the value as a new Board object with the
// configuration reflecting the move of that tile into the blank spot
map<int, Board*> Board::potentialMoves() const
{
  map<int, Board*> moves_;

  int blankLoc;
  for (unsigned int i = 0; i < size(); i++)
  {
    if (_tiles[i] == 0)
    {
      blankLoc = i;
    }
  }

  // cout << "Original board" << endl; 
  // cout << this;

  // for (unsigned int i = 0; i < size(); i++)
  // {
  //   cout << this->_tiles[i] << " ";
  // }
  // cout << endl;

  int blankRow = blankLoc/dim();
  int blankCol = blankLoc%dim();

  // for tile to the left

  int leftTile = _tiles[blankLoc-1];
  int leftRow = blankRow;
  int leftCol = blankCol-1;

  // making sure it doesn't go off the edge
  if (leftCol >= 0)
  {
    Board* leftBoard = new Board(*this);
    leftBoard->move(leftTile);
    // cout << endl << "LEFT BOARD" << endl << *leftBoard;
    moves_.insert(pair <int, Board*>(leftTile, leftBoard));

    // cout << "Copied board" << endl;
    // for (unsigned int i = 0; i < leftBoard->size(); i++)
    // {
    //   cout << leftBoard->_tiles[i] << " ";
    // }
    // cout << endl;
  }

  // for tile above
  
  int upTile = _tiles[blankLoc-dim()];
  int upRow = blankRow-1;
  int upCol = blankCol;

  if (upRow >= 0)
  {
    Board* upBoard = new Board(*this);
    upBoard->move(upTile);
    // cout << endl << "UP BOARD" << endl << *upBoard;
    moves_.insert(pair <int, Board*>(upTile, upBoard));
  }

  // for tile to the right

  int rightTile = _tiles[blankLoc+1];
  int rightRow = blankRow;
  int rightCol = blankCol+1;

  if (rightCol < dim())
  {
    Board* rightBoard = new Board(*this);
    rightBoard->move(rightTile);
    // cout << endl << "RIGHT BOARD" << endl << *rightBoard;
    moves_.insert(pair <int, Board*>(rightTile, rightBoard));
  }

  // for the tile below

  int downTile = _tiles[blankLoc+dim()];
  int downRow = blankRow+1;
  int downCol = blankCol;

  if (downRow < dim())
  {
    Board* downBoard = new Board(*this);
    downBoard->move(downTile);
    // cout << endl << "DOWN BOARD" << endl << *downBoard;
    moves_.insert(pair <int, Board*>(downTile, downBoard));
  }
  
  return moves_;
}


bool Board::solved() const
{
  for (unsigned int i = 0; i < size(); i++)
  {
    if (_tiles[i] != i)
    {
      return false;
    }
  }

  return true;
}


ostream& operator<<(std::ostream &os, const Board &b)
{
  b.printRowBanner(os);
  for (int i = 0; i < b.dim(); i++)
  {
    for (int j = 0; j < b.dim(); j++)
    {
      if (b._tiles[(i*b.dim())+j] == 0)
      {
        os << "|" << setw(2) << " ";
      }
      else
      {
        os << "|" << setw(2) << b._tiles[(i*b.dim())+j];
      }
    }
    os << "|" << "\n";
    b.printRowBanner(os);
  }
}

bool Board::operator<(const Board& rhs) const
{
  // cout << "In less than operator" << endl;
  for (unsigned int i = 0; i < size(); i++)
  {
    if (this->_tiles[i] < rhs._tiles[i])
    {
      return true;
    }
  }

  return false;
}



const int& Board::operator[](int loc) const 
{ 
  return _tiles[loc]; 
}

int Board::size() const 
{ 
  return _size; 
}

int Board::dim() const
{
  return static_cast<int>(sqrt(_size));
}

void Board::printRowBanner(ostream& os) const
{
  int side_dim = dim();
  if(side_dim == 0) return;
  os << '+';
  for(int i=0; i < side_dim; i++){
    os << "--+";
  }
  os << endl;
}
