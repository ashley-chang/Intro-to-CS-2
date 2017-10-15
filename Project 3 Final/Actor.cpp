#include "Actor.h"
#include "StudentWorld.h"
#include "Level.h"


// Students:  Add code to this file (if you wish), Actor.h, StudentWorld.h, and StudentWorld.cpp
/*
 Actors to Account For:
 Player
 SnarlBot (Vertical, Horizontal)
 KleptoBot
 Factories for kleptoBots
 Bullets
 Exit
 Wall
 Hostages
 Gates
 Jewels
 Extra Life Goodies
 Restore Health Goodies
 Ammo Goodies
 */
//******************************************************************************
//Parameterized constructor
Actor::Actor(StudentWorld* sptr, int ID, int x, int y, Direction startDir, int subLev):
GraphObject(ID, x, y, startDir, subLev), sw_ptr(sptr)
{
    setVisible(true);
    m_alive = true;
}

StudentWorld* Actor::getWorld()
{
    return sw_ptr;
}

bool Actor::isAlive()
{
    return m_alive;
}

void Actor::setDead()
{
    m_alive = false;
}

void Actor::receiveDamage(int hurt){}

Actor::~Actor()
{}
//******************************************************************************
Moveable::Moveable(StudentWorld* sptr, int ID, int x, int y, Direction startDir, int subLev): Actor(sptr, ID, x, y, startDir, subLev)
{}

void Moveable::doSomething()
{}

bool Moveable::tryToMove(int x, int y)
{
    std::vector<Actor*> occ = getWorld()->getContents(x,y); //Get a vector of things at on this spot
    for (int i = 0; i < occ.size(); i++) //Check to see if actor can pass through this spot
    {
        int blocked = occ[i]->getID();
        switch (blocked) //If run into a wall, robot factory, or moveable object, return false (obstacle)
        {
            case IID_WALL:
            case IID_SNARLBOT:
            case IID_ROBOT_FACTORY:
            case IID_KLEPTOBOT:
                return false;
                break;
            default:
                break;
        }
    }
    if (getWorld()->getPlayer(x, y) != nullptr) //If there is a player at x, y, return false
        return false;
    return true; //If no obstacles, return true (can move)
}
bool Moveable::go(Direction dir)
{
    setDirection(dir); //Set the actor to face the desired direction
    switch (dir) //Check if the next spot in the desired direction has any obstacles, if so break, if not then move and return true
    {
        case left:
            if (!tryToMove(getX()-1, getY()))
                break;
            moveTo(getX()-1, getY());
            return true;
            break;
        case right:
            if (!tryToMove(getX()+1, getY()))
                break;
            moveTo(getX()+1, getY());
            return true;
            break;
        case down:
            if (!tryToMove(getX(), getY()-1))
                break;
            moveTo(getX(), getY()-1);
            return true;
            break;
        case up:
            if (!tryToMove(getX(), getY()+1))
                break;
            moveTo(getX(), getY()+1);
            return true;
            break;
        default:
            break;
    }
    return false; //If unable to move, then return false
}
void Moveable::receiveDamage(int hurt)
{}

void Moveable::moveLine(Direction dir)
{}

void Moveable::fire()
{
    int xcoord = getX();
    int ycoord = getY();
    switch (getDirection())
    {
        case up:
            ycoord++;
            break;
        case down:
            ycoord--;
            break;
        case left:
            xcoord--;
            break;
        case right:
            xcoord++;
            break;
        default:
            break;
    }
    Actor* temp = new Bullet (getWorld(), xcoord, ycoord, getWorld()->getCurrentSubLevel(), getDirection()); //Allocate a new bullet
    getWorld()->makeNew(temp); //Push bullet into actor vector
}

