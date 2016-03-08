#include "player.h"
using namespace std;
#include <vector>
#include <stdlib.h>
#include <algorithm>

// Steven Brotz initial change

/* -----------------------------
ANDREW WANG --- second teammate change 
--------------------------------
*/


/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish 
 * within 30 seconds.
 */
Player::Player(Side side) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = false;
    mgBoard = new Board();
    mySide = side;
    if (mySide == BLACK){
    	theirSide = WHITE;
    }
    else{
    	theirSide = BLACK;
    }





    /* 
     * TODO: Do any initialization you need to do here (setting up the board,
     * precalculating things, etc.) However, remember that you will only have
     * 30 seconds.
     */
}

/*
 * Destructor for the player.
 */
Player::~Player() {

	delete mgBoard;
}

/*
 * Compute the next move given the opponent's last move. Your AI is
 * expected to keep track of the board on its own. If this is the first move,
 * or if the opponent passed on the last move, then opponentsMove will be NULL.
 *
 * msLeft represents the time your AI has left for the total game, in
 * milliseconds. doMove() must take no longer than msLeft, or your AI will
 * be disqualified! An msLeft value of -1 indicates no time limit.
 *
 * The move returned must be legal; if there are no valid moves for your side,
 * return NULL.
 */

void Player::setBoard (Board *board1)
{
	mgBoard = board1;
}

int Player::calculateScoreOfBoard (Board *board1)
{
	int returnScore = 0;
	if (board1->occupiedBySide(mySide, 0, 0))
	{
		returnScore += 3;
	}

	else if (board1->occupiedBySide(theirSide,0,0))
	{
		returnScore -= 3;
	}

	else {};

	if (board1->occupiedBySide(mySide, 0, 7))
	{
		returnScore += 3;
	}

	else if (board1->occupiedBySide(theirSide, 0, 7))
	{
		returnScore -= 3;
	}
	else {};


	if (board1->occupiedBySide(mySide, -7, 0))
	{
		returnScore += 3;
	}

	else if (board1 -> occupiedBySide(theirSide, -7, 0))
	{
		returnScore -= 3;
	}

	else {};

	if (board1->occupiedBySide(mySide, 7, 7))
	{
		returnScore += 3;
	}

	else if (board1->occupiedBySide(theirSide, 7 , 7))
	{
		returnScore -=3;
	}

	else {};

	return returnScore;
}

Move *Player::doMove(Move *opponentsMove, int msLeft) {

    /* 
     * TODO: Implement how moves your AI should play here. You should first
     * process the opponent's opponents move before calculating your own move
     */ 

    // Move corners[] = {Move(0,0), Move(0,7), Move(-7,0), Move(7,7)};
    // Move edges [] = {Move(0,2), Move(0,3), Move(0,4), Move(0,5), Move(2,0), Move(3,0), Move(4,0), Move(5,0), Move(7,2), 
    // 	Move(7,3), Move(7,4), Move(7,5), Move(2,7), Move(3,7), Move(4,7), Move(5,7)};
    // Move bad [] = {Move(1,0), Move(0,1), Move(0,0), Move(1,7), Move(6,0), Move(7,1), Move(6,7), Move(7,6)};
    // Move worst [] = {Move(1,1), Move(6,1), Move(1,6), Move(6,6)};

    // vector <int> tileValues;
    // tileValues.erase(tileValues.begin(), tileValues.begin() + tileValues.size());

    if (opponentsMove != NULL){
     	mgBoard->doMove (opponentsMove, theirSide);
    }

    vector <int> points; 
    points.erase(points.begin(), points.begin() + points.size());

    if (mgBoard->hasMoves (mySide)){
    	vector <Move*> possibleMoves1 = mgBoard -> returnPossibleMoves(mySide);

    	vector <Move*> possibleOpponentMoves;
    	for (unsigned int i = 0; i < possibleMoves1.size(); i++)
    	{
    		//cerr << possibleMoves1[i]->getX() << ", " << possibleMoves1[i]-> getY() << endl;
    		Board *testBoard = mgBoard -> copy();
    		testBoard->doMove(possibleMoves1[i], mySide);
    		possibleOpponentMoves.erase(possibleOpponentMoves.begin(), possibleOpponentMoves.begin() + possibleOpponentMoves.size());
    		possibleOpponentMoves = testBoard -> returnPossibleMoves(theirSide);
 			int min = 999;
    		
    		for (unsigned int j = 0 ; j < possibleOpponentMoves.size(); j++)
    		{		

    			Board *testBoard2 = testBoard -> copy();
    			testBoard2->doMove(possibleOpponentMoves[j], theirSide);
    			int difference = testBoard2->count(mySide) - testBoard2->count(theirSide);

    			//int difference = calculateScoreOfBoard(testBoard2);
    			if (difference < min){
    				min = difference;
    			}

    			delete testBoard2;
    		}
    		points.push_back(min);
    		delete testBoard;
    	}


    	unsigned int maxIndex = 0;
    	if (points.size() > 0)
    	{	
    		int max = -999;
    		for (unsigned int i = 0 ; i < points.size(); i++)
    		{
    			if (points[i] > max){
    				max = points[i];
    				maxIndex = i;
    			}
    		}
    	}

    	Move *toReturn = possibleMoves1[maxIndex];

    	mgBoard->doMove(toReturn, mySide);

    	for (unsigned int i = 0 ; i < possibleMoves1.size(); i++)
    	{
    		if (i != maxIndex){
    			delete possibleMoves1[i];
    		}
    	}

    	return toReturn;
    }

    return NULL;
    	
}


 