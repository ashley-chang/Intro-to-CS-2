//
//  History.h
//  Project1
//
//  Created by Ashley Chang on 6/25/15.
//  Copyright (c) 2015 Ashley Chang. All rights reserved.
//

#ifndef __Project1__History__
#define __Project1__History__
class Pit;
#include "globals.h"

class History
{
public:
    History(int nRows, int nCols);
    bool record(int r, int c);
    void display() const;
  
private:
    int m_nRows;
    int m_nCols;
    char drawPit [MAXROWS][MAXCOLS];

};

#endif /* defined(__Project1__History__) */
