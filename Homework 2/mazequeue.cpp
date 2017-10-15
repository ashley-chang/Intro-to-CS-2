//
//  mazequeue.cpp
//  Homework2
//
//  Created by Ashley Chang on 7/8/15.
//  Copyright (c) 2015 Ashley Chang. All rights reserved.
//

#include <iostream>
#include <stack>
#include <string>
#include <queue>

using namespace std;

class Coord
{
public:
    Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
    int r() const { return m_r; }
    int c() const { return m_c; }
private:
    int m_r;
    int m_c;
};

#include <queue>
using namespace std;


bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
{
    queue<Coord> coordQueue;
    
    coordQueue.push(Coord(sr,sc));
    maze[sr][sc] = 'o';
    while (!coordQueue.empty())
    {
        Coord location = coordQueue.front();
        coordQueue.pop(); //Pop top coord off -- location holds current (r,c)
        if (location.r() == er && location.c() == ec) //If equal to ending coordinate, solved maze!!
        {
            return true;
        }
        if (location.r()-1 >= 0 && maze[location.r()-1][location.c()] == '.') //Can move NORTH and the cell is unencountered
        {
            coordQueue.push(Coord(location.r()-1, location.c())); //Push coordinate (r-1, c)
            maze[location.r()-1][location.c()] = 'o'; //Update to indicate encounter
        }
        if (location.c()+1 < nCols && maze[location.r()][location.c()+1] == '.') //Can move EAST and the cell is unencountered
        {
            coordQueue.push(Coord(location.r(),location.c()+1)); //Push coordinate (r, c+1)
            maze[location.r()][location.c()+1] = 'o';
        }
        if (location.r()+1 < nRows && maze[location.r()+1][location.c()] == '.') //Can move SOUTH and the cell is unencountered
        {
            coordQueue.push(Coord(location.r()+1, location.c()));
            maze[location.r()+1][location.c()] = 'o';
        }
        if(location.c()-1 >= 0 && maze[location.r()][location.c()-1] == '.') //Can move WEST and the cell is unencountered
        {
            coordQueue.push(Coord(location.r(), location.c()-1));
            maze[location.r()][location.c()-1] = 'o';
        }
    }
    return false;
}


int main()
{
    string maze[10] = {
        "XXXXXXXXXX",
        "X.......@X",
        "XX@X@@.XXX",
        "X..X.X...X",
        "X..X...@.X",
        "X....XXX.X",
        "X@X....XXX",
        "X..XX.XX.X",
        "X...X....X",
        "XXXXXXXXXX"
    };
    
    if (pathExists(maze, 10,10, 6,4, 1,1))
        cout << "Solvable!" << endl;
    else
        cout << "Out of luck!" << endl;
}
