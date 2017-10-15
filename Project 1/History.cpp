//
//  History.cpp
//  Project1
//
//  Created by Ashley Chang on 6/25/15.
//  Copyright (c) 2015 Ashley Chang. All rights reserved.
//

#include "History.h"
#include "globals.h"

History::History (int nRows, int nCols): m_nRows(nRows), m_nCols(nCols)
{
    for (int i = 0; i < m_nRows; i++)
    {
        for (int j = 0; j < m_nCols; j++)
        {
            drawPit[i][j] = '.';
        }
    }
    //Have created a new replica "Pit" area and filled with dots (no recorded moves yet).
}

bool History::record(int r, int c)
{
    //player is still alive--this is the position the player is at
    //false if not within bounds
    if (r <= 0 || r > m_nRows || c <= 0 || c > m_nCols)
        return false;
    //Passed test--use valid coordinates (-1 to correspond to 2D array)
    if (drawPit[r-1][c-1] == '.')
        drawPit[r-1][c-1] = 'A';
    else if (drawPit[r-1][c-1] != '.' && isalpha(drawPit[r-1][c-1]) && drawPit[r-1][c-1] != 'Z')
        drawPit[r-1][c-1] += 1;
    
    return true;
}

void History::display() const
{
    clearScreen();
    for (int i = 0; i < m_nRows; i++) //Go through and print out all the stored values in history
    {
        for (int j = 0; j < m_nCols; j++)
            cout << drawPit[i][j];
        cout << endl;
    }
    cout << endl;
}

