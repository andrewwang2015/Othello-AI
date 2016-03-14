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
    bool occupied(int x, int y);
    bool get(Side side, int x, int y);
    void set(Side side, int x, int y);
    bool onBoard(int x, int y);
    vector <Move*> possibleMoves;
      
public:
    Board();
    ~Board();
    Board *copy();
        
    bool isDone();
    bool hasMoves(Side side);
    bool checkMove(Move *m, Side side);
    void doMove(Move *m, Side side);
    int count(Side side);
    vector <Move*> returnPossibleMoves(Side side); 
    int countBlack();
    int countWhite();
    void setBoard(char data[]);
    int calculateScoreOfBoard (Side mine, Side theirs);
};

#endif
