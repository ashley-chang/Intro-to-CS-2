//
//  Snake.h
//  Project1
//
//  Created by Ashley Chang on 6/24/15.
//  Copyright (c) 2015 Ashley Chang. All rights reserved.
//

#ifndef __Project1__Snake__
#define __Project1__Snake__

class Pit;

class Snake
{
public:
    // Constructor
    Snake(Pit* pp, int r, int c);
    
    // Accessors
    int  row() const;
    int  col() const;
    
    // Mutators
    void move();
    
private:
    Pit* m_pit;
    int  m_row;
    int  m_col;
};

#endif /* defined(__Project1__Snake__) */
