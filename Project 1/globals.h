//
//  globals.h
//  Project1
//
//  Created by Ashley Chang on 6/24/15.
//  Copyright (c) 2015 Ashley Chang. All rights reserved.
//

#ifndef Project1_globals_h
#define Project1_globals_h

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;
///////////////////////////////////////////////////////////////////////////
//  Auxiliary function declarations
///////////////////////////////////////////////////////////////////////////

int decodeDirection(char dir);
bool directionToDeltas(int dir, int& rowDelta, int& colDelta);
void clearScreen();

///////////////////////////////////////////////////////////////////////////
// Manifest constants
///////////////////////////////////////////////////////////////////////////

const int MAXROWS = 20;             // max number of rows in the pit
const int MAXCOLS = 40;             // max number of columns in the pit
const int MAXSNAKES = 190;          // max number of snakes allowed

const int UP    = 0;
const int DOWN  = 1;
const int LEFT  = 2;
const int RIGHT = 3;

#endif
