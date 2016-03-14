#include "board.h"
#include <stdlib.h>
#include <iostream>
using namespace std;
/*
 * Make a standard 8x8 othello board and initialize it to the standard setup.
 */
Board::Board() {
    taken.set(3 + 8 * 3);
    taken.set(3 + 8 * 4);
    taken.set(4 + 8 * 3);
    taken.set(4 + 8 * 4);
    black.set(4 + 8 * 3);
    black.set(3 + 8 * 4);

    vector <Move*> possibleMoves;
   
}

/*
 * Destructor for the board.
 */
Board::~Board() {
}

/*
 * Returns a copy of this board.
 */
Board *Board::copy() {
    Board *newBoard = new Board();
    newBoard->black = black;
    newBoard->taken = taken;
    return newBoard;
}

bool Board::occupied(int x, int y) {
    return taken[x + 8*y];
}

bool Board::get(Side side, int x, int y) {
    return occupied(x, y) && (black[x + 8*y] == (side == BLACK));
}

void Board::set(Side side, int x, int y) {
    taken.set(x + 8*y);
    black.set(x + 8*y, side == BLACK);
}

bool Board::onBoard(int x, int y) {
    return(0 <= x && x < 8 && 0 <= y && y < 8);
}

 
/*
 * Returns true if the game is finished; false otherwise. The game is finished 
 * if neither side has a legal move.
 */
bool Board::isDone() {
    return !(hasMoves(BLACK) || hasMoves(WHITE));
}

/*
 * Returns true if there are legal moves for the given side.
 */
bool Board::hasMoves(Side side) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            Move move(i, j);
            if (checkMove(&move, side)) return true;
        }
    }
    return false;
}



/*
 * Returns true if a move is legal for the given side; false otherwise.
 */
bool Board::checkMove(Move *m, Side side) {
    // Passing is only legal if you have no moves.
    if (m == NULL) return !hasMoves(side);

    int X = m->getX();
    int Y = m->getY();

    // Make sure the square hasn't already been taken.
    if (occupied(X, Y)) return false;

    Side other = (side == BLACK) ? WHITE : BLACK;
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (dy == 0 && dx == 0) continue;

            // Is there a capture in that direction?
            int x = X + dx;
            int y = Y + dy;
            if (onBoard(x, y) && get(other, x, y)) {
                do {
                    x += dx;
                    y += dy;
                } while (onBoard(x, y) && get(other, x, y));

                if (onBoard(x, y) && get(side, x, y)) return true;
            }
        }
    }
    return false;
}

/*
 * 
 */

vector <Move*> Board::returnPossibleMoves(Side side) {
	
	possibleMoves.erase(possibleMoves.begin(), possibleMoves.begin() + possibleMoves.size());
	
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            Move *move = new Move(i, j);
            if (checkMove(move, side)) {
            	possibleMoves.push_back(move);            	
            }
        }
    }
    return possibleMoves;
}

/*
 * Modifies the board to reflect the specified move.
 */
void Board::doMove(Move *m, Side side) {
    // A NULL move means pass.
    if (m == NULL) return;

    // Ignore if move is invalid.
    if (!checkMove(m, side)) return;

    int X = m->getX();
    int Y = m->getY();
    Side other = (side == BLACK) ? WHITE : BLACK;
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (dy == 0 && dx == 0) continue;

            int x = X;
            int y = Y;
            do {
                x += dx;
                y += dy;
            } while (onBoard(x, y) && get(other, x, y));

            if (onBoard(x, y) && get(side, x, y)) {
                x = X;
                y = Y;
                x += dx;
                y += dy;
                while (onBoard(x, y) && get(other, x, y)) {
                    set(side, x, y);
                    x += dx;
                    y += dy;
                }
            }
        }
    }
    set(side, X, Y);
}

/*
 * Current count of given side's stones.
 */
int Board::count(Side side) {
    return (side == BLACK) ? countBlack() : countWhite();
}

/*
 * Current count of black stones.
 */
int Board::countBlack() {
    return black.count();
}

/*
 * Current count of white stones.
 */
int Board::countWhite() {
    return taken.count() - black.count();
}

/*
 * Sets the board state given an 8x8 char array where 'w' indicates a white
 * piece and 'b' indicates a black piece. Mainly for testing purposes.
 */
void Board::setBoard(char data[]) {
    taken.reset();
    black.reset();
    for (int i = 0; i < 64; i++) {
        if (data[i] == 'b') {
            taken.set(i);
            black.set(i);
        } if (data[i] == 'w') {
            taken.set(i);
        }
    }
}

