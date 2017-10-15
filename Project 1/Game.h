//
//  Game.h
//  Project1
//
//  Created by Ashley Chang on 6/24/15.
//  Copyright (c) 2015 Ashley Chang. All rights reserved.
//

#ifndef __Project1__Game__
#define __Project1__Game__

class Pit;
class History;

class Game
{
public:
    // Constructor/destructor
    Game(int rows, int cols, int nSnakes);
    ~Game();
    
    // Mutators
    void play();
    
private:
    Pit* m_pit;
};

#endif /* defined(__Project1__Game__) */
