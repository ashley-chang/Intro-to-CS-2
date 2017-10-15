//
//  Pit.h
//  Project1
//
//  Created by Ashley Chang on 6/24/15.
//  Copyright (c) 2015 Ashley Chang. All rights reserved.
//

#ifndef __Project1__Pit__
#define __Project1__Pit__

class Player;
class Snake;
#include "globals.h"
#include "History.h"

class Pit
{
public:
    // Constructor/destructor
    Pit(int nRows, int nCols);
    ~Pit();
    
    // Accessors
    int     rows() const;
    int     cols() const;
    Player* player() const;
    int     snakeCount() const;
    int     numberOfSnakesAt(int r, int c) const;
    void    display(string msg) const;
    History& history();
    
    // Mutators
    bool   addSnake(int r, int c);
    bool   addPlayer(int r, int c);
    bool   destroyOneSnake(int r, int c);
    bool   moveSnakes();
    
private:
    int     m_rows;
    int     m_cols;
    Player* m_player;
    Snake*  m_snakes[MAXSNAKES];
    int     m_nSnakes;
    History m_history;
};

#endif /* defined(__Project1__Pit__) */
