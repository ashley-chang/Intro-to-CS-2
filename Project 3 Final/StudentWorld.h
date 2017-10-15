#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "GameConstants.h"
#include <string>
#include <vector>

#include "Level.h"

class Actor;

class Player;
// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetDir);
    
    virtual int init();
    
    virtual int move();
    
    virtual void cleanUp();
    
    int getCurrentSubLevel();
    
    std::vector<Actor*> getContents(int x, int y);
    Player* getPlayer(int x, int y);
    
    void setCurrentSubLevel (int l);
    //Level::LoadResult loadSubLevel(std::string sub);
    
    void decCount(int ID);
    bool revealExit();
    
    void addAmmo(int amount);
    void restoreHealth();
    void getHit(int hit);
    int getHealth();
    int getAmmo();
    void makeNew(Actor* thing);
    int bonusTime();
    void finishedLevel();
    
    void setDisplayText();
    ~StudentWorld();
    
private:
    std::vector<Player*> m_player;
    std::vector<std::vector<Actor*>> m_actors;
    int m_subLevel;
    int m_jewels;
    int m_hostages;
    int m_health;
    int m_ammo;
    int m_timeLeft;
    bool m_finishedLevel;
    
    
    
};

#endif // STUDENTWORLD_H_