Moveable::~Moveable(){}
//******************************************************************************
Bullet::Bullet(StudentWorld* sptr, int x, int y, int sublev, Direction startDir): Moveable(sptr, IID_BULLET, x, y, startDir, sublev), m_dir(startDir)
{}
bool Bullet::hitStuff()
{
    //Check to see if any other objects are on current square
    std::vector<Actor*> actorObstacle = getWorld()->getContents(getX(), getY());
    Player* playerObstacle = getWorld()->getPlayer(getX(),getY()); //Find out whether there is a player on square
    if (playerObstacle != nullptr) //If there is a player on this square,
    {
        getWorld()->getHit(3);
        getWorld()->playSound(SOUND_PLAYER_IMPACT);
        setDead();
        return true;
    }
    else if (!actorObstacle.empty())
    {
        for (int i = 0; i < actorObstacle.size(); i++)
        {
            if (actorObstacle[i]->getID() == IID_SNARLBOT || actorObstacle[i]->getID() == IID_KLEPTOBOT)
            {
                actorObstacle[i]->receiveDamage(2);
                getWorld()->playSound(SOUND_ROBOT_IMPACT);
                setDead();
                return true;
            }
            else if (actorObstacle[i]->getID() == IID_WALL)
            {
                setDead();
                return true;
            }
        }
    }
    return false;
}
void Bullet::moveLine(Direction dir)
{
    switch(dir)
    {
        case up:
            moveTo(getX(), getY()+1);
            break;
        case down:
            moveTo(getX(), getY()-1);
            break;
        case left:
            moveTo(getX()-1, getY());
            break;
        case right:
            moveTo(getX()+1, getY());
            break;
        default:
            break;
    }
}
void Bullet::doSomething()
{
    if (!isAlive())
        return;
    if (!hitStuff()) //Check to see if any other objects are on current square
        moveLine(getDirection()); //If not, keep going
    hitStuff();
}

//Bullet::~Bullet(){}

//******************************************************************************
Stationary::Stationary(StudentWorld* sptr, int ID, int x, int y, Direction startDir, int subLev): Actor(sptr, ID, x, y, none, subLev)
{}

void Stationary::doSomething()
{}

Stationary::~Stationary(){}
//******************************************************************************

Goodie::Goodie(StudentWorld* sptr, int ID, int x, int y, Direction startDir, int subLev): Stationary(sptr, ID, x, y, none, subLev)
{}

void Goodie::pickUp(int ID, int points) //Function to remove objects after the player encounters them, then apply appropriate goodie rewards
{
    if (!isAlive())
        return;
    if(getWorld()->getPlayer(getX(), getY()) != nullptr) //If the player is on the same spot as a goodie,
    {
        setDead();
        getWorld()->playSound(SOUND_GOT_GOODIE); //Play goodie sound
        getWorld()->decCount(ID); //If jewel/hostage, adjust number available
        switch (ID) //Do auxiliary stuff (adding points, etc)
        {
            case IID_AMMO:
                getWorld()->addAmmo(25);
                break;
            case IID_RESTORE_HEALTH:
                getWorld()->restoreHealth();
                break;
            case IID_EXTRA_LIFE:
                getWorld()->incLives();
                break;
            case IID_EXIT:
                getWorld()->finishedLevel();
                break;
            default:
                break;
        }
        getWorld()->increaseScore(points); //Increase score appropriately according to goodie values
    }
}

void Goodie::doSomething(){}
Goodie::~Goodie(){}
//******************************************************************************
Bot::Bot(StudentWorld* sptr, int ID, int x, int y, Direction startDir, int sublev, int hitpts): Moveable(sptr, ID, x, y, startDir, sublev), m_hitpts(hitpts)
{
    int ticks = (28-(getWorld()->getLevel()))/4; //Calculate movement speed
    if (ticks < 3)
        m_ticks = 3; //Set movement speed
    else
        m_ticks = ticks;
    m_rest = m_ticks;
}
void Bot::receiveDamage(int hurt)
{
    m_hitpts -= hurt;
}
//int Bot::getHitPts()
//{
//    return m_hitpts;
//}
void Bot::checkKilled()
{
    if (m_hitpts <= 0)
    {
        setDead();
        getWorld()->playSound(SOUND_ROBOT_DIE);
    }
}
bool Bot::rest()
{
    if (m_rest == 0) //If appropriate amount of ticks/time have passed,
    {
        m_rest= m_ticks;    //Reset rest time
        return false;
    }
    else            //Not yet time to move
        m_rest--;           //Continue rest time
    return true;
}
void Bot::doSomething()
{}
void Bot::moveLine(){}
Bot::~Bot(){}

