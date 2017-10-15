//
//  main.cpp
//  Project1
//
//  Created by Ashley Chang on 6/23/15.
//  Copyright (c) 2015 Ashley Chang. All rights reserved.
//
// snakepit.cpp

#include "History.h"
#include "Snake.h"
#include "Player.h"
#include "Pit.h"
#include "globals.h"
#include "Game.h"

///////////////////////////////////////////////////////////////////////////
//  main()
///////////////////////////////////////////////////////////////////////////

int main()
{
    // Initialize the random number generator.  (You don't need to
    // understand how this works.)
    srand(static_cast<unsigned int>(time(0)));
    
    // Create a game
    // Use this instead to create a mini-game:   Game g(3, 3, 2);
    Game g(4, 4, 2);
    
    // Play the game
    g.play();
}

