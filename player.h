#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include "common.h"
#include "board.h"
using namespace std;

class Player {

public:
    Player(Side side);
    ~Player();
    
    Move *doMove(Move *opponentsMove, int msLeft);
    void setBoard(Board *board1);
    int minimax(bool maxPlayer, Board *b, int depth, Side side);

    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;
    Board *mgBoard;
    Side mySide;
    Side theirSide;
    int bestMoveIdx;

};

#endif