//******************************************************************************
SnarlBot::SnarlBot(StudentWorld* sptr, int x, int y, int sublev, Direction startDir): Bot(sptr, IID_SNARLBOT, x, y, startDir, sublev, 20)
{}
void SnarlBot::doSomething()
{
    if (!isAlive())
        return;
    checkKilled(); //Check if hit points are less than 0; if so, then set to dead
    if (!isAlive())
    {
        getWorld()->increaseScore(200);
        return;
    }
    if (!rest()) //If not resting on this tick, take action
    {
        if (detectPlayer() != nullptr && !findObstacle())
        {
            fire();
            getWorld()->playSound(SOUND_ENEMY_FIRE);
            return;
        }
        else if (detectPlayer() == nullptr || findObstacle()) //If don't detect player/obstacle in way of player, keep moving
        {
            if (getDirection() == right || getDirection() == left)
                moveLine(getDirection());
            else if (getDirection() == up || getDirection() == down)
                moveLine(getDirection());
        }
    }
}
bool SnarlBot::findObstacle() //Determine whether there is an obstacle at this position
{
    int xcoord = getX(); //Record coordinates until find obstacle
    int ycoord = getY();
    if (detectPlayer() != nullptr) //Check whether there is a player in front
    {
        int playerX = detectPlayer()->getX(); //Record coordinates of player
        int playerY = detectPlayer()->getY();
        switch (getDirection())
        {
            case up:
                for (int i = ycoord; i < playerY; i++)
                {
                    std::vector<Actor*> obstacles = getWorld()->getContents(xcoord, i+1); //Get a vector of objects at this square
                    for (int q = 0; q < obstacles.size(); q++)
                    {
                        switch (obstacles[q]->getID()) //If any of the objects at this square are an obstacle, return true
                        {
                            case IID_WALL:
                            case IID_KLEPTOBOT:
                            case IID_SNARLBOT:
                            case IID_ROBOT_FACTORY:
                                return true;
                            default:
                                break;
                        }
                    }
                }
            case down:
                for (int i = ycoord; i > playerY; i--)
                {
                    std::vector<Actor*> obstacles = getWorld()->getContents(xcoord, i-1); //Get a vector of objects at this square
                    for (int q = 0; q < obstacles.size(); q++)
                    {
                        switch (obstacles[q]->getID()) //If any of the objects at this square are an obstacle, return true
                        {
                            case IID_WALL:
                            case IID_KLEPTOBOT:
                            case IID_SNARLBOT:
                            case IID_ROBOT_FACTORY:
                                return true;
                            default:
                                break;
                        }
                    }
                }
            case left:
                for (int i = xcoord; i > playerX; i--)
                {
                    std::vector<Actor*> obstacles = getWorld()->getContents(i-1, ycoord); //Get a vector of objects at this square
                    for (int q = 0; q < obstacles.size(); q++)
                    {
                        switch (obstacles[q]->getID()) //If any of the objects at this square are an obstacle, return true
                        {
                            case IID_WALL:
                            case IID_KLEPTOBOT:
                            case IID_SNARLBOT:
                            case IID_ROBOT_FACTORY:
                                return true;
                            default:
                                break;
                        }
                    }
                }
            case right:
                for (int i = xcoord; i < playerX; i++)
                {
                    std::vector<Actor*> obstacles = getWorld()->getContents(i+1, ycoord); //Get a vector of objects at this square
                    for (int q = 0; q < obstacles.size(); q++)
                    {
                        switch (obstacles[q]->getID()) //If any of the objects at this square are an obstacle, return true
                        {
                            case IID_WALL:
                            case IID_KLEPTOBOT:
                            case IID_SNARLBOT:
                            case IID_ROBOT_FACTORY:
                                return true;
                            default:
                                break;
                        }
                    }
                }
            default:
                break;
        }
    }
    return false;
}