int Board::calculateScoreOfBoard (Side mine, Side theirs)
{
int returnScore = count(mine) - count (theirs);
//cerr << get(mine, 1, 1) << endl;
// Move edges [] = {Move(0,2), Move(0,3), Move(0,4), Move(0,5), Move(2,0), Move(3,0), Move(4,0), Move(5,0), Move(7,2),
// Move(7,3), Move(7,4), Move(7,5), Move(2,7), Move(3,7), Move(4,7), Move(5,7)};
// Move bad [] = {Move(1,0), Move(0,1), Move(0,6), Move(1,7), Move(6,0), Move(7,1), Move(6,7), Move(7,6)};
// Move worst [] = {Move(1,1), Move(6,1), Move(1,6), Move(6,6)};
/******************************** VERTICALLY ADJACENT TO CORNER ******************************/
if (get(mine, 1, 1))
{
returnScore -= 3;
}
else if (get(theirs, 1, 1))
{
returnScore += 3;
}
if (get(mine, 6, 1))
{
returnScore -= 3;
}
else if (get(theirs, 6, 1))
{
returnScore += 3;
}
if (get(mine, 6, 6))
{
returnScore -= 3;
}
else if (get(theirs, 6, 6))
{
returnScore += 3;
}
if (get(mine, 1, 6))
{
returnScore -= 3;
}
else if (get(theirs, 1, 6))
{
returnScore += 3;
}
/******************************** ADJACENT TO CORNER ******************************/
if (get(mine, 1, 0))
{
returnScore -= 1;
}
else if (get(theirs, 1, 0))
{
returnScore += 1;
}
if (get(mine, 0, 1))
{
returnScore -= 1;
}
else if (get(theirs, 0, 1))
{
returnScore += 1;
}
if (get(mine, 0, 6))
{
returnScore -= 1;
}
else if (get(theirs, 0, 6))
{
returnScore += 1;
}
if (get(mine, 6, 0))
{
returnScore -= 1;
}
else if (get(theirs, 6, 0))
{
returnScore += 1;
}
if (get(mine, 1, 7))
{
returnScore -= 1;
}
else if (get(theirs, 1, 7))
{
returnScore += 1;
}
if (get(mine, 7, 1))
{
returnScore -= 1;
}
else if (get(theirs, 7, 1))
{
returnScore += 1;
}
if (get(mine, 6, 7))
{
returnScore -= 1;
}
else if (get(theirs, 6, 7))
{
returnScore += 1;
}
if (get(mine, 7, 6))
{
returnScore -= 1;
}
else if (get(theirs, 7, 6))
{
returnScore += 1;
}
/******************************** EDGES **************************/
if (get(mine, 0, 2))
{
returnScore += 3;
}
else if (get(theirs, 0, 2))
{
returnScore -= 3;
}
if (get(mine, 0, 3))
{
returnScore += 3;
}
else if (get(theirs, 0, 3))
{
returnScore -= 3;
}
if (get(mine, 0, 4))
{
returnScore += 3;
}
else if (get(theirs, 0, 4))
{
returnScore -= 3;
}
if (get(mine, 0, 5))
{
returnScore += 3;
}
else if (get(theirs, 0, 5))
{
returnScore -= 3;
}
if (get(mine, 2, 0))
{
returnScore += 3;
}
else if (get(theirs, 2, 0))
{
returnScore -= 3;
}
if (get(mine, 3, 0))
{
returnScore += 3;
}
else if (get(theirs, 3, 0))
{
returnScore -= 3;
}
if (get(mine, 4, 0))
{
returnScore += 3;
}
else if (get(theirs, 4, 0))
{
returnScore -= 3;
}
if (get(mine, 5, 0))
{
returnScore += 3;
}
else if (get(theirs, 5, 0))
{
returnScore -= 3;
}
if (get(mine, 7, 2))
{
returnScore += 3;
}
else if (get(theirs, 7, 2))
{
returnScore -= 3;
}
if (get(mine, 7, 3))
{
returnScore += 3;
}
else if (get(theirs, 7, 3))
{
returnScore -= 3;
}
if (get(mine, 7, 4))
{
returnScore += 3;
}
else if (get(theirs, 7, 4))
{
returnScore -= 3;
}
if (get(mine, 7, 5))
{
returnScore += 3;
}
else if (get(theirs, 7, 5))
{
returnScore -= 3;
}
if (get(mine, 2, 7))
{
returnScore += 3;
}
else if (get(theirs, 2, 7))
{
returnScore -= 3;
}
if (get(mine, 3, 7))
{
returnScore += 3;
}
else if (get(theirs, 3, 7))
{
returnScore -= 3;
}
if (get(mine, 4, 7))
{
returnScore += 3;
}
else if (get(theirs, 4, 7))
{
returnScore -= 3;
}
if (get(mine, 5, 7))
{
returnScore += 3;
}
else if (get(theirs, 5, 7))
{
returnScore -= 3;
}
/******************************** CORNERS ************************/
if (get(mine, 0, 0))
{
returnScore += 10;
}
else if (get(theirs,0,0))
{
returnScore -= 10;
}
if (get(mine, 0, 7))
{
returnScore += 10;
}
else if (get(theirs, 0, 7))
{
returnScore -= 10;
}
if (get(mine, 7, 0))
{
returnScore += 10;
}
else if (get(theirs, 7, 0))
{
returnScore -= 10;
}
if (get(mine, 7, 7))
{
returnScore += 10;
}
else if (get(theirs, 7 , 7))
{
returnScore -= 10;
}
return returnScore;
}
