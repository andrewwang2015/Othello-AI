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
    bestMoveIdx = 0;




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

void Player::setBoard(Board *board1)
{
	mgBoard = board1;
}
/*
int Player::minimax(bool maxPlayer, Board *b, int depth)
{	
	if (depth == 0) {
		return b->count(theirSide) - b->count(mySide);
	}
	
	vector <Move*> possibleMoves;
	
	if (maxPlayer == true) {
		possibleMoves = b->returnPossibleMoves(mySide);
		int best = 1000000;
		int score;
		for (unsigned int i = 0; i < possibleMoves.size(); i++) {
			Board *newBoard = b->copy();
			newBoard->doMove(possibleMoves[i], mySide);
			score = minimax(false, newBoard, depth - 1);
			if (score < best) {
				best = score;
				bestMoveIdx = i;
			}
		}
		return best;
	} else {
		possibleMoves = b->returnPossibleMoves(theirSide);
		int best = -1000000;
		int score;
		for (unsigned int i = 0; i < possibleMoves.size(); i++) {
			Board *newBoard = b->copy();
			newBoard->doMove(possibleMoves[i], theirSide);
			score = minimax(true, newBoard, depth - 1);
			if (score > best) {
				best = score;
			}
		}
		return best;
	}
}*/

int Player::minimax(bool maxPlayer, Board *b, int depth, Side side)
{
	Side other = (side == mySide) ? theirSide : mySide;
	
	if (depth == 0) {
		return b->calculateScoreOfBoard(other, side);
	}
	
	vector<Move*> possibleMoves;
	
	if (maxPlayer) {
		int best = 1000000;
		int score;
		possibleMoves = b->returnPossibleMoves(side);
		for (unsigned int i = 0; i < possibleMoves.size(); i++) {
			Board *newBoard = b->copy();
			newBoard->doMove(possibleMoves[i], side);
			score = minimax(false, newBoard, depth - 1, other);
			if (score < best) {
				best = score;
			}
		}
		return best;
	} else {
		int best = -1000000;
		int score;
		possibleMoves = b->returnPossibleMoves(side);
		for (unsigned int i = 0; i < possibleMoves.size(); i++) {
			Board *newBoard = b->copy();
			newBoard->doMove(possibleMoves[i], side);
			score = minimax(true, newBoard, depth - 1, other);
			if (score > best) {
				best = score;
			}
		}
		return best;
	}
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
Move *Player::doMove(Move *opponentsMove, int msLeft) {
    /* 
     * TODO: Implement how moves your AI should play here. You should first
     * process the opponent's opponents move before calculating your own move
     */ 
    
    /*
    Move corners[] = {Move(0,0), Move(0,7), Move(-7,0), Move(7,7)};
    Move edges[] = {Move(0,2), Move(0,3), Move(0,4), Move(0,5), Move(2,0), Move(3,0), Move(4,0), Move(5,0), Move(7,2), 
    	Move(7,3), Move(7,4), Move(7,5), Move(2,7), Move(3,7), Move(4,7), Move(5,7)};
    Move bad[] = {Move(1,0), Move(0,1), Move(0,0), Move(1,7), Move(6,0), Move(7,1), Move(6,7), Move(7,6)};
    Move worst[] = {Move(1,1), Move(6,1), Move(1,6), Move(6,6)};

    vector <int> tileValues;
    tileValues.erase(tileValues.begin(), tileValues.begin() + tileValues.size());
    if (opponentsMove != NULL) {
     	mgBoard->doMove (opponentsMove, theirSide);

    }

    if (mgBoard->hasMoves (mySide)){
    	vector <Move*> possibleMoves1 = mgBoard->returnPossibleMoves(mySide);

    	for (unsigned int i = 0 ; i < possibleMoves1.size(); i++){
    		int flag = 0;
    		Move *currentMove = possibleMoves1[i];
    		for (unsigned int i = 0; i < 4; i++){
    			if (corners[i].getX() == currentMove->getX() && corners[i].getY() == currentMove->getY()){
    				tileValues.push_back(3);
    				flag = 1;
    				break;
    			}
    		}

    		if (flag == 0){
        		for (unsigned int i = 0; i < 16; i++){
	    			if (edges[i].getX() == currentMove->getX() && edges[i].getY() == currentMove->getY()){
	    				tileValues.push_back(1);
	    				flag = 1;
	    				break;
	    			}
    			}			
    		}

    		if (flag == 0){
        		for (unsigned int i = 0; i < 8; i++){
	    			if (bad[i].getX() == currentMove->getX() && bad[i].getY() == currentMove->getY()){
	    				tileValues.push_back(-1);
	    				flag = 1;
	    				break;
	    			}
    			}			
    		}

    		if (flag == 0){
        		for (unsigned int i = 0; i < 4; i++){
	    			if (worst[i].getX() == currentMove->getX() && worst[i].getY() == currentMove->getY()){
	    				tileValues.push_back(-3);
	    				flag = 1;
	    				break;
	    			}
    			}			
    		}

			if (flag == 0){
				tileValues.push_back(0);
			}
    		
    	}

    	int max = -999;
    	unsigned int index = 0;
    	for (unsigned int i = 0 ; i < tileValues.size(); i++){
    		if (tileValues[i] > max){
    			max = tileValues[i];
    			index = i;
    		}
    	}

    	//unsigned int randomIndex = rand() % possibleMoves1.size();

    	Move *toReturn = possibleMoves1[index];

    	mgBoard->doMove(toReturn, mySide);

    	for (unsigned int i = 0 ; i < possibleMoves1.size(); i++)
    	{
    		if (i != index){
    			delete possibleMoves1[i];
    		}
    	}

    	return toReturn;
    }
    */    
    if (opponentsMove != NULL) {
		mgBoard->doMove(opponentsMove, theirSide);
    }
    
    if (mgBoard->hasMoves(mySide)) {
		vector <Move*> possibleMoves1 = mgBoard->returnPossibleMoves(mySide);
		
		int best = 10000000;
		int score;
		for (unsigned int i = 0; i < possibleMoves1.size(); i++) {
			Board *newBoard = mgBoard->copy();
			newBoard->doMove(possibleMoves1[i], mySide);
			int score = minimax(false, newBoard, 1, theirSide);
			if (score < best) {
				best = score;
				bestMoveIdx = i;
			}
		}
		mgBoard->doMove(possibleMoves1[bestMoveIdx], mySide);
		return possibleMoves1[bestMoveIdx];
	}

    return NULL;
    	
}
	
	
	
	
	