Player* SnarlBot::detectPlayer() //Find player within range in front
{
    Player* detected = nullptr; //Declare a pointer to find the actor if within view
    int xcoord = getX(); //Record coordinates until find player
    int ycoord = getY();
    switch (getDirection())
    {
        case up:
            for (int i = ycoord; i < 15; i++)
                if (getWorld()->getPlayer(xcoord, i) != nullptr) //If there is a player at this spot
                    return detected = getWorld()->getPlayer(xcoord, i); //Return pointer to that player
            break;
        case down:
            for (int i = ycoord; i >=0; i--)
                if (getWorld()->getPlayer(xcoord, i) != nullptr) //If there is a player at this spot
                    return detected = getWorld()->getPlayer(xcoord, i); //Return pointer to that player
            
            break;
        case left:
            for (int i = xcoord; i >= 0; i--)
                if (getWorld()->getPlayer(i, ycoord) != nullptr) //If there is a player at this spot
                    return detected = getWorld()->getPlayer(i, ycoord); //Return pointer to that player
            break;
        case right:
            for (int i = xcoord; i < 15; i++)
                if (getWorld()->getPlayer(i, ycoord) != nullptr) //If there is a player at this spot
                    return detected = getWorld()->getPlayer(i, ycoord); //Return pointer to that player
            break;
        default:
            std::cerr<< "notfound" << std::endl;
            break;
    }
    return nullptr; //Return pointer to player (if found)
}

void SnarlBot::moveLine(Direction dir)
{
    if (dir == left || dir == right) //If horizontal snarlbot
    {
        if (getDirection() == left)
        {
            if (!go(left)) //If encounter obstacle, go opposite way
                go(right);
        }
        else if (getDirection() == right)
        {
            if (!go(right)) //If encounter obstacle, go opposite way
                go(left);
        }
    }
    else if (dir == up || dir == down) //If vertical snarlbot
    {
        if (getDirection() == up)
        {
            if (!go(up)) //If encounter obstacle, go opposite way
                go(down);
        }
        else if (getDirection() == down)
        {
            if (!go(down)) //If encounter obstacle, go opposite way
                go(up);
        }
    }
}

