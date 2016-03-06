#ifndef __BOARD_H__
#define __BOARD_H__

#include <bitset>
#include "common.h"
using namespace std;
#include <vector>

class Board {
   
private:
    bitset<64> black;
    bitset<64> taken;    
    vector <Move*> possibleMoves1;
       
    bool occupied(int x, int y);
    bool get(Side side, int x, int y);
    void set(Side side, int x, int y);
    bool onBoard(int x, int y);
      
public:
    Board();
    ~Board();
    Board *copy();
        
    bool isDone();
    bool hasMoves(Side side);
    bool checkMove(Move *m, Side side);
    void doMove(Move *m, Side side);
    int count(Side side);
    int countBlack();
    int countWhite();
    Move *returnPossibleMove(Side side);
    void setBoard(char data[]);
};

#endif
