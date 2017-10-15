#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

class StudentWorld;

class Actor: public GraphObject //Pure virtual!! can't declare
{
public:
    Actor(StudentWorld* sptr, int ID, int x, int y, Direction startDir, int subLev); //Parameterized constructor--gets info for graphObject
    virtual void doSomething() = 0;
    StudentWorld* getWorld();
    bool isAlive();
    void setDead();
    virtual ~Actor() = 0; //(Virtual) Destructor
    virtual void receiveDamage(int hurt);
private:
    bool m_alive;
    StudentWorld* sw_ptr;
    
};

class Moveable: public Actor
{
public:
    Moveable(StudentWorld* sptr, int ID, int x, int y, Direction startDir, int subLev);
    virtual ~Moveable() = 0;
    virtual void receiveDamage(int hurt);
    virtual void doSomething()= 0;
    bool tryToMove(int x, int y);
    bool go(Direction dir);
    virtual void moveLine(Direction dir);
    void fire();
private:
};

class Stationary: public Actor
{
public:
    Stationary(StudentWorld* sptr, int ID, int x, int y, Direction startDir, int subLev);
    virtual ~Stationary() = 0;
    virtual void doSomething() = 0;
    
};

class Goodie: public Stationary
{
public:
    Goodie(StudentWorld* sptr, int ID, int x, int y, Direction startDir, int subLev);
    virtual ~Goodie() = 0;
    void pickUp(int ID, int points);
    virtual void doSomething() = 0;
};

class Gate: public Stationary
{
public:
    Gate (StudentWorld* sptr, int x, int y, int sublev, int destination);
    //virtual ~Gate();
    virtual void doSomething();
private:
    int m_gateNumber;
};

class Wall: public Stationary
{
public:
    Wall(StudentWorld* sptr, int x, int y, int sublev); //Constructor
    //virtual ~Wall(); //Destructor
    virtual void doSomething();
};
class KleptoFactory: public Stationary
{
public:
    KleptoFactory(StudentWorld* sptr, int x, int y, int sublev);
    //virtual ~KleptoFactory();
    virtual void doSomething();
    int countBots();
};
class Exit: public Goodie
{
public:
    Exit(StudentWorld* sptr, int x, int y, int sublev);
    ~Exit();
    virtual void doSomething();
};

class Player: public Moveable
{
public:
    Player(StudentWorld* sptr, int x, int y, int sublev);
    virtual void doSomething();
    //virtual ~Player();
private:
    
};

class Hostage: public Goodie
{
public:
    Hostage(StudentWorld* sptr, int x, int y, int sublev);
    virtual void doSomething();
    //virtual ~Hostage();
};
class Jewel: public Goodie
{
public:
    Jewel(StudentWorld* sptr, int x, int y, int sublev);
    virtual void doSomething();
    //virtual ~Jewel();
};
class ExtraLife: public Goodie
{
public:
    ExtraLife(StudentWorld* sptr, int x, int y, int sublev);
    virtual void doSomething();
    //virtual ~ExtraLife();
};
class RestoreHealth: public Goodie
{
public:
    RestoreHealth(StudentWorld* sptr, int x, int y, int sublev);
    virtual void doSomething();
    //virtual ~RestoreHealth();
};
class Ammo: public Goodie
{
public:
    Ammo(StudentWorld* sptr, int x, int y, int sublev);
    virtual void doSomething();
    //virtual ~Ammo();
};
class Bot: public Moveable
{
public:
    Bot(StudentWorld* sptr, int ID, int x, int y, Direction startDir, int sublev, int hitpts);
    virtual void doSomething()=0;
    virtual void receiveDamage(int hurt);
    virtual void moveLine();
    void checkKilled();
    bool rest();
    //int getHitPts();
    virtual ~Bot() = 0;
private:
    int m_hitpts;
    int m_ticks;
    int m_rest;
};
class KleptoBot: public Bot
{
public:
    KleptoBot(StudentWorld* sptr, int x, int y, int sublev);
    virtual void doSomething();
    //virtual ~KleptoBot();
private:
    int m_distanceBeforeTurning;
    Actor* m_storedGoodie;
};
class SnarlBot: public Bot
{
public:
    SnarlBot(StudentWorld* sptr, int x, int y, int sublev, Direction startDir);
    bool findObstacle();
    Player* detectPlayer();
    virtual void doSomething();
    void moveLine(Direction dir);
    //virtual ~SnarlBot();
};

class Bullet: public Moveable
{
public:
    Bullet(StudentWorld* sptr, int x, int y, int sublev, Direction startDir);
    virtual void doSomething();
    virtual void moveLine(Direction dir);
    bool hitStuff();
    //virtual ~Bullet();
private:
    Direction m_dir;
    
};
#endif // ACTOR_H_