//SnarlBot::~SnarlBot(){}
//******************************************************************************
KleptoBot::KleptoBot(StudentWorld *sptr, int x, int y, int sublev): Bot(sptr, IID_KLEPTOBOT, x, y, right, sublev, 9), m_distanceBeforeTurning(3), m_storedGoodie(nullptr)
{}
void KleptoBot::doSomething()
{
    if (!isAlive()) //If kleptobot is not alive, do nothing
        return;
    checkKilled(); //Check if hit points are less than 0; if so, then set to dead
    if (!isAlive() && m_storedGoodie !=nullptr) //If  set to dead during this tick and was holding a goodie, restore the goodie
    {
        getWorld()->increaseScore(20);
        m_storedGoodie->setVisible(true);
        return;
    }
    std::vector<Actor*> goodiePresent = getWorld()->getContents(getX(),getY());
    Actor* goods = nullptr;
    for (int g = 0; g < goodiePresent.size(); g++)
    {
        switch (goodiePresent[g]->getID())
        {
            case IID_EXTRA_LIFE:
            case IID_RESTORE_HEALTH:
            case IID_AMMO:
                goods = goodiePresent[g];
                break;
            default:
                break;
        }
        if (goods != nullptr)
            break;
    }

    if (!rest()) //If not resting on this tick, take action
    {
        if (m_storedGoodie == nullptr && goods !=nullptr) //If not holding goodie and Kleptobot is standing on one, attempt to pick one up
        {
            int chance = rand() % 4;
            if (chance == 0) //Prompt kleptobot to pick up
            {
                m_storedGoodie = goods; //Get pointer to goodie the kleptobot is standing on
                m_storedGoodie->setVisible(false); //Set the goodie to invisible to indicate that it has been picked up
                getWorld()->playSound(SOUND_ROBOT_MUNCH); //Play sound to indicate pick up
                return; //Do nothing more during this tick
            }
        }
        //Did not pick up a goodie...
        if (m_distanceBeforeTurning != 0) //Keep going in this direction (not yet moved distanceBeforeturning squares in current dir)
        {
            if (!go(getDirection())) //Can't keep moving in this direction (obstacle), so change directions
            {
                m_distanceBeforeTurning = 0;
            }
            else //Can keep going, so move to adjacent square in this direction
            {
                m_distanceBeforeTurning--;
                return;
            }
        }
        if (m_distanceBeforeTurning == 0) //Moved 3 steps already
        {
            m_distanceBeforeTurning = rand() % 3+1; //Select random value to be new distanceBeforeTurning
            int canMove = false;
            bool upBlock = false;
            bool downBlock = false;
            bool leftBlock = false;
            bool rightBlock = false;
            while (canMove == false)
            {
                int newDir = rand() % 4;
                switch (newDir)
                {
                    case 0:
                        if (go(up))
                            canMove = true;
                        else
                            upBlock = true;
                        break;
                    case 1:
                        if (go(down))
                            canMove = true;
                        else
                            downBlock = true;
                        break;
                    case 2:
                        if (go(left))
                            canMove = true;
                        else
                            leftBlock = true;
                        break;
                    case 3:
                        if (go(right))
                            canMove = true;
                        else
                            rightBlock = true;
                        break;
                }
                if (upBlock == true && downBlock == true && leftBlock == true && rightBlock == true) //If blocked in all directions,
                {
                    switch (newDir) //Change direction to whatever the random direction specified
                    {
                        case 0:
                            setDirection(up);
                            break;
                        case 1:
                            setDirection(down);
                            break;
                        case 2:
                            setDirection(left);
                            break;
                        case 3:
                            setDirection(right);
                            break;
                    }
                    break; //Break out of while loop
                }
            }
        }
    }
    
}
//void KleptoBot::moveLine(Direction dir)
//{
//    
//}
//KleptoBot::~KleptoBot(){}
//******************************************************************************
Player::Player(StudentWorld* sptr, int x, int y, int sublev): Moveable(sptr, IID_PLAYER, x, y, right, sublev)
{}

void Player::doSomething()
{
    if (!isAlive())
        return;
    if (getWorld()->getHealth() <= 0)
        setDead();
    int ch;
    if (getWorld()->getKey(ch)) //If receive directional command, attempt to process
    {
        switch (ch)
        {
            case KEY_PRESS_LEFT:
                go(left);
                break;
            case KEY_PRESS_RIGHT:
                go(right);
                break;
            case KEY_PRESS_DOWN:
                go(down);
                break;
            case KEY_PRESS_UP:
                go(up);
                break;
            case KEY_PRESS_ESCAPE:
                setDead();
                break;
            case KEY_PRESS_SPACE:
            {
                if (getWorld()->getAmmo() > 0)
                {
                    getWorld()->addAmmo(-1);
                    fire();
                    getWorld()->playSound(SOUND_PLAYER_FIRE); // Get sound
                }
            }
                break;
        }
    }
}

//Player::~Player(){}

//******************************************************************************
Wall::Wall(StudentWorld* sptr, int x, int y, int sublev): Stationary(sptr, IID_WALL, x, y, none, sublev)
{}
//Wall::~Wall(){}
void Wall::doSomething()
{}

//******************************************************************************
Exit::Exit(StudentWorld* sptr, int x, int y, int sublev):Goodie(sptr, IID_EXIT, x, y, none, sublev)
{
    setVisible(false);
}
Exit::~Exit()
{}
void Exit::doSomething()
{
    if (!isAlive())
        return;
    if (getWorld()->revealExit())
    {
        if (!isVisible())
        {
            getWorld()->playSound(SOUND_REVEAL_EXIT);
        }
        setVisible(true);
    }
    if (isVisible())
        pickUp(IID_EXIT, 1000+getWorld()->bonusTime());
    
}
//******************************************************************************
Gate::Gate(StudentWorld* sptr, int x, int y, int sublev, int destination): Stationary(sptr, IID_GATE, x, y, none, sublev), m_gateNumber(destination)
{}
void Gate::doSomething()
{
    if (!isAlive())
        return;
    if (getWorld()->getPlayer(getX(), getY()) != nullptr) //If there is a player on the same square as the exit, transport!
    {
        setDead();
        getWorld()->setCurrentSubLevel(m_gateNumber);
    }
    //go to student world and make sure sublevel is correct
}
//Gate::~Gate(){}
//******************************************************************************
KleptoFactory::KleptoFactory (StudentWorld *sptr, int x, int y, int sublev): Stationary(sptr, IID_ROBOT_FACTORY, x, y, none, sublev)
{
}
int KleptoFactory::countBots() //Counts kleptobots in 3x3 vicinity
{
    int kleptoCount = 0; //Initialize kleptobot count
    for (int i = getX()-1; i <= getX()+1 && i >= 0 && i < 15; i++) //For every valid square in the vicinity (not out of bounds)
        for (int j = getY()-1; j <= getY()+1 && j >= 0 && j < 15; j++)
        {
            std::vector<Actor*> kleptos = getWorld()->getContents(i, j); //Get a vector of actors at that spot
            for (int k = 0; k < kleptos.size(); k++)
            {
                if (kleptos[k]->getID() == IID_KLEPTOBOT) //Check to see if any kleptobots, and add to count
                    kleptoCount++;
            }
        }
    return kleptoCount;
}

void KleptoFactory::doSomething()
{
    std::vector<Actor*> findKlepto = getWorld()->getContents(getX(), getY()); //Find out whether there is a kleptoBot on the factory
    bool kleptoPresent = false;
    for (int i = 0; i < findKlepto.size(); i++)
    {
        if (findKlepto[i]->getID() == IID_KLEPTOBOT)
        {
            kleptoPresent = true;
            break;
        }
    }
    if (countBots() < 3 && !kleptoPresent) //If less than 3 kleptobots in the vicinity
    {
        int produceBot = rand() % 50; //1 in 50 chance that factory will produce kleptobot
        if (produceBot == 0) //Push back a new kleptobot into actor vector
        {
            Actor* temp = new KleptoBot(getWorld(), getX(), getY(), getWorld()->getCurrentSubLevel());
            getWorld()->makeNew(temp);
            getWorld()->playSound(SOUND_ROBOT_BORN);
        }
    }
}
//KleptoFactory::~KleptoFactory(){}
//******************************************************************************
Hostage::Hostage (StudentWorld* sptr, int x, int y, int sublev): Goodie(sptr, IID_HOSTAGE, x, y, none, sublev)
{}
void Hostage::doSomething()
{
    pickUp(IID_HOSTAGE, 0);
}
//Hostage::~Hostage(){}

//******************************************************************************
Jewel::Jewel(StudentWorld* sptr, int x, int y, int sublev): Goodie (sptr, IID_JEWEL, x, y, none, sublev)
{}
void Jewel::doSomething()
{
    pickUp(IID_JEWEL, 100);
    
}
//Jewel::~Jewel(){}

//******************************************************************************
Ammo::Ammo(StudentWorld* sptr, int x, int y, int sublev): Goodie (sptr, IID_AMMO, x, y, none, sublev)
{
}
void Ammo::doSomething()
{
    if (!isAlive())
        return;
    pickUp(IID_AMMO, 200);
}
//Ammo::~Ammo(){}
//******************************************************************************
ExtraLife::ExtraLife(StudentWorld* sptr, int x, int y, int sublev): Goodie (sptr, IID_EXTRA_LIFE, x, y, none, sublev)
{}
void ExtraLife::doSomething()
{
    if (!isAlive())
        return;
    pickUp(IID_EXTRA_LIFE,500);
}
//ExtraLife::~ExtraLife(){}
//******************************************************************************
RestoreHealth::RestoreHealth(StudentWorld* sptr, int x, int y, int sublev): Goodie (sptr, IID_RESTORE_HEALTH, x, y, none, sublev)
{
}
void RestoreHealth::doSomething()
{
    if (!isAlive())
        return;
    pickUp(IID_RESTORE_HEALTH, 1000);
}
//RestoreHealth::~RestoreHealth(){}
//******************************************************************************




